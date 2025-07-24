import math
import mindspore
from mindspore import nn, ops


class Encoder(nn.Cell):
    def __init__(self, d_model, d_ff, n_heads, n_encoder_layers):
        super().__init__()
        self.layers = nn.CellList([EncoderLayer(d_model, d_ff, n_heads) for _ in range(n_encoder_layers)])

    def construct(self, x):
        for layer in self.layers:
            x = layer(x)
        return x


class EncoderLayer(nn.Cell):
    def __init__(self, d_model, d_ff, n_heads):
        super().__init__()
        self.attn = MultiHeadAttention(d_model, d_model, d_model, n_heads)
        self.ffn = FeedForward(d_model, d_ff)
        self.norm = nn.LayerNorm((d_model,))

    def construct(self, x):
        x = self.norm(x + self.attn(x))
        x = self.norm(x + self.ffn(x))
        return x


class FeedForward(nn.Cell):
    def __init__(self, d_model, d_ff):
        super().__init__()
        self.linear1 = nn.Linear(d_model, d_ff)
        self.linear2 = nn.Linear(d_ff, d_model)
        self.relu = nn.ReLU()

    def construct(self, x):
        return self.linear2(self.relu(self.linear1(x)))


class MultiHeadAttention(nn.Cell):
    def __init__(self, embed_dim: int, attn_dim: int, output_dim: int, num_heads: int):
        super().__init__()
        self.embed_dim = embed_dim
        self.attn_dim = attn_dim
        self.output_dim = output_dim
        self.num_heads = num_heads
        self.head_dim = attn_dim // num_heads

        self.q_proj = nn.Linear(embed_dim, self.attn_dim, bias=False)
        self.k_proj = nn.Linear(embed_dim, self.attn_dim, bias=False)
        self.v_proj = nn.Linear(embed_dim, self.attn_dim, bias=False)

        self.out_proj = nn.Linear(self.attn_dim, self.output_dim, bias=False)

        self.softmax = nn.Softmax(axis=-1)

    def construct(self, x):
        batch_size, seq_len, embed_dim = x.shape

        q = self.q_proj(x)
        k = self.k_proj(x)
        v = self.v_proj(x)

        q = q.view(batch_size, seq_len, self.num_heads, self.head_dim).transpose(1, 2)
        k = k.view(batch_size, seq_len, self.num_heads, self.head_dim).transpose(1, 2)
        v = v.view(batch_size, seq_len, self.num_heads, self.head_dim).transpose(1, 2)

        attn_score = ops.matmul(q, k.transpose(-2, -1))
        q_k = k.shape[-1]
        attn_score = attn_score / ops.sqrt(mindspore.tensor(q_k))
        attn_weight = self.softmax(attn_score)

        o = ops.matmul(attn_weight, v)
        attn_out = o.transpose(1, 2).reshape(batch_size, seq_len, self.attn_dim)
        return self.out_proj(attn_out)


batch_size = 2
seq_len = 5
d_model = 512
vocab_size = 100

words_inputs = ops.randint(0, vocab_size, (batch_size, seq_len))
embedding = nn.Embedding(vocab_size, d_model)
embedding_outputs = embedding(words_inputs)

pe = ops.zeros((seq_len, d_model), dtype=mindspore.float32)
position = ops.arange(0, seq_len, dtype=mindspore.float32).unsqueeze(1)
div_term = ops.exp(ops.arange(0, d_model, 2).float() * (-math.log(10000.0) / d_model))
pe[:, 0::2] = ops.sin(position * div_term)
pe[:, 1::2] = ops.cos(position * div_term)

encoder_inputs = embedding_outputs + pe
encoder = Encoder(512, 2048, 8, 6)
encoder_outputs = encoder(encoder_inputs)
print(encoder_outputs)
