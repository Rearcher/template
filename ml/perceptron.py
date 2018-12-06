"""感知机"""
import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D
from sklearn.metrics import accuracy_score, precision_score, recall_score
from tqdm import tqdm


def sign(x):
    """符号函数"""
    if x >= 0:
        return 1
    return -1


def genearte_f():
    """随机生成三维中的一个平面，并返回其参数"""
    w = -5 + 10 * np.random.random([3, 1])
    b = -5 + 10 * np.random.rand()

    def f(x):
        return np.vdot(w, x) + b
    return f, w, b


def generate_data(f):
    """随机生成数据"""
    n, m = 100, 3
    X = -5 + 10 * np.random.random([n, m])

    y = []
    for i in range(n):
        y.append(sign(f(X[i].reshape(3, 1))))
    return X, np.array(y)


def show(X, y, w, b, w1, b1):
    """画图展示拟合效果"""
    pos_samples, neg_samples = [], []
    n, m = X.shape
    for i in range(n):
        if y[i] == 1:
            pos_samples.append(list(X[i]))
        else:
            neg_samples.append(list(X[i]))
    pos_samples, neg_samples = np.array(pos_samples), np.array(neg_samples)

    ax = plt.subplot(111, projection='3d')
    ax.scatter(pos_samples[:,0], pos_samples[:,1], pos_samples[:,2], c='b')
    ax.scatter(neg_samples[:,0], neg_samples[:,1], neg_samples[:,2], c='r')

    x1 = np.arange(-10, 10, 0.25)
    x2 = np.arange(-10, 10, 0.25)
    x1, x2 = np.meshgrid(x1, x2)
    ax.plot_surface(x1, x2, (-b - w[0][0] * x1 - w[1][0] * x2) / w[2][0], alpha=0.5, color='y')
    ax.plot_surface(x1, x2, (-b1 - w1[0][0] * x1 - w1[1][0] * x2) / w1[2][0], alpha=0.5, color='g')
    plt.show()


class Perceptron:
    def __init__(self):
        pass

    def fit(self, X, y, n_iterations=1000, learning_rate=1):
        """感知机训练算法的原始形式
        Args:
            X: 输入的特征
            y: 输入的标签{-1, 1}
            n_iterations: 算法迭代次数
            learning_rate: 学习速率
        """
        n, m = X.shape
        self.w, self.b = np.zeros((3, 1)), 0

        for i in tqdm(range(n_iterations)):
            idx = np.random.randint(0, n)
            if y[idx] * (np.vdot(self.w, X[idx].reshape(3, 1)) + self.b) <= 0:
                self.w += learning_rate * y[idx] * X[idx].reshape(3, 1)
                self.b += learning_rate * y[idx]

    def fit_dual(self, X, y, n_iterations=1000, learning_rate=1):
        """感知机训练算法的对偶形式"""
        n, m = X.shape
        self.alpha, self.b = np.zeros((n, 1)), 0
        self.gram = np.zeros((n, n))

        # 计算Gram相关性矩阵
        for i in range(0, n):
            self.gram[i][i] = 1
            for j in range(i + 1, n):
                self.gram[i][j] = self.gram[j][i] = np.vdot(X[i].reshape(3, 1), X[j].reshape(3, 1))

        for i in tqdm(range(n_iterations)):
            idx = np.random.randint(0, n)
            if y[idx] * (sum(self.alpha * y * self.gram[:, idx].reshape(-1, 1)) + self.b) <= 0:
                self.alpha[idx][0] += learning_rate
                self.b += learning_rate * y[idx]
        self.w = sum(self.alpha * y * X).reshape(-1, 1)

    def predict(self, X):
        """预测"""
        y = (np.dot(X, self.w) + self.b).reshape(-1, 1)
        n, _ = y.shape
        for i in range(n):
            y[i][0] = sign(y[i][0])
        return y


def main():
    f, w, b = genearte_f()
    X, y = generate_data(f)

    model = Perceptron()
    model.fit(X, y)
    y_pred = model.predict(X)

    print(accuracy_score(y, y_pred))
    print(precision_score(y, y_pred))
    print(recall_score(y, y_pred))
    show(X, y, w, b, model.w, model.b)


if __name__ == '__main__':
    main()
