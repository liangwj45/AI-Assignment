from tqdm import tqdm
from torchvision import datasets, transforms
from torch.utils.data import DataLoader
from torch.autograd import Variable
from torch import nn
import torchvision
import torch
import pickle


class Model(nn.Module):
    def __init__(self):
        super(Model, self).__init__()
        self.conv1 = nn.Sequential(nn.Conv2d(3, 16, 5, padding=2),   # 卷积
                                   nn.ReLU(),                        # 激活
                                   nn.MaxPool2d(2))                  # 池化
        self.conv2 = nn.Sequential(nn.Conv2d(16, 32, 5, padding=2),  # 卷积
                                   nn.ReLU(),                        # 激活
                                   nn.MaxPool2d(2))                  # 池化
        self.out = nn.Sequential(nn.Linear(8*8*32, 10))              # 全连接

    def forward(self, x):
        x = self.conv1(x)
        x = self.conv2(x)
        x = x.view(x.shape[0], 8*8*32)  # 压缩扁平化处理
        x = self.out(x)
        return x


if __name__ == "__main__":
    # 加载数据
    transform = transforms.Compose([
        transforms.RandomCrop(32, padding=4),
        transforms.RandomHorizontalFlip(),
        transforms.ToTensor(),
        transforms.Normalize((0.4914, 0.4822, 0.4465),
                             (0.2023, 0.1994, 0.2010)),
    ])
    data_train = datasets.CIFAR10(
        root="./dataset/", transform=transform, train=True, download=True)
    data_test = datasets.CIFAR10(
        root="./dataset/", transform=transform, train=False)
    data_loader_train = DataLoader(
        dataset=data_train, batch_size=200, shuffle=True)
    data_loader_test = DataLoader(
        dataset=data_test, batch_size=200, shuffle=True)

    # 建立模型
    model = Model()
    loss_func = nn.CrossEntropyLoss()
    optimizer = torch.optim.Adam(model.parameters(), lr=0.001)

    # 迭代
    n_epochs = 5
    print(f"Epochs: {n_epochs}")
    for epoch in range(n_epochs):
        # 使用训练集训练
        correct_train = 0
        total_loss = 0
        with tqdm(total=len(data_loader_train)) as pbar:
            for data in data_loader_train:
                # 对一个batch进行训练
                X_train, y_train = data
                X_train, y_train = Variable(X_train), Variable(y_train)
                outputs = model(X_train)
                # 反向传播误差
                loss = loss_func(outputs, y_train)
                optimizer.zero_grad()
                loss.backward()
                optimizer.step()
                # 记录训练集准确率
                total_loss += loss
                _, pred = torch.max(outputs.data, 1)
                correct_train += torch.sum(pred == y_train.data)
                # 打印进度条信息
                pbar.set_description(
                    'Epoch: %d | train loss: %.4f' % (epoch + 1, loss.data.numpy()))
                pbar.update(1)

        # 使用测试集测试
        correct_test = 0
        with tqdm(total=len(data_loader_test)) as pbar:
            for data in data_loader_test:
                # 对一个batch进行预测
                X_test, y_test = data
                X_test, y_test = Variable(X_test), Variable(y_test)
                outputs = model(X_test)
                # 记录测试集准确率
                _, pred = torch.max(outputs.data, 1)
                correct_test += torch.sum(pred == y_test.data)
                # 打印进度条信息
                pbar.set_description(f'Epoch: {epoch + 1} | test')
                pbar.update(1)

        # 打印迭代信息
        print("Loss is:{:.4f}, Train Accuracy is:{:.2f}%, Test Accuracy is:{:.2f}%".format(
            total_loss/len(data_train),
            100.0*correct_train/len(data_train),
            100.0*correct_test/len(data_test)))
