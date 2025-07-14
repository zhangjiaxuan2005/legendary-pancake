import mindspore
from mindspore import nn, Model, Callback, ops
from mindspore.dataset import GeneratorDataset
from mindspore.nn import Adam

text = """
臣密言：臣以险衅，夙遭闵凶。生孩六月，慈父见背；行年四岁，舅夺母志。
祖母刘愍臣孤弱，躬亲抚养。
臣少多疾病，九岁不行，零丁孤苦，至于成立。
既无伯叔，终鲜兄弟，门衰祚薄，晚有儿息。
外无期功强近之亲，内无应门五尺之僮，茕茕孑立，形影相吊。
而刘夙婴疾病，常在床蓐，臣侍汤药，未曾废离。
"""

words = set(text)
vocab_size = len(words)
word_to_index = {word: i for i, word in enumerate(words)}
index_to_word = {i: word for i, word in enumerate(words)}

SEQ_LEN = 5
BATCH_SIZE = 1
HIDDEN_SIZE = 128
EMBEDDING_SIZE = 128


def text_generator(text, seq_len):
    data = [word_to_index[ch] for ch in text]
    for i in range(len(data) - seq_len):
        input_seq = data[i:i + seq_len]
        target_seq = data[i + 1:i + seq_len + 1]
        yield mindspore.tensor(input_seq, dtype=mindspore.int32), mindspore.tensor(target_seq, dtype=mindspore.int32)


dataset = GeneratorDataset(source=text_generator(text, seq_len=SEQ_LEN), column_names=['input', 'target'])
train_loader = dataset.batch(batch_size=BATCH_SIZE, drop_remainder=True)


class RNN(nn.Cell):
    def __init__(self, vocab_size, input_size, hidden_size):
        super().__init__()
        self.hidden_size = hidden_size
        self.embedding = nn.Embedding(input_size, hidden_size)
        self.rnn = nn.RNN(hidden_size, hidden_size, batch_first=True)
        self.out_linear = nn.Linear(hidden_size, vocab_size)

    def construct(self, x, hidden=None):
        embedding = self.embedding(x)
        outputs, hidden = self.rnn(embedding, hidden)
        outputs = self.out_linear(outputs)
        outputs = outputs.transpose(0, 2, 1)
        return outputs, hidden


class LossMonitor(Callback):
    def step_end(self, run_context):
        cb_params = run_context.original_args()
        current_step = (cb_params.cur_epoch_num - 1) * cb_params.batch_num + cb_params.cur_step_num
        print(f"Step: {current_step}, Loss: {cb_params.net_outputs.asnumpy():.6f}")


class CustomCrossEntropyLoss(nn.CrossEntropyLoss):
    def construct(self, logits, labels):
        return super().construct(logits[0], labels)


net = RNN(vocab_size, EMBEDDING_SIZE, HIDDEN_SIZE)
criterion = CustomCrossEntropyLoss()
optimizer = Adam(net.trainable_params(), learning_rate=0.001)

model = Model(net, loss_fn=criterion, optimizer=optimizer)

model.train(100, train_loader, callbacks=[LossMonitor()])


def generate_text(context, step, temperature=0.8):
    words = [word for word in context]
    hidden = None
    for _ in range(step):
        input_chars = words[-SEQ_LEN:] if len(words) >= SEQ_LEN else words
        input_seq = mindspore.tensor([word_to_index[ch] for ch in input_chars], mindspore.int32)
        input_seq = input_seq.view(1, -1)

        output, hidden = net(input_seq, hidden)
        last_output = output[0, :, -1]
        probs = ops.softmax(last_output / temperature, axis=-1)
        result_index = ops.multinomial(probs, 1).item()
        result = index_to_word[result_index]
        words.append(result)
    return ''.join(words)


print(generate_text('臣以险衅，夙遭', 5, 0.1))
