import math

import numpy as np
from sklearn import datasets
from sklearn.metrics import accuracy_score
from sklearn.model_selection import train_test_split


class TreeNode:
    def __init__(self, feature_idx=None, threshold=None, target=None, target_proba=None, left_child=None, right_child=None):
        self.feature_idx = feature_idx
        self.threshold = threshold
        self.left_child = left_child
        self.right_child = right_child
        self.target = target
        self.target_proba = target_proba


class DecisionTree:
    def __init__(self, min_samples_split=2, min_info_gain=1e-7, max_depth=float("inf")):
        self.root = None
        self.min_samples_split = min_samples_split
        self.min_info_gain = min_info_gain
        self.max_depth = max_depth

    def _entropy(self, y):
        """计算信息熵"""
        log2 = lambda x: math.log(x) / math.log(2)
        entropy = 0
        for label in np.unique(y):
            count = len(y[y == label])
            p = count / len(y)
            entropy += -p * log2(p)
        return entropy

    def _info_gain(self, y, y1, y2):
        """计算信息增益"""
        p = len(y1) / len(y)
        entropy = self._entropy(y)
        info_gain = entropy - p * self._entropy(y1) - (1 - p) * self._entropy(y2)
        return info_gain

    def _leaf_calculation(self, y):
        """计算叶子节点对应的标签、对应标签的概率"""
        proba = {}
        max_proba, max_label = 0, None
        for label in np.unique(y):
            count = len(y[y == label])
            proba[label] = count / len(y)
            if proba[label] > max_proba:
                max_proba = proba[label]
                max_label = label
        return max_label, proba
                
    def _data_split(self, X, feature_idx, threshold):
        """将数据集根据第feature_idx个特征分成两部分：该特征值小于等于threshold的分为一部分，剩下的为另一部分"""
        f = lambda x: x[feature_idx] <= threshold
        X1 = np.array([x for x in X if f(x)])
        X2 = np.array([x for x in X if not f(x)])
        return X1, X2

    def _build_tree(self, X, y, current_depth=0):
        """构建决策树"""
        n_samples, n_features = np.shape(X)
        
        if len(np.shape(y)) == 1:
            y = np.expand_dims(y, axis=1)

        Xy = np.concatenate((X, y), axis=1)

        largest_info_gain = 0
        cache = {}

        if n_samples >= self.min_samples_split and current_depth <= self.max_depth:
            for feature_idx in range(n_features):
                feature_values = np.unique(X[:, feature_idx])
                for threshold in feature_values:
                    Xy1, Xy2 = self._data_split(Xy, feature_idx, threshold)
                    if len(Xy1) > 0 and len(Xy2) > 0:
                        y1, y2 = Xy1[:, n_features:], Xy2[:, n_features:]
                        info_gain = self._info_gain(y, y1, y2)
                        if info_gain > largest_info_gain:
                            largest_info_gain = info_gain
                            cache = {
                                "feature_idx": feature_idx,
                                "threshold": threshold,
                                "leftX": Xy1[:, :n_features],
                                "lefty": Xy1[:, n_features:],
                                "rightX": Xy2[:, :n_features],
                                "righty": Xy2[:, n_features:]
                            }
        
        if largest_info_gain > self.min_info_gain:
            left_child = self._build_tree(cache["leftX"], cache["lefty"], current_depth + 1)
            right_child = self._build_tree(cache["rightX"], cache["righty"], current_depth + 1)
            return TreeNode(feature_idx=cache["feature_idx"], threshold=cache["threshold"], left_child=left_child, right_child=right_child)

        target, target_proba = self._leaf_calculation(y)
        return TreeNode(target=target, target_proba=target_proba)

    def _search_tree(self, x, proba=False, tree=None):
        """搜索树"""
        if tree is None:
            tree = self.root

        if tree.target is not None:
            return tree.target_proba if proba else tree.target

        feature_value = x[tree.feature_idx]
        child = tree.left_child if feature_value <= tree.threshold else tree.right_child
        return self._search_tree(x, proba, child)

    def fit(self, X, y):
        """训练决策树"""
        self.root = self._build_tree(X, y)

    def predict(self, X):
        """预测"""
        y_pred = [self._search_tree(x) for x in X]
        return y_pred

    def predict_proba(self, X):
        """预测概率"""
        y_pred = [self._search_tree(x, proba=True) for x in X]
        return y_pred


def main():
    data = datasets.load_iris()
    X, y = data.data, data.target
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2)

    model = DecisionTree()
    model.fit(X_train, y_train)
    y_pred = model.predict(X_test)
    accuracy = accuracy_score(y_test, y_pred)

    print(f'Accuracy = {accuracy}')


if __name__ == '__main__':
    main()
