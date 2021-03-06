- [常用算法模板](#%e5%b8%b8%e7%94%a8%e7%ae%97%e6%b3%95%e6%a8%a1%e6%9d%bf)
  - [数论](#%e6%95%b0%e8%ae%ba)
    - [快速乘法与快速幂](#%e5%bf%ab%e9%80%9f%e4%b9%98%e6%b3%95%e4%b8%8e%e5%bf%ab%e9%80%9f%e5%b9%82)
    - [矩阵快速幂](#%e7%9f%a9%e9%98%b5%e5%bf%ab%e9%80%9f%e5%b9%82)
    - [Miller-Rabin大素数判定算法](#miller-rabin%e5%a4%a7%e7%b4%a0%e6%95%b0%e5%88%a4%e5%ae%9a%e7%ae%97%e6%b3%95)
    - [Pollard-Rho大整数因子分解算法](#pollard-rho%e5%a4%a7%e6%95%b4%e6%95%b0%e5%9b%a0%e5%ad%90%e5%88%86%e8%a7%a3%e7%ae%97%e6%b3%95)
    - [无限循环小数转分数](#%e6%97%a0%e9%99%90%e5%be%aa%e7%8e%af%e5%b0%8f%e6%95%b0%e8%bd%ac%e5%88%86%e6%95%b0)
  - [字符串](#%e5%ad%97%e7%ac%a6%e4%b8%b2)
    - [后缀数组](#%e5%90%8e%e7%bc%80%e6%95%b0%e7%bb%84)
  - [图论](#%e5%9b%be%e8%ae%ba)
    - [二分图](#%e4%ba%8c%e5%88%86%e5%9b%be)
    - [最短路径](#%e6%9c%80%e7%9f%ad%e8%b7%af%e5%be%84)
    - [最小生成树](#%e6%9c%80%e5%b0%8f%e7%94%9f%e6%88%90%e6%a0%91)
  - [动态规划](#%e5%8a%a8%e6%80%81%e8%a7%84%e5%88%92)
    - [背包问题](#%e8%83%8c%e5%8c%85%e9%97%ae%e9%a2%98)
  - [数据结构](#%e6%95%b0%e6%8d%ae%e7%bb%93%e6%9e%84)
    - [并查集](#%e5%b9%b6%e6%9f%a5%e9%9b%86)
    - [堆](#%e5%a0%86)
    - [二叉树的遍历（非递归）](#%e4%ba%8c%e5%8f%89%e6%a0%91%e7%9a%84%e9%81%8d%e5%8e%86%e9%9d%9e%e9%80%92%e5%bd%92)
    - [树状数组](#%e6%a0%91%e7%8a%b6%e6%95%b0%e7%bb%84)
    - [线段树](#%e7%ba%bf%e6%ae%b5%e6%a0%91)

# 常用算法模板

-----

## 数论

### 快速乘法与快速幂
```cpp
typedef long long ll;
// (a * b) % m
ll quick_mul(ll a, ll b, ll m) {
    ll res = 0;
    while (b) {
        if (b & 1) res = (res + a) % m;
        a = (a + a) % m;
        b >>= 1;
    }
    return res;
}

// (a ^ b) % m
ll quick_pow(ll a, ll b, ll m) {
    ll res = 1;
    while (b) {
        if (b & 1) res = quick_mul(res, a, m);
        a = quick_mul(a, a, m);
        b >>= 1;
    }
    return res;
}

// a ^ b
ll quick_pow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}
```

### 矩阵快速幂
```cpp
typedef long long ll;

struct Mat {
    ll mat[maxn][maxn];
    ll row, col;
};

Mat mul(Mat &a, Mat &b) {
    Mat ans;
    ans.row = a.row;
    ans.col = b.col;
    memset(ans.mat, 0, sizeof(ans.mat));

    for (ll i = 0; i < ans.row; i++)       
        for (ll k = 0; k < a.col; k++)
            if (a.mat[i][k])
                for (ll j = 0; j < ans.col; j++)
                    ans.mat[i][j] += a.mat[i][k] * b.mat[k][j];
    
    return ans;
}

Mat pow(Mat a, ll k) {
    Mat ans;
    ans.row = a.row;
    ans.col = a.col;

    for (ll i = 0; i < a.row; i++)
        for (ll j = 0; j < a.col; j++)
            ans.mat[i][j] = (i == j);
            
    while (k) {
        if (k & 1) ans = mul(ans, a);
        a = mul(a, a);
        k >>= 1;
    }
    return ans;
}
```

### Miller-Rabin大素数判定算法
```cpp
bool check(ll a, ll x, ll n, ll r) {
    ll res = quick_pow(a, x, n);
    ll last = res;
    for (int i = 0; i < r; ++i) {
        res = quick_mul(res, res, n);
        if (res == 1 && last != 1 && last != n - 1) return true;
        last = res;
    }
    if (res != 1) return true;
    return false;
}

// 返回true代表是素数
bool miller_rabin(ll n, int times=20) {
    if (n < 2) return false;
    if (n == 2) return true;
    if ((n & 1) == 0) return false;

    ll x = n - 1, r = 0;
    while ((x & 1) == 0) {
        x >>= 1;
        r++;
    }

    for (int i = 0; i < times; ++i) {
        ll a = rand() % (n - 1) + 1;
        if (check(a, x, n, r)) return false;
    }
    return true;
}
```

### Pollard-Rho大整数因子分解算法
```cpp
ll factor[100]; // 保存所有质因子
map<ll, ll> mp; // 保存所有质因子对应的数目
int tot;  // 质因子的个数

ll gcd(ll a, ll b) {
    if (a < 0) return gcd(-a, b);
    if (b == 0) return a;
    return gcd(b, a % b);
}

ll pollard_rho(ll x, ll c) {
    ll i = 1, k = 2;
    ll x0 = rand() % x;
    ll y = x0;

    while (true) {
        i++;
        x0 = (quick_mul(x0, x0, x) + c) % x;
        ll d = gcd(y - x0, x);
        if (d != 1 && d != x) return d;
        if (y == x0) return x;
        if (i == k) {
            y = x0;
            k += k;
        }
    }
}

void factorize(ll n) {
    if (miller_rabin(n)) {
        factor[tot++] = n;
        mp[n]++;
        return;
    }

    ll p = n;
    while (p >= n) {
        p = pollard_rho(p, rand() % (n - 1) + 1);
    }
    factorize(p);
    factorize(n / p);
}
```

### 无限循环小数转分数
假设有无限循环小数0.abcdefg，其中，defg是循环体。令非循环体的长度为L1，循环体的长度为L2，总长度L=L1+L2，那么原始的分数为(abcdefg - abc)/(pow(10, L) - pow(10, L1))

## 字符串

### 后缀数组
```cpp
const int MAX_N = 20005;
int n, k;
int rk[MAX_N + 1], sa[MAX_N + 1], tmp[MAX_N + 1];

bool compare_sa(int i, int j) {
    if (rk[i] != rk[j]) return rk[i] < rk[j];
    else {
        int ri = i + k <= n ? rk[i + k] : -1;
        int rj = j + k <= n ? rk[j + k] : -1;
        return ri < rj;
    }
}

void build_sa(string s) {
    n = s.length();
    for (int i = 0; i <= n; ++i) {
        sa[i] = i;
        rk[i] = i < n ? s[i] : -1;
    }

    for (k = 1; k <= n; k *= 2) {
        sort(sa, sa + n + 1, compare_sa);

        tmp[sa[0]] = 0;
        for (int i = 1; i <= n; ++i) {
            tmp[sa[i]] = tmp[sa[i - 1]] + (compare_sa(sa[i - 1], sa[i]) ? 1 : 0);
        }
        for (int i = 0; i <= n; ++i) {
            rk[i] = tmp[i];
        }
    }
}
```

## 图论

### 二分图
染色法判断一个图是否是二分图：将一个顶点标记为一种颜色，与其相邻的顶点标记为不同的颜色，如果发现相邻的顶点颜色与自身的颜色相同，则不能构成一个二分图。时间复杂度O(V + E)。
```cpp
vector<int> G[MAX_N]; // 邻接表
int color[MAX_V];     
int V; // 顶点数

// 深度优先搜索，将顶点v染成颜色c
bool dfs(int v, int c) {
    color[v] = c;
    for (int i = 0; i < G[v].size(); ++i) {
        // 发现邻居颜色与自己相同，不能构成二分图
        if (color[G[v][i]] == c) return false;
        // 将邻居染成与自己不同的颜色，如果失败，也不能构成二分图
        if (color[G[v][i]] == 0 && !dfs(G[v][i], -c)) return false;
    }
    return true;
}

void solve() {
    // 如果图不连通，需要一个循环
    for (int i = 0; i < V; ++i) {
        if (color[i] == 0) {
            if (!dfs(i, 1)) {
                cout << "NO\n";
                return;
            }
        }
    }
    cout << "YES\n";
}
```

### 最短路径

**单源最短路径算法Dijkstra**  

**注意**：下面的模板代码，数组都是从下标0开始的

将所有的点分成两个集合，一个集合S是最短路径已经确定的点，另一个集合V是最短路径还没有确定的点。最初集合S中只有起点，然后从集合V中选取距离起点最小的点，加入S，然后更新集合V中各个点与起点的距离，直到所有的点都加入到集合S中。复杂度为O(V^2)。不能处理负边。
```cpp
int g[MAX_V][MAX_V]; // 邻接矩阵
int d[MAX_V]; // 各个顶点到起点的距离
bool used[MAX_V]; // 用于记录顶点的最短路径是否确定
int V;

void dijkstra(int s) {
    fill(d, d + V, 0x3f3f3f3f);
    fill(used, used + V, false);
    d[s] = 0;

    while (true) {
        int v = -1;
        for (int i = 0; i < V; ++i)
            if (!used[i] && (v == -1 || d[v] > d[i])) v = i;

        if (v == -1) break;
        used[v] = true;
        for (int i = 0; i < v; ++i)
            d[i] = min(d[i], d[v] + g[v][i]);
    }
}
```

原始的dijkstra算法，最耗时的地方在于每一轮都要遍历寻找下一个距离起点最近的顶点，因此可以用最小堆来优化。利用堆优化的dijkstra算法，时间复杂度为O(ElogV)。
```cpp
typedef struct edge {
    int to, cost;
    edge() {}
    edge(int _to, int _cost) : to(_to), cost(_cost) {}
} edge;

typedef pair<int, int> P;

int V;
vector<edge> G[MAX_V];
int d[MAX_V];

void dijkstra(int s) {
    priority_queue<P, vector<P>, greater<P>> que;
    fill(d, d + V, 0x3f3f3f3f);
    
    d[s] = 0;
    que.push(P(0, s));

    while (!que.empty()) {
        P p = que.top(); que.pop();
        int v = p.second;
        if (d[v] < p.first) continue;
        for (int i = 0; i < G[v].size(); ++i) {
            edge e = G[v][i];
            if (d[e.to] > d[v] + e.cost) {
                d[e.to] = d[v] + e.cost;
                que.push(P(d[e.to], e.to));
            }
        }
    }
}
```


**单源最短路径算法Bellman-Ford**   

通过松弛法来更新，时间复杂度O(VE)。可以处理负边。
```cpp
typedef struct edge {
    int u, v, w;
} edge;

const int inf = 0x3f3f3f3f;

edge es[MAX_E];
int d[MAX_V];
int V, E;

void bellman_ford(int s) {
    for (int i = 0; i < V; ++i) d[i] = inf;
    d[s] = 0;

    while (true) { // 如果图中没有负环，则循环最多执行V-1次
        bool update = false;
        for (int i = 0; i < E; ++i) {
            if (d[e[i].u] != inf && d[e[i].v] > d[e[i].u] + e[i].w) {
                d[e[i].v] = d[e[i].u] + e[i].w;
                update = true;
            }
        }
        if (!update) break;
    }
}
```

**求所有点对之间的最短路径算法Floyd-Warshall**  

```cpp
int d[MAX_V][MAX_V];
int V;

for (int k = 0; k < V; ++k)
    for (int i = 0; i < V; ++i)
        for (int j = 0; j < V; ++j)
            d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
```

### 最小生成树

**prim算法**   

假设有一棵只包含一个顶点v的树T，然后贪心地选取T和其他顶点之间相连的最小权值的边，并把它加到T中。时间复杂度也是O(V^2)，如果用堆优化，时间复杂度是O(ElogV)。

```cpp
int g[MAX_V][MAX_V];
int d[MAX_V]; // 从当前生成树包含的点出发的边到其余顶点的最小值
bool used[MAX_V];
int v;

int prim() {
    for (int i = 0; i < V; ++i) {
        d[i] = 0x3f3f3f3f;
        used[i] = false;
    }
    d[i] = 0;
    int res = 0;

    while (true) {
        int v = -1;
        for (int i = 0; i < V; ++i) {
            if (!used[i] && (v == -1 || d[v] > d[i])) v = i;
        }

        if (v == -1) break;
        used[v] = true;
        res += d[v];
        for (int i = 0; i < V; ++i)
            d[i] = min(d[i], g[v][i]);
    }
    return res;
}
```

**kruskal算法**   

将边按权值从小到大排序，然后遍历边，如果不产生圈，就将这条边加入到最小生成树中。利用并查集高效判断是否会产生圈。时间复杂度O(ElogV)。
```cpp
typedef struct edge {
    int u, v, w;
    bool operator < (const edge& rhs) const {
        return w < rhs.w;
    }
} edge;

edge es[MAX_E];
int V, E;

int kruskal() {
    sort(es, es + E);
    init(V); // 并查集初始化
    int res = 0;
    for (int i = 0; i < E; ++i) {
        edge e = es[i];
        if (!same(e.u, e.v)) { // 并查集判断是否属于同一集合
            res += e.w;
            unite(e.u, e.v);
        }
    }
    return res;
}
```


## 动态规划

### 背包问题

**01背包**：N件物品放入容量为V的背包，放入第i件物品的费用是Ci，得到的价值是Wi，求解将哪些物品装入背包可以使得价值总和最大。
```cpp
// dp[i][j]表示前i件物品放入容量为j的背包时可以获得的最大价值
dp[0][0] = 0;
for (int i = 0; i < n; ++i) 
    for (int j = c[i]; j <= v; ++j)
        dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - c[i]] + w[i]);


// 优化空间复杂度
dp[0] = 0;
for (int i = 0; i < n; ++i)
    for (int j = v; j >= c[i]; --j)
        dp[j] = max(dp[j], dp[j - c[i]] + w[i]);
```
01背包的初始化：如果要求恰好装满背包，则`dp[0] = 0`，其余设为负无穷；如果不需要装满背包，只要求价值最大，则全部初始化为0

**完全背包**：每件物品的数量为无限
```cpp
dp[0] = 0;
for (int i = 0; i < n; ++i)
    for (int j = c[i]; j <= v; ++j)
        dp[j] = max(dp[j], dp[j - c[i]] + w[i]);
```

**多重背包**：每件物品的数量为Mi个
1. 朴素解法：对每种物品考虑取0、1、2...Mi个，时间复杂度是O(NV*sum(Mi))
2. 二进制优化：转化为01背包问题，采用二进制优化的思想，将Mi件第i个物品分解为log(Mi)件物品，此时时间复杂度为O(NV*log(sum(Mi)))
3. 如果需要将指定容量的背包装满，可以有O(NV)的解法（具体应用场景比如：物品的价值都为1，或者物品的价值和重量相等，比如“给你一堆不同数值的硬币，能凑成最大的面值是多少”这种问题）
 
```cpp
// 此代码为上述第3种情况的O(NV)解法
// 对于每一轮，用num[j]表示装满容量为j的背包当前物品最多需要多少个
// dp[j] = 1表示能将容量为j的背包装满，dp[j] = 0表示不能，dp[0] = 1
// 最后dp[1..v]中为1的都是对应的能被装满的容量

for (int i = 0; i < n; ++i) {
    memset(num, 0, sizeof(num));
    for (int j = c[i]; j <= v; ++j) {
        if (!dp[j] && dp[j - c[i]] && num[j - c[i]] < m[i]) {
            dp[j] = 1;
            num[j] = num[j - c[i]] + 1;
        }
    }
}
```

-----

## 数据结构

### 并查集
```cpp
const int MAX_N = 105;
int p[MAX_N], sz[MAX_N];

void init(int n) {
    for (int i = 0; i <= n; ++i) {
        p[i] = i;
        sz[i] = 1;
    }
}

int find(int x) {
    while (p[x] != x) {
        p[x] = p[p[x]];
        x = p[x];
    }
    return x;
}

void unite(int x, int y) {
    int rx = find(x), ry = find(y);
    if (rx == ry) return;
    if (sz[rx] < sz[ry]) {
        p[rx] = ry;
        sz[ry] += sz[rx];
    } else {
        p[ry] = rx;
        sz[rx] += sz[ry];
    }
}
```

### 堆
**注意：自底向上建堆的时间复杂度是O(n)**
```cpp
// 调整数组nums中[start, end)范围内的元素，使其满足最大堆的性质
void maxHeapify(vector<int>& nums, int start, int end) {
    int father = start;
    int son = father * 2 + 1;

    while (son < end) {
        if (son + 1 < end && nums[son + 1] > nums[son])
            son += 1;

        if (nums[father] >= nums[son]) return;

        swap(nums[father], nums[son]);
        father = son;
        son = father * 2 + 1;
    }
}

// 自底向上建立最大堆，复杂度是O(n)
void buildMaxHeap(vector<int>& nums) {
    int n = nums.size();
    for (int i = n / 2; i >= 0; --i)
        maxHeapify(nums, i, n);
}

/* 堆排序（从小到大）
 * 初始建立最大堆，此时nums[0]对应整个数组中最大的元素
 * 每一轮将当前堆中的最大元素nums[0]调整到数组的最后，然后调整堆（堆的大小减一）
 */
void heapSort(vector<int>& nums) {
    buildMaxHeap(nums);

    int n = nums.size();
    for (int i = n - 1; i >= 0; --i) {
        swap(nums[0], nums[i]);
        maxHeapify(nums, 0, i);
    }
}
```

### 二叉树的遍历（非递归）
```cpp
// 二叉树节点定义
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 先序遍历
vector<int> preOrder(TreeNode *root) {
    if (root == nullptr) return vector<int>();

    vector<int> res;
    stack<TreeNode *> s;
    s.push(root);
    
    while (!s.empty()) {
        TreeNode *tmpNode = s.top();
        s.pop();
        
        if (tmpNode->right) s.push(tmpNode->right);
        if (tmpNode->left) s.push(tmpNode->left);

        res.push_back(tmpNode->val);
    }

    return res;
};

// 中序遍历
vector<int> inOrder(TreeNode *root) {
    if (root == nullptr) return vector<int>();

    vector<int> res;
    TreeNode *curNode = root;
    stack<TreeNode *> s;

    while (curNode || !s.empty()) {
        if (curNode) {
            s.push(curNode);
            curNode = curNode->left;
        } else {
            TreeNode *tmpNode = s.top();
            s.pop();
            
            res.push_back(tmpNode->val);
            curNode = tmpNode->right;
        }
    }

    return res;
}

// 后序遍历
vector<int> postOrder(TreeNode *root) {
    if (root == nullptr) return vector<int>();

    vector<int> res;
    TreeNode *curNode = root, *prevNode = nullptr;
    stack<TreeNode *> s;

    while (curNode || !s.empty()) {
        if (curNode) {
            s.push(curNode);
            curNode = curNode->left;
        } else {
            TreeNode *tmpNode = s.top();
            if (tmpNode->right && prevNode != tmpNode->right) {
                curNode = tmpNode->right;
            } else {
                res.push_back(tmpNode->val);
                prevNode = tmpNode;
                s.pop();
            }
        }
    }

    return res;
};
```

### 树状数组

基本的树状数组的特征：
1. 主要用于快速求前缀和、区间和，复杂度都是O(logn)；
2. 基本实现只支持单点更新，复杂度也是O(logn)；
3. 空间复杂度是O(n)。

**注意：下面代码实现的树状数组坐标都是从1开始。**
```cpp
const int MAX_N = 100001;
int bit[MAX_N];

// 求[1, i]的和
int sum(int i) {
    int res = 0;
    while (i > 0) {
        res += bit[i];
        i -= i & (-i);
    }
    return res;
}

// 单点更新，i上的值加上x
void add(int i, int x) {
    while (i <= MAX_N) {
        bit[i] += x;
        i += i & (-i);
    }
}
```

通过使用两个树状数组来达到**O(logn)的区间更新复杂度**：
```cpp
const int MAX_N = 100001;
int bit0[MAX_N], bit1[MAX_N];

int sum(int* bit, int i) {
    int res = 0;
    while (i > 0) {
        res += bit[i];
        i -= i & (-i);
    }
    return res;
}

void add(int* bit, int i, int x) {
    while (i <= MAX_N) {
        bit[i] += x;
        i += i & (-i);
    }
}

// 求和[1, i]
int sum(int i) {
    return sum(bit1, i) * i + sum(bit0, i);
}

// 区间更新，[from, to]的元素都加上x，时间复杂度logn
void rangeUpdate(int from, int to, int x) {
    add(bit0, from, -x * (from - 1));
    add(bit1, from, x);
    add(bit0, to + 1, x * to);
    add(bit1, to + 1, -x);
}
```
二维树状数组：

```cpp
const int MAX_N = 100001;
int bit[MAX_N][MAX_N];

int sum(int x, int y) {
    int res = 0;
    for (int i = x; i > 0; i -= i & (-i))
        for (int j = y; j > 0; j -= j & (-j))
            res += bit[i][j];
   	return res;
}

void add(int x, int y, int val) {
    for (int i = x; i <= MAX_N; i += i & (-i))
        for (int j = y; j <= MAX_N; j += j & (-j))
            bit[i][j] += val;
}
```

### 线段树

用于单点更新、区间更新、区间求和、区间最值。下面的模板基于区间求和。

**注意点：**
1. 线段树的空间大小应是原始数组的**4倍**
2. 如果线段树的下标从0开始，那么某一节点idx的左儿子和右儿子分别是`idx * 2 + 1`和`idx * 2 + 2`
3. 如果线段树的下标从1开始，那么某一节点idx的左儿子和右儿子分别是`idx * 2`和`idx * 2 + 1`

```cpp
#define lson idx * 2
#define rson idx * 2 + 1

const int MAX_N = 100010;
int tree[MAX_N * 4], lazy[MAX_N * 4];
int a[MAX_N];

// 节点数据向上更新
void push_up(int idx) {
    tree[idx] = tree[lson] + tree[rson];
}

// lazy标记向下推
// len为tree[idx]对应的区间长度
void push_down(int idx, int len) {
    tree[lson] += lazy[idx] * (len - (len >> 1));
    lazy[lson] += lazy[idx];

    tree[rson] += lazy[idx] * (len >> 1);
    lazy[rson] += lazy[idx];

    lazy[idx] = 0;
}

/* 如果是求区间最值，则这样写 
void push_down(int idx, int len) {
    tree[lson] += lazy[idx];
    lazy[lson] += lazy[idx];

    tree[rson] += lazy[idx];
    lazy[rson] += lazy[idx];

    lazy[idx] = 0;
} */

void build(int idx, int s, int e) {
    if (s > e) return;
    if (s == e) {
        tree[idx] = a[s];
        return;
    }

    int m = (s + e) / 2;
    build(lson, s, m);
    build(rson, m + 1, e);
    push_up(idx);
}

// 单点更新
void update(int idx, int s, int e, int q, int val) {
    if (s == e) {
        tree[idx] += val;
        return;
    }

    int m = (s + e) / 2;
    if (q <= m) update(lson, s, m, q, val);
    else update(rson, m + 1, e, q, val);
    push_up(idx);
}

// 区间更新
void update(int idx, int s, int e, int qs, int qe, int val) {
    if (qs <= s && e <= qe) {
        tree[idx] += val * (e - s + 1);
        lazy[idx] += val;
        return;
    }

    if (lazy[idx]) push_down(idx, e - s + 1);

    int m = (s + e) / 2;
    if (qs <= m) update(lson, s, m, qs, qe, val);
    if (qe > m) update(rson, m + 1, e, qs, qe, val);
    push_up(idx);
}

// 区间查询
int query(int idx, int s, int e, int qs, int qe) {
    if (qs <= s && e <= qe) return tree[idx];
    if (lazy[idx]) push_down(idx, e - s + 1);

    int m = (s + e) / 2, res = 0;
    if (qs <= m) res += query(lson, s, m, qs, qe);
    if (qe > m) res += query(rson, m + 1, e, qs, qe);
    return res;
}
```
