from loader import load_data
import numpy as np


class SVM():
    def __init__(self, feature_size, class_num):
        sigma = 0.01
        self.W = sigma * np.random.randn(feature_size, class_num)

    def train(self, x, y, iteration=1000, batch_size=500, learning_rate=1e-5, reg=1e-5):
        for i in range(iteration):
            num_train = np.random.choice(x.shape[0], batch_size)
            x_batch = x[num_train]
            y_batch = y[num_train]
            dW = self._gradient(x_batch, y_batch, reg)
            self.W -= learning_rate * dW

    def _gradient(self, x, y, reg):
        dW = np.zeros_like(self.W)
        s = x.dot(self.W)
        s_yi = s[np.arange(x.shape[0]), y]
        margins = s - s_yi[:, np.newaxis] + 1
        margins = np.maximum(0, margins)
        margins[np.arange(x.shape[0]), y] = 0
        loss = np.sum(margins) / x.shape[0]
        loss += reg * np.sum(self.W * self.W)
        d = np.zeros_like(margins)
        d[margins > 0] = 1
        d[np.arange(x.shape[0]), y] = 0
        d[np.arange(x.shape[0]), y] = -np.sum(d, axis=1)
        dW = (1/x.shape[0]) * (x.T).dot(d)
        dW = dW + (2 * reg * self.W)
        return dW

    def predict(self, x):
        y = np.zeros(x.shape[0])
        s = x.dot(self.W)
        y = np.argmax(s, axis=1)
        return y


def main():
    train_data, train_label, test_data, test_label = load_data(5000, 1000)
    svm = SVM(train_data.shape[1], 10)
    svm.train(train_data, train_label, 1000)
    prediction = svm.predict(test_data)
    num_correct = np.sum(prediction == test_label)
    print("SVM")
    print(f"Correct:\t{num_correct} / {len(test_label)}")
    print(f"Accuracy:\t{num_correct / len(test_label)}")


if __name__ == "__main__":
    main()
