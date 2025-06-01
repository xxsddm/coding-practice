// https://www.luogu.com.cn/problem/P3367

#include <iostream>
#include <vector>

using namespace std;

class DSU {
public:
    int length;
    vector<int> size, prev;

    explicit DSU(int length): length(length) {
        size.resize(length, 1);
        prev.resize(length);
        for (int i = 0; i < length; ++i) {
            prev[i] = i;
        }
    }

    int find(int node) {
        while (prev[node] != node) {
            prev[node] = prev[prev[node]];
            node = prev[node];
        }
        return node;
    }

    bool merge(int node1, int node2) {
        int root1 = find(node1), root2 = find(node2);
        if (root1 == root2) {
            return false;
        }
        if (size[root1] < size[root2]) {
            std::swap(root1, root2);
        }
        prev[root2] = root1;
        size[root1] += size[root2];
        return true;
    }
};

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    DSU dsu(N + 1);
    for (int i = 0, op, x, y; i < M; ++i) {
        scanf("%d %d %d", &op, &x, &y);
        if (op == 1) {
            dsu.merge(x, y);
        } else {
            printf(dsu.find(x) == dsu.find(y) ? "Y\n" : "N\n");
        }
    }
    return 0;
}
