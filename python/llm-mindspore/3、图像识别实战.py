import mindspore
import mindspore.nn as nn
from mindspore.dataset import MnistDataset
from mindspore.dataset import transforms, vision
import mindspore.ops as ops

# 数据归一化
image_transform = transforms.Compose([
    vision.Rescale(1.0 / 255.0, 0),
    vision.Normalize(mean=[0.1307], std=[0.3081]),
    vision.HWC2CHW(),
    transforms.TypeCast(mindspore.float32)
])
label_transform = transforms.TypeCast(mindspore.int32)

# 下载mnist数据
train_data = MnistDataset(dataset_dir='./data/MINST', usage='train')
train_data = train_data.map(operations=image_transform, input_columns="image")
train_data = train_data.map(operations=label_transform, input_columns="label")
train_dataloader = train_data.batch(batch_size=16)

test_data = MnistDataset(dataset_dir='./data/MINST', usage='test')
test_data = test_data.map(operations=image_transform, input_columns="image")
test_data = test_data.map(operations=label_transform, input_columns="label")
test_dataloader = test_data.batch(batch_size=16)


# 建立模型
class MnistModel(nn.Cell):
    def __init__(self):
        super().__init__()
        self.fc1 = nn.Linear(28 * 28, 128)
        self.fc2 = nn.Linear(128, 256)
        self.fc3 = nn.Linear(256, 128)
        self.fc4 = nn.Linear(128, 10)
        self.relu = nn.ReLU()

    def construct(self, x):
        x = self.relu(self.fc1(x))
        x = self.relu(self.fc2(x))
        x = self.relu(self.fc3(x))
        x = self.fc4(x)
        return x


# 配置模型
model = MnistModel()
optimizer = nn.Adam(model.trainable_params(), learning_rate=0.001, weight_decay=1e-4)
criterion = nn.CrossEntropyLoss()

net_with_loss = nn.WithLossCell(model, criterion)
train_net = nn.TrainOneStepCell(net_with_loss, optimizer)

step = 10

# 训练
for _ in range(step):
    model.set_train()
    for i, (image, label) in enumerate(train_dataloader):
        image = image.view(-1, 28 * 28)
        train_net(image, label)
        if i % 250 == 0:
            loss = net_with_loss(image, label).asnumpy()
            print(f"step:{_ + 1}/{step}, data:{i + 250}/{len(train_dataloader)},loss:{loss}")

metric = nn.Accuracy()
metric.clear()

#评估模型
model.set_train(False)

for images, labels in test_dataloader:
    images = images.view(-1, 28 * 28)
    outputs = model(images)

    metric.update(outputs, labels)

accuracy = metric.eval()
print(f'测试的正确率为： {100 * accuracy}%')
