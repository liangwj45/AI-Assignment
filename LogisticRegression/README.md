# HW3

> 数据科学与计算机学院 2017级 软件工程 教务二班 梁文杰 16303050

### 似然估计

在逻辑回归模型当中，引入了 Sigma 函数，将连续线性函数的值映射到 0-1 之间，并利用这个特性进行更好地解决二分类问题。
$$
\begin{align}
g(z)=\frac{1}{1+e^{-z}}\tag{1}
\end{align}
$$
 如果将上面的函数扩展到多维空间，并且加上参数，则函数变成： 
$$
\begin{align}
h_\theta(x)=g(\theta^Tx)=\frac{1}{1+e^{-\theta^Tx}}\tag{2}
\end{align}
$$
其中 $x$ 是变量，$\theta$ 是参数，$x_j$ 表示为 $x$ 向量的第 $j$ 个元素，$\theta^T$ 为矩阵 $\theta$ 的转置。

根据这个函数，可以得到对于一个样本的概率分布：
$$
\begin{align}
P(y=1|x;\theta)&=h_\theta(x)\\
P(y=0|x;\theta)&=1-h_\theta(x)
\end{align}\tag{3}
$$
综合为：
$$
\begin{align}
P(y|x;\theta)&=(h_\theta(x))^y(1-h_\theta(x))^{1-y}
\end{align}\tag{4}
$$
假设有 $n$ 个独立同分布的训练样本： $(x^{(i)}, y^{(i)})$ 表示为第 $i$ 个样本。

可以得到似然函数为：
$$
\begin{align}
L(\theta)&=P(Y|X;\theta)\\
&=\prod_iP(y^{(i)}|x^{(i)};\theta)\\
&=\prod_i(h_\theta(x^{(i)}))^{y^{(i)}}(1-h_\theta(x^{(i)}))^{1-y^{(i)}}
\end{align}\tag{5}
$$
对其求对数得：
$$
\begin{align}
l(\theta)=-lnL(\theta)=-\sum_{i=1}^n(y^{(i)}ln\,h(x^{(i)})+(1-y^{(i)})ln(1-h(x^{(i)})))
\end{align}\tag{6}
$$

### 梯度回传

使用梯度上升算法，求其最大值：
$$
\begin{align}
\frac{\partial}{\partial\theta_j}l(\theta)&=(y\frac{1}{g(\theta^Tx)}-(1-y)\frac{1}{1-g(\theta^Tx)})\frac{\partial}{\partial\theta_j}g(\theta^Tx)\\
&=(y\frac{1}{g(\theta^Tx)}-(1-y)\frac{1}{1-g(\theta^Tx)})g(\theta^Tx)(1-g(\theta^Tx))\frac{\partial}{\partial\theta_j}\theta^Tx\\
&=(y(1-g(\theta^Tx))-(1-y)g(\theta^Tx))x_j\\
&=(y-h_\theta(x))x_j
\end{align}\tag{7}
$$
由于：
$$
\theta := \theta + \alpha\nabla_\theta l(\theta)\tag{8}
$$
所以最终得到：
$$
\begin{align}
\theta &:= \theta + \alpha\sum_{i=1}^n(y^{(i)}-h_\theta(x^{(i)}))x^{(i)}_j\\
&:= \theta + \alpha\sum_{i=1}^n(y^{(i)}-\frac{1}{1+e^{-\theta^Tx^{(i)}}})x^{(i)}_j
\end{align}\tag{9}
$$

其中 $\alpha$ 为学习率因子。
