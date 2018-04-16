"""线性回归"""
import matplotlib.pyplot as plt
import numpy as np
from sklearn import datasets


class LinearRegression:
    def __init__(self, n_iterations=1000, learning_rate=0.01, gradient_descent=True):
        """初始化.
        Args:
            n_iterations: 梯度下降算法的迭代次数.
            learning_rate: 梯度下降算法的学习速率.
            gradient_descent: True代表使用梯度下降算法求解，False代表使用normal equation求解.
        """
        self.n_iterationns = n_iterations
        self.learning_rate = learning_rate
        self.gradient_descent = gradient_descent

    def computeCost(self, X, y):
        """计算当前模型对于训练数据的损失(平方损失)
        Args:
            X: 训练数据中的特征
            y: 训练数据中的目标值

        Returns:
            当前模型对于训练数据的损失
        """
        n_samples = len(y)
        return (X.dot(self.theta) - y).T.dot(X.dot(self.theta) - y) / 2 / n_samples

    def fit(self, X, y):
        """用训练数据来训练模型
        Args:
            X: 训练数据中的特征
            y: 训练数据中的目标值

        Returns:
            theta: 线性回归模型的参数
            costHistory: 如果使用梯度下降算法求解，梯度下降算法过程中模型的历史损失会被返回
        """

        # 加入常量1作为偏置bias特征
        X = np.insert(X, 0, 1, axis=1)
        y = np.array(y).reshape(len(y), 1)
        n_samples, n_features = X.shape
        self.theta = np.zeros(n_features).reshape(n_features, 1)

        costHistory = np.zeros(self.n_iterationns)

        if not self.gradient_descent:
            # normal equation
            self.theta = np.linalg.pinv(X.T.dot(X)).dot(X.T).dot(y)
        else:
            for i in range(self.n_iterationns):
                tmp = X.T.dot(X.dot(self.theta) - y)
                self.theta -= tmp * self.learning_rate / n_samples
                costHistory[i] = self.computeCost(X, y)

        return self.theta, costHistory

    def predict(self, X):
        X = np.insert(X, 0, 1, axis=1)
        return X.dot(self.theta)


def test_linear_regression():
    # 加载数据
    diabetes = datasets.load_diabetes()

    diabetes_X = diabetes.data[:, np.newaxis, 2]
    diabetes_X_train = diabetes_X[:-20]
    diabetes_X_test = diabetes_X[-20:]

    diabetes_y_train = diabetes.target[:-20]
    diabetes_y_test = diabetes.target[-20:]

    # 使用线性回归模型
    model = LinearRegression(n_iterations=1000, learning_rate=0.05)
    theta, costHistory = model.fit(diabetes_X_train, diabetes_y_train)
    diabetes_y_pred_1 = model.predict(diabetes_X_test)

    # 通过查看模型损失值的变化，来判断梯度下降算法是否正常工作
    plt.plot(costHistory)
    plt.xlabel('iterations')
    plt.ylabel('cost')
    plt.show()

    model = LinearRegression(n_iterations=5000, learning_rate=0.05)
    model.fit(diabetes_X_train, diabetes_y_train)
    diabetes_y_pred_2 = model.predict(diabetes_X_test)

    model = LinearRegression(n_iterations=10000, learning_rate=0.05)
    model.fit(diabetes_X_train, diabetes_y_train)
    diabetes_y_pred_3 = model.predict(diabetes_X_test)

    model = LinearRegression(gradient_descent=False)
    model.fit(diabetes_X_train, diabetes_y_train)
    diabetes_y_pred_4 = model.predict(diabetes_X_test)

    # 比较不同迭代次数时模型对数据的拟合情况
    plt.scatter(diabetes_X_test, diabetes_y_test, color='black')
    plt.plot(diabetes_X_test, diabetes_y_pred_1, color='blue', linewidth=3, label='iterations=1000')
    plt.plot(diabetes_X_test, diabetes_y_pred_2, color='orange', linewidth=3, label='iterations=5000')
    plt.plot(diabetes_X_test, diabetes_y_pred_3, color='red', linewidth=3, label='iterations=10000')
    plt.plot(diabetes_X_test, diabetes_y_pred_4, color='purple', linewidth=3, label='normal equation')
    plt.legend()
    plt.show()


def main():
    test_linear_regression()


if __name__ == '__main__':
    main()
