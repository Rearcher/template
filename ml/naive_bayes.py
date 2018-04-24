"""朴素贝叶斯"""
import math

import numpy as np
from sklearn import datasets
from sklearn.metrics import accuracy_score


class NaiveBayes:
    def fit(self, X, y):
        """朴素贝叶斯算法
        假设条件概率p(x|y)符合高斯分布
        为每一类的样本中特征的每一个维度拟合一个高斯分布

        Args:
            X: 训练特征
            y: 训练标签
        """
        self.X, self.y = X, y
        self.classes = np.unique(y)
        self.parameters = []

        for i, c in enumerate(self.classes):
            tmp_X = X[np.where(y == c)]
            self.parameters.append([])
            for col in tmp_X.T:
                parameters = {"mean": col.mean(), "var": col.var()}
                self.parameters[i].append(parameters)

    def _calculate_priori(self, c):
        """根据训练数据计算每一类的先验概率"""
        tmp_X = self.X[np.where(self.y == c)]
        return len(tmp_X) / len(self.X)

    def _calculate_likelihood(self, mean, var, x):
        """计算条件概率"""
        eps = 1e-4
        coef = 1.0 / math.sqrt(2.0 * math.pi * var + eps)
        exponent = math.exp(-math.pow(x - mean, 2) / (2 * var + eps))
        return coef * exponent

    def _classify(self, sample):
        """采用最大后验概率来分类"""
        posteriors = []
        for i, c in enumerate(self.classes):
            posterior = self._calculate_priori(c)
            for feature_value, params in zip(sample, self.parameters[i]):
                likelihood = self._calculate_likelihood(params['mean'], params['var'], feature_value)
                posterior *= likelihood
            posteriors.append(posterior)
        return self.classes[np.argmax(posteriors)]

    def predict(self, X):
        pred = [self._classify(x) for x in X]
        return pred


def main():
    model = NaiveBayes()
    iris = datasets.load_iris()

    model.fit(iris.data, iris.target)
    y_pred = model.predict(iris.data)
    print(f'accuracy = {accuracy_score(iris.target, y_pred)}')


if __name__ == '__main__':
    main()
