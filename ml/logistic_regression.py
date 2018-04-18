"""逻辑回归"""
import numpy as np
from sklearn import datasets
from sklearn.metrics import accuracy_score, precision_score, recall_score
from sklearn.model_selection import train_test_split


class LogisticRegression:
    def sigmoid(self, z):
        """sigmoid函数"""
        g = 1 / (1 + np.exp(-z))
        return g

    def costFunction(self, X, y):
        """损失函数
        Args:
            X: 训练数据
            y: 标签数据

        Returns:
            J: 模型当前的损失
            grad: 损失函数的梯度
        """
        n_samples = len(y)
        h = self.sigmoid(X.dot(self.theta))
        J = (1 / n_samples) * (-1 * y.T.dot(np.log(h)) - (1 - y).T.dot(np.log(1 - h)))
        grad = (1 / n_samples) * X.T.dot(h - y)
        return J, grad

    def fit(self, X, y, n_iterations=1000):
        """训练模型
        Args:
            X: 训练数据
            y: 标签数据
            n_iterations: 梯度下降算法迭代次数
        """
        n_features = X.shape[1]
        self.theta = np.zeros([n_features, 1])
        for i in range(n_iterations):
            J, grad = self.costFunction(X, y)
            self.theta -= grad

    def predict(self, X):
        """用模型进行预测"""
        y_pred = np.round(self.sigmoid(X.dot(self.theta))).astype(int)
        return y_pred


def main():
    # 使用sklearn自带的测试数据集
    iris = datasets.load_iris()
    X = iris.data[:100]
    y = np.array(iris.target[:100]).reshape(100, 1)
    # 分割训练集和测试集
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=19)

    # 用训练集训练模型，用测试集测试模型
    model = LogisticRegression()
    model.fit(X_train, y_train)
    y_pred = model.predict(X_test)

    # 计算模型的各项评分
    accuracy = accuracy_score(y_test, y_pred)
    precision = precision_score(y_test, y_pred)
    recall = recall_score(y_test, y_pred)
    print(f'accuracy {accuracy}, precision {precision}, recall {recall}')


if __name__ == '__main__':
    main()
