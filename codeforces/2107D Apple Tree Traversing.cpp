// https://codeforces.com/contest/2107/problem/D

#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;

int N, nUsed = 0, virtualRoot = 0;
vector<int> node2PrevNode, depth;
vector<bool> used;
vector<array<int, 3>> container;
vector<vector<int>> adj;

void init(int n) {
    nUsed = 0;
    container.clear();
    adj.clear();
    adj.resize(n + 1);
    for (int i = 0; i < used.size(); ++i) {
        used[i] = false;
        node2PrevNode[i] = 0;
        depth[i] = 0;
    }
    if (used.size() > n) {
        return;
    }
    used.resize(n + 1, false);
    node2PrevNode.resize(n + 1, 0);
    depth.resize(n + 1, 0);
}

array<int, 3> dfs(int node, int prevNode, array<int, 3>& finalRes) { // 找出子树的直径
    node2PrevNode[node] = prevNode;
    depth[node] = depth[prevNode] + 1;
    array<int, 3> res = {1, node, node};
    for (int nextNode : adj[node]) {
        if (nextNode == prevNode || used[nextNode]) {
            continue;
        }
        auto temp = dfs(nextNode, node, finalRes);
        array<int, 3> concat = {res[0] + temp[0], max(res[2], temp[2]), min(res[2], temp[2])};
        ++temp[0];
        temp[1] = node;
        res = max(res, temp);
        finalRes = max(finalRes, concat);
    }
    finalRes = max(finalRes, {res[0], max(res[1], res[2]), min(res[1], res[2])});
    return res;
}

void mark(int u, int v) {   // 标记路径使用的点
    if (depth[u] < depth[v]) {
        swap(u, v);
    }
    while (depth[u] > depth[v]) {
        used[u] = true;
        u = node2PrevNode[u];
    }
    while (u != v) {
        used[u] = true;
        used[v] = true;
        u = node2PrevNode[u];
        v = node2PrevNode[v];
    }
    used[u] = true;
}

void solve() {
    scanf("%d", &N);
    init(N);
    for (int i = 0, u, v; i < N - 1; ++i) {
        scanf("%d %d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    depth[virtualRoot] = 0;
    // 不断寻找子树的直径, 移除(软删除)直径上的点并拆分子树, 直到所有点都被使用
    while (nUsed < N) {
        for (int i = 1; i <= N; ++i) {
            if (used[i] || depth[i]) {  // 标记或该轮dfs遍历过的子树, 跳过
                continue;
            }
            array<int, 3> res = {0, 0, 0};
            dfs(i, virtualRoot, res);
            nUsed += res[0];
            container.push_back(res);
            mark(res[1], res[2]);
        }
        for (int i = 1; i <= N; ++i) {
            depth[i] = 0;
        }
    }
    sort(container.begin(), container.end());
    reverse(container.begin(), container.end());
    for (auto& res : container) {
        printf("%d %d %d ", res[0], res[1], res[2]);
    }
    putchar('\n');
}

int main() {
    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; ++i) {
        solve();
    }
    return 0;
}