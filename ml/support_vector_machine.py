"""支持向量机"""
import numpy as np
import os
from sklearn.metrics import precision_score, recall_score, accuracy_score


class SVM:
    def __init__(self):
        pass

    def _rbf_kernel(self, x1, x2, gamma):
        """径向基核函数"""
        distance = np.linalg.norm(x1 - x2) ** 2
        return np.exp(-gamma * distance)

    def _cal_E_i(self, i):
        """计算Ei，注意只用到支持向量"""
        alpha = self.alpha[self.alpha > 0].reshape(-1, 1)
        y = self.y[self.alpha > 0].reshape(-1, 1)
        Ki = self.K[i].reshape(-1, 1)[self.alpha > 0].reshape(-1, 1)
        return np.dot((alpha * y).T, Ki) + self.b

    def _select_j(self, i):
        """SMO算法的第二层循环，根据选择的第一个点来选择第二个点"""
        max_delta_E, j = 0, -1
        n, _ = self.X.shape
        for k in range(n):
            if k == i:
                continue
            delta_E = abs(self.E[i, 0] - self.E[k, 0])
            if delta_E > max_delta_E:
                max_delta_E = delta_E
                j = k
        return j

    def _update(self, i, j):
        """两个变量的二次规划算法"""
        alpha_i_old, alpha_j_old = self.alpha[i, 0], self.alpha[j, 0]
        if self.y[i, 0] != self.y[j, 0]:
            L = max(0, self.alpha[j, 0] - self.alpha[i, 0])
            H = min(self.C, self.C + self.alpha[j, 0] - self.alpha[i, 0])
        else:
            L = max(0, self.alpha[i, 0] + self.alpha[j, 0] - self.C)
            H = min(self.C, self.alpha[i, 0] + self.alpha[j, 0])
        if L == H:
            return 0

        eta = self.K[i, i] + self.K[j, j] - 2 * self.K[i, j]
        if eta < 0:
            return 0

        alpha_j_new = alpha_j_old + self.y[j, 0] * (self.E[i, 0] - self.E[j, 0]) / eta
        if alpha_j_new > H:
            self.alpha[j, 0] = H
        elif alpha_j_new < L:
            self.alpha[j, 0] = L
        else:
            self.alpha[j, 0] = alpha_j_new
        if abs(self.alpha[j, 0] - alpha_j_old) < 1e-5:
            return 0

        self.alpha[i, 0] = alpha_i_old + self.y[i, 0] * self.y[j, 0] * (alpha_j_old - self.alpha[j, 0])
        b1 = self.b - self.E[i, 0] - self.y[i, 0] * self.K[i, i] * (self.alpha[i, 0] - alpha_i_old) \
                - self.y[j, 0] * self.K[j, i] * (self.alpha[j, 0] - alpha_j_old)
        b2 = self.b - self.E[j, 0] - self.y[i, 0] * self.K[i, j] * (self.alpha[i, 0] - alpha_i_old) \
                - self.y[j, 0] * self.K[j, j] * (self.alpha[j, 0] - alpha_j_old)
        if self.alpha[i, 0] > 0 and self.alpha[i, 0] < self.C:
            self.b = b1
        elif self.alpha[j, 0] > 0 and self.alpha[j, 0] < self.C:
            self.b = b2
        else:
            self.b = (b1 + b2) / 2
        
        self.E[i, 0] = self._cal_E_i(i)[0]
        self.E[j, 0] = self._cal_E_i(j)[0]        
        
        return 1
                
    def fit(self, X, y, C=1.0, gamma='auto', kernel='rbf', n_iteration=1000, tol=1e-3):
        """
        对数据进行拟合

        Args:
            X: 特征矩阵
            y: 标签矩阵
            C: 对误差的惩罚项
            gamma: rbf核函数的参数
            n_iteration: 迭代次数
            tol: 停止训练的误差精度
        """
        n, m = X.shape
        if gamma == 'auto':
            self.gamma = 1 / m
        else:
            self.gamma = gamma

        self.K = np.zeros((n, n))
        for i in range(n):
            for j in range(i, n):
                self.K[i, j] = self.K[j, i] = self._rbf_kernel(X[i], X[j], self.gamma)
        self.X, self.y = X, y
        self.C, self.tol = C, tol
        self.alpha, self.b = np.zeros((n, 1)), 0
        self.E = (np.dot((self.alpha * y).T, self.K) + self.b).reshape(-1, 1) - y
        
        for iteration in range(n_iteration):
            pairs_changed = 0
            for i in range(n):
                Ei = self.E[i, 0]
                if ((y[i, 0] * Ei < -tol) and (self.alpha[i, 0] < C)) or ((y[i, 0] * Ei > tol) and (self.alpha[i, 0] > 0)):
                    j = self._select_j(i)
                    if j != -1:
                        pairs_changed += self._update(i, j)
            if pairs_changed == 0:
                print(f'no more pairs to change, stop at iteration {iteration + 1}')
                break

    def predict(self, X):
        """预测"""
        n, _ = self.X.shape
        m, _ = X.shape

        K = np.zeros((n, m))
        for i in range(n):
            for j in range(m):
                K[i, j] = self._rbf_kernel(self.X[i], X[j], self.gamma)
        y = np.dot((self.alpha * self.y).T, K) + self.b
        y = y.reshape(-1, 1)
        for i in range(m):
            y[i] = 1 if y[i] >= 0 else -1
        return y


def img2vec(filename):
    x = np.zeros((1, 1024))
    with open(filename, 'r') as f:
        for i in range(32):
            line = f.readline()
            for j in range(32):
                x[0, 32 * i + j] = int(line[j])
    return x


def load_data(dir):
    files = os.listdir(dir)
    X = np.zeros((len(files), 1024))
    y = np.zeros((len(files), 1))

    for i, file in enumerate(files):
        X[i, :] = img2vec(dir + os.path.sep + file)
        label = file.split('_')[0]
        y[i, 0] = 1 if label == '1' else -1
    return X, y


def main():
    X_train, y_train = load_data('digits/trainingDigits')
    X_test, y_test = load_data('digits/testDigits')

    model = SVM()
    model.fit(X_train, y_train)

    y_pred = model.predict(X_train)
    a, p, r = accuracy_score(y_train, y_pred), precision_score(y_train, y_pred), recall_score(y_train, y_pred)
    print(f'train: accuracy {a:.2f}, precision {p:.2f}, recall {r:.2f}')

    y_pred = model.predict(X_test)
    a, p, r = accuracy_score(y_test, y_pred), precision_score(y_test, y_pred), recall_score(y_test, y_pred)
    print(f'test: accuracy {a:.2f}, precision {p:.2f}, recall {r:.2f}')


if __name__ == '__main__':
    main()
