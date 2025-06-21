// https://atcoder.jp/contests/abc397/tasks/abc397_f

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class SegmentTree {
public:
    struct Node {
        int value = 0, lazy= 0;
    };

    int length;
    vector<Node> tree;

    explicit SegmentTree(int length): length(length) {
        tree.resize(length << 2);
    }

    void change(int left, int right, int delta) {
        change(1, 1, length, left, right, delta);
    }

    int query(int left, int right) {
        return query(1, 1, length, left, right);
    }

private:
    void pushDown(int node) {
        Node& cur = tree[node];
        if (cur.lazy == 0) {
            return;
        }
        int lazy = cur.lazy;
        cur.lazy = 0;
        int leftNode = node << 1, rightNode = leftNode ^ 1;
        Node &leftChild = tree[leftNode], &rightChild = tree[rightNode];
        leftChild.value += lazy;
        rightChild.value += lazy;
        leftChild.lazy += lazy;
        rightChild.lazy += lazy;
    }

    void change(int node, int start, int end, int left, int right, int delta) {
        if (left > end || right < start) {
            return;
        }
        if (left <= start && right >= end) {
            tree[node].value += delta;
            tree[node].lazy += delta;
            return;
        }
        pushDown(node);
        int mid = (start + end) >> 1;
        int leftNode = node << 1, rightNode = leftNode ^ 1;
        change(leftNode, start, mid, left, right, delta);
        change(rightNode, mid + 1, end, left, right, delta);
        tree[node].value = max(tree[leftNode].value, tree[rightNode].value);
    }

    int query(int node, int start, int end, int left, int right) {
        if (left > end || right < start) {
            return 0;
        }
        if (left <= start && right >= end) {
            return tree[node].value;
        }
        pushDown(node);
        int mid = (start + end) >> 1;
        int leftNode = node << 1, rightNode = leftNode ^ 1;
        return max(query(leftNode, start, mid, left, right),
               query(rightNode, mid + 1, end, left, right));
    }
};


int main() {
    int N;
    scanf("%d", &N);
    vector<int> nums(N + 1);
    for (int i = 1; i <= N; ++i) {
        scanf("%d", &nums[i]);
    }
    vector<int> counter(N + 1, 0), leftSameNum(N + 1);
    vector<int> leftCounter(N + 1), rightCounter(N + 1); // 维护左右前缀和, 查询左右区间不同元素数量
    for (int i = 1, num, count = 0; i <= N; ++i) {
        num = nums[i];
        if (counter[num]++ == 0) {
            ++count;
        }
        leftCounter[i] = count;
    }
    fill(counter.begin(), counter.end(), 0);
    for (int i = N, num, count = 0; i >= 1; --i) {
        num = nums[i];
        if (counter[num]++ == 0) {
            ++count;
        }
        rightCounter[i] = count;
    }
    fill(counter.begin(), counter.end(), 0);

    for (int i = 1, num; i <= N; ++i) {
        num = nums[i];
        leftSameNum[i] = counter[num];
        counter[num] = i;
    }
    // 线段树维护前两个区间的不同元素数量总和
    // 从小到大枚举中间区间右端点i, 则新加入的元素nums[i], 在 [前一个相同值索引+1, i] 导致 +1
    SegmentTree tree(N);
    int ans = 0;
    for (int i = 2; i < N; ++i) {
        tree.change(i, i, leftCounter[i - 1]);  // 当前点初始化为第一个区间不同元素数量
        tree.change(leftSameNum[i] + 1, i, 1);  // 引入当前值导致的区间更新
        ans = max(ans, tree.query(2, i) + rightCounter[i + 1]);
    }
    printf("%d", ans);
    return 0;
}
