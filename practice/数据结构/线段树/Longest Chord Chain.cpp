// https://atcoder.jp/contests/abc410/tasks/abc410_g

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class SegmentTree {
public:
    struct Node {
        int value = 0;
    };

    int length;
    vector<Node> tree;

    explicit SegmentTree(int length): length(length) {
        tree.resize(length << 2);
    }

    void change(int loc, int value) {
        change(1, 1, length, loc, value);
    }

    int query(int left, int right) {
        return query(1, 1, length, left, right);
    }

private:
    void change(int node, int start, int end, int loc, int value) {
        if (loc > end || loc < start) {
            return;
        }
        if (start == end) {
            tree[node].value = value;
            return;
        }
        int mid = (start + end) >> 1;
        int leftNode = node << 1, rightNode = leftNode ^ 1;
        change(leftNode, start, mid, loc, value);
        change(rightNode, mid + 1, end, loc, value);
        tree[node].value = max(tree[leftNode].value, tree[rightNode].value);
    }

    int query(int node, int start, int end, int left, int right) {
        if (left > end || right < start) {
            return 0;
        }
        if (left <= start && right >= end) {
            return tree[node].value;
        }
        int mid = (start + end) >> 1;
        int leftNode = node << 1, rightNode = leftNode ^ 1;
        return max(query(leftNode, start, mid, left, right),
                   query(rightNode, mid + 1, end, left, right));
    }
};

int main() {
    int N;
    scanf("%d", &N);
    vector<pair<int, int>> container;
    container.reserve(N);
    for (int i = 0; i < N; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        if (a > b) {
            swap(a, b);
        }
        container.emplace_back(a, b);
    }
    sort(container.begin(), container.end(),
         [&](const pair<int, int>& o1, const pair<int, int>& o2) -> bool {
        if (o1.second != o2.second) {
            return o1.second < o2.second;
        }
        return o1.first < o2.first;
    });
    int length = N * 2;
    SegmentTree tree(length);
    vector<int> res(N, 0);
    for (int i = 0; i < N; ++i) {   // 处理该区间直接包含的内环(需考虑内环相互交叉, 取max)
        auto& [a, b] = container[i];
        int temp = tree.query(a, b - 1);
        ++temp;
        tree.change(a, temp);
        res[i] += temp;
    }
    for (int i = 0; i < N; ++i) {
        auto& [a, b] = container[i];
        res[i] += tree.query(b, length);    // 处理环形
    }
    printf("%d", *max_element(res.begin(), res.end()));
    return 0;
}