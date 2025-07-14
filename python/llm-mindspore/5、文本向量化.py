import mindspore
from mindspore import nn
from mindspore.dataset import GeneratorDataset
from mindspore.nn import optim


def generate_training_data(sentences, vocabulary, window_size):
    center_words = []
    target_words = []
    for sentence in sentences:
        indices = [vocabulary[word] for word in sentence]

        for center_index in range(len(indices)):
            start = max(0, center_index - window_size)
            end = min(len(indices), center_index + window_size + 1)

            for context_index in range(start, end):
                if context_index != center_index:
                    center_words.append(indices[center_index])
                    target_words.append(indices[context_index])

    return mindspore.tensor(center_words, mindspore.int32), mindspore.tensor(target_words, mindspore.int32)


class SkipGramNet(nn.Cell):
    def __init__(self, vocab_size, embedding_dim):
        super().__init__()
        self.input_embeddings = nn.Embedding(vocab_size, embedding_dim)
        self.output_embeddings = nn.Linear(embedding_dim, vocab_size)

    def construct(self, center_word):
        hidden = self.input_embeddings(center_word)
        return self.output_embeddings(hidden)


class SkipModel():
    def __init__(self, texts):
        self.texts = texts
        self.window_size = 2
        self.embedding_dim = 10
        self.batch_size = 10
        self.sentences, self.vocabulary = self._preprocess_data()
        self.center_words, self.target_words = self._generate_training_data()
        self.dataloader = self._create_dataloader()
        self.net, self.loss_fn, self.optimizer = self._init_model()
        self.model = self._init_train_model()
        self._train_model()
        self._print_word_vectors()

    def _preprocess_data(self):
        sentences = [text.split() for text in self.texts]
        vocabulary = {}
        for sentence in sentences:
            for word in sentence:
                if word not in vocabulary:
                    vocabulary[word] = len(vocabulary)
        return sentences, vocabulary

    def _generate_training_data(self):
        return generate_training_data(self.sentences, self.vocabulary, self.window_size)

    def _create_dataloader(self):
        dataset = GeneratorDataset(
            list(zip(self.center_words, self.target_words)),
            column_names=['center', 'target']
        )
        return dataset.batch(batch_size=self.batch_size)
    def _init_model(self):
        vocab_size = len(self.vocabulary)
        net = SkipGramNet(vocab_size, self.embedding_dim)
        loss_fn = nn.CrossEntropyLoss()
        optimizer = optim.Adam(net.trainable_params(), learning_rate=0.01)
        return net, loss_fn, optimizer

    def _init_train_model(self):
        return mindspore.Model(self.net, self.loss_fn, self.optimizer)

    def _train_model(self):
        self.model.train(10, self.dataloader)

    def _print_word_vectors(self):
        word_vectors = self.net.input_embeddings.embedding_table
        return word_vectors.asnumpy()

texts=[
    "I love natural language processing.",
    "I love machine learning.",
    "I love coding in Python and Java.",
    "I love Java.",
    "I love Java, I don't love C++.",
    "I don't love Java."
]
model = SkipModel(texts)
print(model._print_word_vectors())