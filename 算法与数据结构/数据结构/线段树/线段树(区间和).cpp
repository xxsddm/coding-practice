// https://www.luogu.com.cn/problem/P3372

#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

class SegmentTree {
public:
    struct Node {
        ll value = 0, lazy= 0;
    };

    int length;
    vector<Node> tree;

    explicit SegmentTree(int length): length(length) {
        tree.resize(length << 2);
    }

    void change(int left, int right, ll delta) {
        change(1, 1, length, left, right, delta);
    }

    ll query(int left, int right) {
        return query(1, 1, length, left, right);
    }

private:
    void pushDown(int node, int start, int end) {
        Node& cur = tree[node];
        if (cur.lazy == 0) {
            return;
        }
        ll lazy = cur.lazy;
        cur.lazy = 0;
        int mid = (start + end) >> 1;
        int leftNode = node << 1, rightNode = leftNode ^ 1;
        Node &leftChild = tree[leftNode], &rightChild = tree[rightNode];
        leftChild.value += lazy * (mid - start + 1);
        rightChild.value += lazy * (end - mid);
        leftChild.lazy += lazy;
        rightChild.lazy += lazy;
    }

    void change(int node, int start, int end, int left, int right, ll delta) {
        if (left > end || right < start) {
            return;
        }
        if (left <= start && right >= end) {
            tree[node].value += delta * (end - start + 1);
            tree[node].lazy += delta;
            return;
        }
        pushDown(node, start, end);
        int mid = (start + end) >> 1;
        int leftNode = node << 1, rightNode = leftNode ^ 1;
        change(leftNode, start, mid, left, right, delta);
        change(rightNode, mid + 1, end, left, right, delta);
        tree[node].value = tree[leftNode].value + tree[rightNode].value;
    }

    ll query(int node, int start, int end, int left, int right) {
        if (left > end || right < start) {
            return 0;
        }
        if (left <= start && right >= end) {
            return tree[node].value;
        }
        pushDown(node, start, end);
        int mid = (start + end) >> 1;
        int leftNode = node << 1, rightNode = leftNode ^ 1;
        return query(leftNode, start, mid, left, right) +
                   query(rightNode, mid + 1, end, left, right);
    }
};

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    SegmentTree tree(n);
    for (int i = 1; i <= n; ++i) {
        ll num;
        scanf("%lld", &num);
        tree.change(i, i, num);
    }
    for (int i = 0, op, x, y; i < m; ++i) {
        scanf("%d %d %d", &op, &x, &y);
        if (op == 1) {
            ll k;
            scanf("%lld", &k);
            tree.change(x, y, k);
        } else {
            printf("%lld\n", tree.query(x, y));
        }
    }
    return 0;
}
