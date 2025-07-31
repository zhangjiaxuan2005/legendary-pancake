import math
import mindspore
from mindspore import nn, ops, Callback, Model
from modelscope import MsDataset
from mindspore.dataset import GeneratorDataset
from modelscope import AutoTokenizer

tokenizer = AutoTokenizer.from_pretrained('tiansz/bert-base-chinese')
vocab_size = len(tokenizer)

ds_train = MsDataset.load('DAMO_NLP/jd', subset_name='default', split='train')


def filter_condition(x):
    return isinstance(x['sentence'], str) and x['label'] is not None and not math.isnan(x['label'])


filtered_data = [data for data in ds_train if filter_condition(data)]

train_data = list(filtered_data[:200])


def text_classification_generator(data, max_seq_len):
    for item in data:
        sentence = item['sentence']
        if isinstance(sentence, bytes):
            sentence = sentence.decode('utf-8')
        # 使用 tokenizer 进行编码
        encoding = tokenizer.encode_plus(
            sentence,
            add_special_tokens=True,
            max_length=max_seq_len,
            truncation=True,
            padding='max_length',
            return_tensors='np'
        )
        input_ids = mindspore.Tensor(encoding['input_ids'], dtype=mindspore.int32).squeeze(0)
        segment_ids = mindspore.Tensor(encoding['token_type_ids'], dtype=mindspore.int32).squeeze(0)
        segment_ids = ops.clip_by_value(segment_ids, 0, 1)
        label = mindspore.Tensor(int(item['label']), dtype=mindspore.int32)
        yield input_ids, segment_ids, label


max_seq_len = 100
dataset = GeneratorDataset(source=text_classification_generator(train_data, max_seq_len),
                           column_names=['input_ids', 'segment_ids', 'label'])


def combine_inputs(input_ids, segment_ids, label):
    return (input_ids, segment_ids), label


dataset = dataset.map(operations=combine_inputs, input_columns=['input_ids', 'segment_ids', 'label'],
                      output_columns=['inputs', 'label'])

dataloader = dataset.batch(batch_size=32)

d_model = 64
d_ff = d_model * 2
n_heads = 2
n_encoder_layers = 2


class BertModel(nn.Cell):
    def __init__(self, vocab_size, max_seq_len):
        super().__init__()
        self.token_embedding = nn.Embedding(vocab_size, d_model)
        self.position_embedding = nn.Embedding(max_seq_len, d_model)
        self.segment_embedding = nn.Embedding(2, d_model)
        self.encoder = nn.TransformerEncoder(
            nn.TransformerEncoderLayer(d_model, n_heads, d_ff),
            n_encoder_layers
        )
        self.nsp_head = nn.SequentialCell(
            nn.Linear(d_model, 2)
        )

    def construct(self, input_ids, segment_ids):
        batch_size, seq_len = input_ids.shape

        token_embedding = self.token_embedding(input_ids)

        pos_ids = ops.arange(0, seq_len).unsqueeze(0).tile((batch_size, 1))

        pos_ids = ops.clip_by_value(pos_ids, 0, self.position_embedding.vocab_size - 1)
        pos_embeddings = self.position_embedding(pos_ids)

        segment_ids = ops.clip_by_value(segment_ids, 0, 1)
        segment_embedding = self.segment_embedding(segment_ids)
        embeddings = token_embedding + pos_embeddings + segment_embedding

        encoder_output = self.encoder(embeddings)
        cls_output = encoder_output[:, 0, :]

        nsp_output = self.nsp_head(cls_output)

        return nsp_output


class BertModelWrapper(nn.Cell):
    def __init__(self, bert_model):
        super().__init__()
        self.bert_model = bert_model

    def construct(self, inputs):
        input_ids = inputs[:, 0, :]
        segment_ids = inputs[:, 1, :]
        return self.bert_model(input_ids, segment_ids)


class LossMonitor(Callback):
    def step_end(self, run_context):
        cb_params = run_context.original_args()
        current_step = (cb_params.cur_epoch_num - 1) * cb_params.batch_num + cb_params.cur_step_num

        print(f"Step: {current_step}, Loss: {cb_params.net_outputs.asnumpy():.6f}")


net = BertModel(vocab_size, max_seq_len)
wrapped_net = BertModelWrapper(net)
criterion = nn.CrossEntropyLoss()

lr = nn.CosineDecayLR(min_lr=0.00000001, max_lr=0.0001, decay_steps=250*len(dataloader))
optimizer = nn.Adam(wrapped_net.trainable_params(), learning_rate=lr)


model = Model(wrapped_net, loss_fn=criterion, optimizer=optimizer)
model.train(100, dataloader, callbacks=[LossMonitor()])

text = '这个商品真好'
encoding = tokenizer.encode_plus(
    text,
    add_special_tokens=True,
    max_length=128,
    truncation=True,
    padding='max_length',
    return_tensors='np'
)

input_ids = mindspore.Tensor(encoding['input_ids'], dtype=mindspore.int32)
segment_ids = mindspore.Tensor(encoding['token_type_ids'], dtype=mindspore.int32)
segment_ids = ops.clip_by_value(segment_ids, 0, 1)

inputs = mindspore.ops.stack([input_ids, segment_ids], axis=1)

outputs = model.predict(inputs)

predicted = mindspore.ops.argmax(mindspore.ops.softmax(outputs, axis=1), dim=1)

print("Predicted label:", predicted.asnumpy())
