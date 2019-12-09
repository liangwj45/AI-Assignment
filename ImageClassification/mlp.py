from loader import load_data
import numpy as np


class MLP:
    def __init__(self, input_dim, hidden_dim, output_dim, std=1e-4, batch_size=200, iterations=1000, learning_rate=1e-3, reg=2e4):
        self.params = {"W1": std * np.random.randn(input_dim, hidden_dim), "b1": np.zeros(hidden_dim),
                       "W2": std * np.random.randn(hidden_dim, output_dim), "b2": np.zeros(output_dim)}
        self.batch_size = batch_size
        self.iterations = iterations
        self.learning_rate = learning_rate
        self.reg = reg

    def train(self, train_data, train_label):
        for i in range(self.iterations):
            batch_index = np.random.choice(
                train_data.shape[0], self.batch_size)
            train_data_batch, train_label_batch = train_data[batch_index], train_label[batch_index]
            gradient = self._gradient(
                train_data_batch, train_label_batch)
            self.params["W1"] -= self.learning_rate * gradient["W1"]
            self.params["b1"] -= self.learning_rate * gradient["b1"]
            self.params["W2"] -= self.learning_rate * gradient["W2"]
            self.params["b2"] -= self.learning_rate * gradient["b2"]

    def predict(self, x):
        output_h1 = x.dot(self.params["W1"]) + self.params["b1"]
        output_h1_relu = np.maximum(0, output_h1)
        output_h2 = output_h1_relu.dot(self.params["W2"]) + self.params["b2"]
        prediction = np.argmax(output_h2, axis=1)
        return prediction

    def _gradient(self, x, y):
        w1, b1 = self.params["W1"], self.params["b1"]
        w2, b2 = self.params["W2"], self.params["b2"]

        output_h1 = x.dot(w1) + b1
        output_h1_relu = np.maximum(0, output_h1)
        output_h2 = output_h1_relu.dot(w2) + b2
        scores = output_h2

        num_train = x.shape[0]
        scores -= scores.max()
        scores = np.exp(scores)
        scores_sums = np.sum(scores, axis=1)
        cors = scores[range(num_train), y]
        loss = -np.sum(np.log(cors / scores_sums)) / num_train + self.reg * (
            np.sum(w1 * w1) + np.sum(w2 * w2))

        gradient = {}
        s = np.divide(scores, scores_sums.reshape(num_train, 1))
        s[range(num_train), y] = - (scores_sums - cors) / scores_sums
        s /= num_train

        d_w2 = output_h1.T.dot(s)
        d_b2 = np.sum(s, axis=0)

        hidden = s.dot(w2.T)
        hidden[output_h1 == 0] = 0

        d_w1 = x.T.dot(hidden)
        d_b1 = np.sum(hidden, axis=0)

        gradient['W2'] = d_w2 + 2 * self.reg * w2
        gradient['b2'] = d_b2
        gradient['W1'] = d_w1 + 2 * self.reg * w1
        gradient['b1'] = d_b1
        return gradient


def main():
    train_data, train_label, test_data, test_label = load_data(5000, 1000)
    mlp = MLP(input_dim=train_data.shape[1], hidden_dim=100, output_dim=10,
              iterations=1000, learning_rate=1e-5, reg=1e-5)
    mlp.train(train_data, train_label)
    prediction = mlp.predict(test_data)
    num_correct = np.sum(prediction == test_label)
    print("MLP")
    print(f"Correct:\t{num_correct} / {len(test_label)}")
    print(f"Accuracy:\t{num_correct / len(test_label)}")


if __name__ == "__main__":
    main()
