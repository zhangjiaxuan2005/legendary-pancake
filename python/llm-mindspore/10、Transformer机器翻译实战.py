from collections import Counter
import jieba
import mindspore
from mindspore import nn, Model, Callback, ops
from mindspore.dataset import GeneratorDataset
from mindspore.nn import optim, CosineDecayLR

data = [
    ("你好，今天天气真好！", "Hello, the weather is nice today!"),
    ("深度学习很有趣。", "Deep learning is interesting."),
    ("我们一起学习吧。", "We are learning together."),
    ("这是一个测试案例。", "This is a test example.")
]


def tokenize_chinese(text):
    return list(jieba.cut(text))


def tokenize_english(text):
    return text.lower().split()


chinese_vocab = [tokenize_chinese(pair[0]) for pair in data]
english_vocab = [tokenize_english(pair[1]) for pair in data]

chinese_sentences = [tokenize_chinese(pair[0]) for pair in data]
english_sentences = [tokenize_english(pair[1]) for pair in data]

special_tokens = ['<PAD>', '<UNK>', '<BOS>', '<EOS>']


def build_vocab(sentences):
    counter = Counter()

    for sentence in sentences:
        for word in sentence:
            counter[word] += 1

    vocab = special_tokens.copy()
    for word, count in counter.items():
        if word not in special_tokens:
            vocab.append(word)

    word_to_idx = {word: idx for idx, word in enumerate(vocab)}
    return word_to_idx, vocab


chinese_word_to_idx, chinese_vocab = build_vocab([sentence for sentence in chinese_sentences])
english_word_to_idx, english_vocab = build_vocab([sentence for sentence in english_sentences])

ch_vocab_size = len(chinese_vocab)
en_vocab_size = len(english_vocab)
batch_size = 1
Learning_rate = 0.00001


def tokenize(words, word_to_idx):
    return [word_to_idx.get(word, word_to_idx['<UNK>']) for word in words]


processed_data_ch = []
processed_data_en = []

for ch, en in zip(chinese_sentences, english_sentences):
    ch_numerical = [chinese_word_to_idx['<BOS>']] + tokenize(ch, chinese_word_to_idx) + [chinese_word_to_idx['<EOS>']]
    en_numerical = [english_word_to_idx['<BOS>']] + tokenize(en, english_word_to_idx) + [english_word_to_idx['<EOS>']]
    processed_data_ch.append(mindspore.tensor(ch_numerical, mindspore.int32))
    processed_data_en.append(mindspore.tensor(en_numerical, mindspore.int32))


def pad_sequences(sequences, pad_value, max_len=None):
    if max_len is None:
        max_len = max(len(seq) for seq in sequences)
    padded = []
    for seq in sequences:
        pad_length = max_len - len(seq)
        if pad_length > 0:
            padded_seq = mindspore.ops.pad(seq, padding=[0, pad_length], value=pad_value)
        else:
            padded_seq = seq
        padded.append(padded_seq)
    return mindspore.tensor(padded, mindspore.int32)


padded_chinese = pad_sequences(processed_data_ch, pad_value=chinese_word_to_idx['<PAD>'])
padded_english = pad_sequences(processed_data_en, pad_value=english_word_to_idx['<PAD>'])

dataset = GeneratorDataset(zip(padded_chinese, padded_english), column_names=["input", "target"])
dataloader = dataset.batch(batch_size=batch_size)


class PositionalEncoding(nn.Cell):

    def __init__(self, d_model, dropout_p=0.1, max_len=100):
        super().__init__()
        self.dropout = nn.Dropout(p=dropout_p)

        self.pe = ops.zeros((max_len, d_model), dtype=mindspore.float16)

        pos = ops.arange(0, max_len, dtype=mindspore.float16).view((-1, 1))
        angle = ops.pow(10000.0, ops.arange(0, d_model, 2, dtype=mindspore.float16) / d_model)

        self.pe[:, 0::2] = ops.sin(pos / angle)
        self.pe[:, 1::2] = ops.cos(pos / angle)

    def construct(self, x):
        batch_size = x.shape[0]

        pe = self.pe.expand_dims(0)
        pe = ops.broadcast_to(pe, (batch_size, -1, -1))

        x = x + pe[:, :x.shape[1], :]
        return self.dropout(x)


