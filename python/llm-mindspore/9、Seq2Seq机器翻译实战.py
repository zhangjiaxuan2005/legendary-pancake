from collections import Counter
import jieba
import mindspore
from mindspore import nn, Model, Callback
from mindspore.dataset import GeneratorDataset
from mindspore.nn import optim

data = [
    ("你好，今天天气真好！", "Hello, the weather is nice today!"),
    ("你吃饭了吗？", "Have you eaten yet?"),
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
hidden_size = 256
batch_size = 2
Learning_rate = 0.001


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


class Encoder(nn.Cell):
    def __init__(self, vocab_size, hidden_size):
        super().__init__()
        self.hidden_size = hidden_size
        self.encoder_embedding = nn.Embedding(vocab_size, hidden_size)
        self.encoder_gru = nn.GRU(hidden_size, hidden_size, batch_first=True)

    def construct(self, src):
        embedded = self.encoder_embedding(src)
        outputs, hidden = self.encoder_gru(embedded)
        return outputs, hidden


class Decoder(nn.Cell):
    def __init__(self, vocab_size, hidden_size):
        super().__init__()
        self.decoder_embedding = nn.Embedding(vocab_size, hidden_size)
        self.decoder_gru = nn.GRU(hidden_size, hidden_size, batch_first=True)
        self.fc = nn.Linear(hidden_size, vocab_size)

    def construct(self, trg, hidden):
        embedded = self.decoder_embedding(trg)
        output, hidden = self.decoder_gru(embedded, hidden)
        output = self.fc(output)
        return output, hidden


class Seq2Seq(nn.Cell):
    def __init__(self, encoder, decoder):
        super().__init__()
        self.encoder = encoder
        self.decoder = decoder

    def construct(self, src, trg):
        _, hidden = self.encoder(src)
        output, _ = self.decoder(trg, hidden)
        return output


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


encoder_net = Encoder(ch_vocab_size, hidden_size)
decoder_net = Decoder(en_vocab_size, hidden_size)
seq2seq_net = Seq2Seq(encoder_net, decoder_net)

optimizer = optim.Adam(seq2seq_net.trainable_params(), learning_rate=Learning_rate)
criterion = nn.CrossEntropyLoss(ignore_index=english_word_to_idx['<PAD>'])

loss_net = CustomWithLossCell(seq2seq_net, criterion)
train_net = nn.TrainOneStepCell(loss_net, optimizer)
seq2seq_model = Model(train_net)

seq2seq_model.train(100, dataloader, callbacks=[LossMonitor()])


def translate(sentence, encoder, decoder):
    token = tokenize_chinese(sentence)
    numerical = [chinese_word_to_idx.get(word, chinese_word_to_idx['<UNK>']) for word in token]
    numerical = [chinese_word_to_idx['<BOS>']] + numerical + [chinese_word_to_idx['<EOS>']]
    src = mindspore.tensor(numerical).unsqueeze(0)
    _, hidden = encoder(src)
    trg_indexes = [english_word_to_idx['<BOS>']]

    for _ in range(10):
        trg_tensor = mindspore.tensor([trg_indexes[-1]]).unsqueeze(0)
        output, hidden = decoder(trg_tensor, hidden)
        pred_token = output.argmax().item()
        trg_indexes.append(pred_token)
        if pred_token == english_word_to_idx['<EOS>']:
            break
    return ' '.join(english_vocab[idx] for idx in trg_indexes[1:-1])

test_sentence='你好，今天天气真好！'

print(translate(test_sentence,encoder_net,decoder_net))