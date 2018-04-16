#include <iostream>
#include <vector>
using namespace std;

/* @param a: 状态转移概率矩阵
 * @param b: 观察到可见符号的概率矩阵
 * @param x: 观察到的序列
 * @param w0: 初始状态
 * @return: 最有可能的隐状态序列
 */
vector<int> viterbi(vector<vector<double>>& a, vector<vector<double>>& b, vector<int>& x, int w0) {
    int c = a.size(); // 状态数
    // int m = b[0].size(); // 可见符号数
    int T = x.size(); // 观察到的序列长度

    vector<double> delta(c);
    vector<vector<int>> psi(T, vector<int>(c));

    // 初始状态
    for (int i = 0; i < c; ++i)
        delta[i] = a[w0][i] * b[i][x[0]];

    for (int t = 1; t < T; ++t) {
        vector<double> newDelta;
        for (int j = 0; j < c; ++j) {
            double temp = 0;
            for (int i = 0; i < c; ++i) {
                if (delta[i] * a[i][j] > temp) {
                    temp = delta[i] * a[i][j];
                    psi[t][j] = i;
                }
            }
            newDelta.push_back(temp * b[j][x[t]]);
        }
        delta = newDelta;
    }

    vector<int> result;
    // 开始回溯
    // 先获取T时刻的状态
    int state = 0;
    for (int i = 1; i < c; ++i)
        if (delta[i] > delta[state]) state = i;
    result.push_back(state);

    for (int t = T - 2; t >= 0; --t) 
        result.push_back(psi[t+1][result.back()]);

    reverse(result.begin(), result.end());
    return result;
}

int main() {
    vector<vector<double>> a{{1, 0, 0, 0}, {0.2, 0.3, 0.1, 0.4}, {0.2, 0.5, 0.2, 0.1}, {0.8, 0.1, 0.0, 0.1}};
    vector<vector<double>> b{{1, 0, 0, 0, 0}, {0, 0.3, 0.4, 0.1, 0.2}, {0, 0.1, 0.1, 0.7, 0.1}, {0, 0.5, 0.2, 0.1, 0.2}};
    vector<int> x{1, 3, 2, 0};
    int w0 = 1;

    vector<int> result = viterbi(a, b, x, w0);
    for (int r : result) cout << r << " ";
    cout << "\n";
}