class MachineTranslation(nn.Cell):
    def __init__(self, d_model, d_ff, n_heads, n_encoder_layers, n_decoder_layers):
        super().__init__()
        self.encoder_embedding = nn.Embedding(len(chinese_vocab), d_model)
        self.decoder_embedding = nn.Embedding(len(english_vocab), d_model)
        self.pos_encoder = PositionalEncoding(d_model)
        self.transformer = nn.Transformer(d_model=d_model, dim_feedforward=d_ff, nhead=n_heads,
                                          num_decoder_layers=n_decoder_layers, num_encoder_layers=n_encoder_layers,
                                          batch_first=True)
        self.fc = nn.Linear(d_model, len(english_vocab))

    def construct(self, ch_inputs, en_inputs, mask=None):
        batch_size, en_seq_len = en_inputs.shape
        n_heads = self.transformer.nhead

        mask = ops.tril(ops.ones((en_seq_len, en_seq_len), dtype=mindspore.float32))

        mask = mask.expand_dims(0).expand_dims(0)

        mask = ops.tile(mask, (batch_size, n_heads, 1, 1))
        mask = mask.view(batch_size * n_heads, en_seq_len, en_seq_len)

        encoder_inputs = self.pos_encoder(self.encoder_embedding(ch_inputs))
        decoder_inputs = self.pos_encoder(self.decoder_embedding(en_inputs))

        outputs = self.transformer(encoder_inputs, decoder_inputs, tgt_mask=mask)

        return self.fc(outputs)


class LossMonitor(Callback):
    def step_end(self, run_context):
        cb_params = run_context.original_args()
        current_step = (cb_params.cur_epoch_num - 1) * cb_params.batch_num + cb_params.cur_step_num

        print(f"Step: {current_step}, Loss: {cb_params.net_outputs.asnumpy():.6f}")


class CustomWithLossCell(nn.Cell):
    def __init__(self, backbone, loss_fn):
        super().__init__()
        self._backbone = backbone
        self._loss_fn = loss_fn

    def construct(self, src, trg):
        output = self._backbone(src, trg)
        target = trg[:, 1:]
        output = output[:, :-1, :]
        output_flat = output.reshape(-1, output.shape[-1])
        target_flat = target.reshape(-1)
        return self._loss_fn(output_flat, target_flat)


lr_scheduler = CosineDecayLR(
    min_lr=0.00000000001,
    max_lr=Learning_rate,
    decay_steps=5000 * len(dataloader)
)

net = MachineTranslation(d_model=256, d_ff=2048, n_heads=8, n_encoder_layers=2, n_decoder_layers=2)
optimizer = optim.Adam(net.trainable_params(), learning_rate=lr_scheduler, weight_decay=0.0001)
criterion = nn.CrossEntropyLoss(ignore_index=english_word_to_idx['<PAD>'])

loss_net = CustomWithLossCell(net, criterion)
train_net = nn.TrainOneStepCell(loss_net, optimizer)
model = Model(train_net)

model.train(2000, dataloader, callbacks=[LossMonitor()])


def translate(sentence, net, beam_size=3, max_len=100, repetition_penalty=2.0):
    ch_token = mindspore.Tensor(
        [chinese_word_to_idx['<BOS>']] + tokenize(tokenize_chinese(sentence), chinese_word_to_idx) + [
            chinese_word_to_idx['<EOS>']], dtype=mindspore.int32).unsqueeze(0)
    encoder_inputs = net.pos_encoder(net.encoder_embedding(ch_token))

    candidates = [([english_word_to_idx['<BOS>']], 0)]

    for _ in range(max_len):
        new_candidates = []
        for seq, score in candidates:
            if seq[-1] == english_word_to_idx['<EOS>']:
                new_candidates.append((seq, score))
                continue

            decoder_inputs_tensor = mindspore.Tensor(seq, dtype=mindspore.int32).unsqueeze(0)
            decoder_inputs_embedded = net.pos_encoder(net.decoder_embedding(decoder_inputs_tensor))

            en_seq_len = decoder_inputs_tensor.shape[1]
            n_heads = net.transformer.nhead
            mask = ops.tril(ops.ones((en_seq_len, en_seq_len), dtype=mindspore.float32))
            mask = mask.expand_dims(0).expand_dims(0)
            mask = ops.tile(mask, (1, n_heads, 1, 1))
            mask = mask.view(1 * n_heads, en_seq_len, en_seq_len)

            outputs = net.transformer(encoder_inputs, decoder_inputs_embedded, tgt_mask=mask)
            output = net.fc(outputs)
            log_probs = ops.log_softmax(output[:, -1, :], axis=-1)

            for token in set(seq):
                log_probs[0][token] -= repetition_penalty

            topk_probs, topk_indices = ops.topk(log_probs, beam_size)

            for i in range(beam_size):
                new_seq = seq + [topk_indices[0][i].item()]
                new_score = score + topk_probs[0][i].item()
                new_candidates.append((new_seq, new_score))

        candidates = sorted(new_candidates, key=lambda x: x[1], reverse=True)[:beam_size]

        if all(seq[-1] == english_word_to_idx['<EOS>'] for seq, _ in candidates):
            break

    best_seq = max(candidates, key=lambda x: x[1])[0]

    if best_seq[-1] == english_word_to_idx['<EOS>']:
        best_seq = best_seq[1:-1]
    else:
        best_seq = best_seq[1:]

    return ' '.join(english_vocab[idx] for idx in best_seq if 0 <= idx < len(english_vocab))


test_sentence = '你好，今天天气真好！'
print(translate(test_sentence, net))
