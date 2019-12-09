from typing import List
import numpy as np
from scipy import stats
from scipy.special import comb, perm


def maximum_likelihood(observations, coins):
    prior_a = (observations * (coins - 1)).sum() / (coins - 1).sum()
    prior_b = (observations * coins).sum() / coins.sum()
    return [prior_a, prior_b]


def expectation_maximization(observations, priors, iterations=10000, tolerance=1e-6):
    for iteration in range(iterations):
        new_priors = train_iteration(observations, priors)
        delta_a = np.abs(new_priors[0] - priors[0])
        delta_b = np.abs(new_priors[1] - priors[1])
        print("iteration %3d / %3d: (%f, %f)\tdelta: (%f, %f)" %
              (iteration, iterations, new_priors[0], new_priors[1], delta_a, delta_b))
        if delta_a < tolerance and delta_b < tolerance:
            return new_priors
        priors = new_priors
    return priors


def train_iteration(observations, priors):
    theta_a = priors[0]
    theta_b = priors[1]

    # E 步骤
    e_h = np.array([0, 0])
    e_t = np.array([0, 0])
    for observation in observations:
        # 统计该次试验硬币正反面次数
        n = observation.size
        h_i = observation.sum()
        t_i = observation.size - h_i
        # 计算该次试验分别是硬币A或硬币B的概率
        p_a = comb(n, h_i) * theta_a**h_i * (1-theta_a)**t_i
        p_b = comb(n, h_i) * theta_b**h_i * (1-theta_b)**t_i
        pp = np.array([p_a, p_b]) / (p_a + p_b)
        # 计算期望
        e_h = e_h + pp * h_i
        e_t = e_t + pp * t_i

    # M 步骤
    theta_a = e_h[0] / (e_h[0] + e_t[0])
    theta_b = e_h[1] / (e_h[1] + e_t[1])

    return [theta_a, theta_b]


def main():
    # 用1代表正面，0代表反面
    observations = np.array([
        [1, 0, 0, 0, 1, 1, 0, 1, 0, 1],
        [1, 1, 1, 1, 0, 1, 1, 1, 1, 1],
        [1, 0, 1, 1, 1, 1, 1, 0, 1, 1],
        [1, 0, 1, 0, 0, 0, 1, 1, 0, 0],
        [0, 1, 1, 1, 0, 1, 1, 1, 0, 1]
    ])

    # 用0表示硬币A，1表示硬币B
    coins = np.array([
        [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    ])

    # 最大似然
    priors = maximum_likelihood(observations, coins)
    print("maximum likelihood:", priors)

    # 最大期望
    priors = [0.6, 0.5]
    priors = expectation_maximization(observations, priors, 100, 1e-6)
    print("expectation maximization: [%.6f, %.6f]" % (priors[0], priors[1]))


if __name__ == "__main__":
    main()
