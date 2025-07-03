import mindspore
import mindspore.nn as nn
from mindspore.dataset import MnistDataset
from mindspore.dataset import transforms, vision

image_transform = transforms.Compose([
    vision.Rescale(1.0 / 255.0, 0),
    vision.Normalize(mean=[0.1307], std=[0.3081]),
    vision.HWC2CHW(),
    transforms.TypeCast(mindspore.float32)
])
label_transform = transforms.TypeCast(mindspore.int32)

train_data = MnistDataset(dataset_dir='./data/MINST', usage='train')
train_data = train_data.map(operations=image_transform, input_columns="image")
train_data = train_data.map(operations=label_transform, input_columns="label")
train_dataloader = train_data.batch(batch_size=16)

test_data = MnistDataset(dataset_dir='./data/MINST', usage='test')
test_data = test_data.map(operations=image_transform, input_columns="image")
test_data = test_data.map(operations=label_transform, input_columns="label")
test_dataloader = test_data.batch(batch_size=16)


class CNNMnistModel(nn.Cell):
    def __init__(self):
        super().__init__()
        self.cov1 = nn.Conv2d(1, 32, kernel_size=3, stride=1, pad_mode='valid')
        self.cov2 = nn.Conv2d(32, 64, kernel_size=3, stride=1, pad_mode='valid')
        self.pool = nn.MaxPool2d(kernel_size=2, stride=2, pad_mode='valid')
        self.flatten = nn.Flatten()
        self.relu = nn.ReLU()
        self.fc1 = nn.Linear(64 * 5 * 5, 128)
        self.fc2 = nn.Linear(128, 10)

    def construct(self, x):
        x = self.pool(self.relu(self.cov1(x)))
        x = self.pool(self.relu(self.cov2(x)))
        x = self.flatten(x)
        x = self.relu(self.fc1(x))
        x = self.fc2(x)
        return x


model = CNNMnistModel()
optimizer = nn.Adam(model.trainable_params(), learning_rate=0.001)
criterion = nn.CrossEntropyLoss()

net_with_loss = nn.WithLossCell(model, criterion)
tran_net = nn.TrainOneStepCell(net_with_loss, optimizer)

step = 10

for _ in range(step):
    model.set_train()
    for i, (images, labels) in enumerate(train_dataloader):
        tran_net(images, labels)
        if i % 250 == 0:
            loss = net_with_loss(images, labels).asnumpy()
            print(f"step:{_ + 1}/{step}, data:{i + 250}/{len(train_dataloader)},loss:{loss}")

metric = nn.Accuracy()
metric.clear()

model.set_train(False)

for images, labels in test_dataloader:
    outputs = model(images)

    metric.update(outputs, labels)

accuracy = metric.eval()
print(f'测试的正确率为： {100 * accuracy}%')
