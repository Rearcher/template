#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

/* @param a: 状态转移概率矩阵
 * @param b: 观察到可见符号的概率矩阵
 * @param x: 观察到的序列
 * @param w0: 初始状态
 * @return: 观察到序列x的概率
 */
double hmm_forward(vector<vector<double>>& a, vector<vector<double>>& b, vector<int>& x, int w0) {
    int c = a.size(); // 状态数
    // int m = b[0].size(); // 可见符号数
    int T = x.size();

    vector<double> alpha(c);
    // 初始状态
    for (int i = 0; i < c; ++i)
        alpha[i] = a[w0][i] * b[i][x[0]];

    for (int t = 1; t < T; ++t) {
        vector<double> newAlpha(c);
        for (int j = 0; j < c; ++j) {
            double temp = 0;
            for (int i = 0; i < c; ++i)
                temp += alpha[i] * a[i][j];
            newAlpha[j] = temp * b[j][x[t]];
        }
        alpha = newAlpha;
    }

    return accumulate(alpha.begin(), alpha.end(), 0.0);
}

int main() {
    vector<vector<double>> a{{1, 0, 0, 0}, {0.2, 0.3, 0.1, 0.4}, {0.2, 0.5, 0.2, 0.1}, {0.8, 0.1, 0.0, 0.1}};
    vector<vector<double>> b{{1, 0, 0, 0, 0}, {0, 0.3, 0.4, 0.1, 0.2}, {0, 0.1, 0.1, 0.7, 0.1}, {0, 0.5, 0.2, 0.1, 0.2}};
    vector<int> x{1, 3, 2, 0};
    int w0 = 1;

    cout << hmm_forward(a, b, x, w0) << endl;
}