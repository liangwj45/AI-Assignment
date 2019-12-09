from collections import Counter
from loader import load_data
import numpy as np


class KNN:
    def __init__(self, train_data, train_label):
        self.train_data = train_data
        self.train_label = train_label

    def predict(self, test_data, k=6):
        distances = self._compute_distance(test_data)
        len_distances = distances.shape[0]
        prediction = np.zeros(len_distances)

        for i in range(len_distances):
            k_nearest_indices = np.argsort(distances[i])[:k]
            k_nearest_neighbors = self.train_label[k_nearest_indices]
            vote = Counter(k_nearest_neighbors)
            counter = vote.most_common()
            prediction[i] = counter[0][0]

        return prediction

    def _compute_distance(self, x):
        x2 = np.sum(x**2, axis=1).reshape(x.shape[0], 1)
        y2 = np.sum(self.train_data**2, axis=1)
        xy = x.dot(self.train_data.T)
        return np.sqrt(x2 + y2 - 2 * xy)


def main():
    train_data, train_label, test_data, test_label = load_data(5000, 1000)
    knn = KNN(train_data, train_label)
    prediction = knn.predict(test_data, 9)
    num_correct = np.sum(prediction == test_label)
    print("KNN")
    print(f"Correct:\t{num_correct} / {len(test_label)}")
    print(f"Accuracy:\t{num_correct / len(test_label)}")


if __name__ == "__main__":
    main()
