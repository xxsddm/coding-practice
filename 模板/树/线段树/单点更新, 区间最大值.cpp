#include <vector>

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