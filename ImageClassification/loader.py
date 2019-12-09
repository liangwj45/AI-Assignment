import os
import pickle
import numpy as np


def load_data(train_size=50000, test_size=10000):
    train_data = []
    train_label = []
    for batch in range(1, 6):
        with open(f"./datasets/data_batch_{batch}", "rb") as f:
            data = pickle.load(f, encoding='bytes')
        train_data.append(data[b'data'])
        train_label.append(data[b'labels'])

    test_data = []
    test_label = []
    with open("./datasets/test_batch", 'rb') as f:
        data = pickle.load(f, encoding='bytes')
        test_data.append(data[b'data'])
        test_label.append(data[b'labels'])

    train_data = np.array(train_data).reshape(50000, -1)[:train_size] / 255
    train_label = np.array(train_label).reshape(-1)[:train_size]
    test_data = np.array(test_data).reshape(10000, -1)[:test_size] / 255
    test_label = np.array(test_label).reshape(-1)[:test_size]
    print("dataset")
    print("train_data shape:", train_data.shape)
    print("train_label shape:", train_label.shape)
    print("test_data shape:", test_data.shape)
    print("test_label shape:", test_label.shape)
    return train_data, train_label, test_data, test_label
