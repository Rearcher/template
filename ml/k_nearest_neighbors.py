"""k近邻"""
import heapq
import random
import time
from itertools import count

import numpy as np
from sklearn import datasets
from sklearn.metrics import accuracy_score
from sklearn.model_selection import train_test_split

counter = count()


def run_time(func):
    """用于记录程序运行时间的装饰器"""
    def wrapper(*args, **kw):
        begin_time = time.time()
        res = func(*args, **kw)
        print(f'{func.__name__} run time is {time.time() - begin_time:.2f}s')
        return res
    return wrapper


def euclidean_distance(a, b):
    """计算样本之间的欧几里得距离"""
    return np.linalg.norm(a - b)


class KNN:
    def __init__(self, k=3):
        self.k = k
        self.neighbors = []  # 用于保存kd树搜索过程中k个最近邻居的标签

    def _vote(self, neighbors):
        """投票算法，选取k个邻居中出现次数最多的类别"""
        counts = np.bincount(neighbors.astype('int'))
        return counts.argmax()

    def _build_kd_tree(self, data, depth):
        """建立kd树
        Args:
            data: 需要训练的数据
            depth: 当前建立的数的深度
        Returns:
            kd树的节点
        """
        data = np.array(data)
        n_samples = data.shape[0]
        if n_samples == 0:
            return None
        else:
            n_features = data.shape[1] - 1
            current_node = dict()
            current_node['split_axis'] = depth % n_features + 1

            data = sorted(data, key=lambda x: x[current_node['split_axis']])
            split_idx = n_samples // 2
            current_node['data'] = data[split_idx]
            current_node['left'] = self._build_kd_tree(data[:split_idx], depth + 1)
            current_node['right'] = self._build_kd_tree(data[split_idx+1:], depth + 1)
            return current_node

    def _search_tree(self, root, x):
        """搜索kd树
        Args:
            root: 开始搜索的树节点
            x: 需要判定类别的样本
        """
        if root is None:
            return

        split_axis = root['split_axis']
        if x[split_axis] < root['data'][split_axis]:
            self._search_tree(root['left'], x)
        else:
            self._search_tree(root['right'], x)

        heapq.heappush(self.neighbors, (-1 * euclidean_distance(x, root['data'][1:]), next(counter), root['data']))
        if len(self.neighbors) > self.k:
            heapq.heappop(self.neighbors)

        split_dist = abs(x[split_axis] - root['data'][split_axis])
        neighbor_max = -1 * heapq.nsmallest(1, self.neighbors)[0][0]
        if split_dist > neighbor_max:
            return

        if x[split_axis] < root['data'][split_axis]:
            self._search_tree(root['right'], x)
        else:
            self._search_tree(root['left'], x)

    @run_time
    def predict(self, X_train, y_train, X_test, kd_tree=False):
        """用训练集来预测测试集
        Args:
            X_train: 训练特征数据
            y_train: 训练标签数据
            X_test: 测试特征数据
            kd_tree: True代表使用kd树搜索，False代表使用线性扫描
        Returns
            pred: 针对X_test的预测结果
        """
        pred = np.empty(X_test.shape[0])
        if kd_tree:
            data = np.insert(X_train, 0, y_train, axis=1)
            n_features = np.array(data).shape[1]
            self.split_order = random.sample(range(1, n_features), n_features - 1)
            root = self._build_kd_tree(data, 0)
            for i, sample in enumerate(X_test):
                # print(f'processing sample {i + 1} / {len(X_test)}')
                self.neighbors.clear()
                self._search_tree(root, sample)
                neighbors = np.array([x[0] for d, c, x in self.neighbors])
                pred[i] = self._vote(neighbors)
        else:
            for i, sample in enumerate(X_test):
                # print(f'processing sample {i + 1} / {len(X_test)}')
                idx = np.argsort([euclidean_distance(x, sample) for x in X_train])[:self.k]
                neighbors = np.array([y_train[j] for j in idx])
                pred[i] = self._vote(neighbors)
        return pred


def main():
    # 加载数据集，切分训练集和测试集
    digits = datasets.load_digits()
    X = digits.data
    y = digits.target
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=19)

    model = KNN(k=3)

    print('brute force search: ')
    pred = model.predict(X_train, y_train, X_test, kd_tree=False)
    print(f'accuracy = {accuracy_score(y_test, pred):.6f}\n')

    print('kd-tree search: ')
    pred = model.predict(X_train, y_train, X_test, kd_tree=False)
    print(f'accuracy = {accuracy_score(y_test, pred):.6f}')


if __name__ == '__main__':
    main()
