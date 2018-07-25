# 常用算法模板

## 数据结构

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
 * 每一轮将当前堆中的最大元素nums[0]调整到数组的最后，然后调整堆（堆的大小减一）
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
int rangeUpdate(int from, int to, int x) {
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

