// https://www.luogu.com.cn/problem/P8435

#include <cstdint>
#include <iostream>
#include <vector>
#include <stack>
#include <map>

using namespace std;

int idx = 1;
stack<int> stk;
vector<int> dfsOrder, low, *adj;
vector<vector<int>> container;

void init(int n) {
    dfsOrder.resize(n + 1, 0);
    low.resize(n + 1, 0);
    adj = new vector<int>[n + 1];
}

void dfs(int node) {
    dfsOrder[node] = low[node] = idx;
    ++idx;
    stk.push(node);
    if (adj[node].empty()) {
        container.push_back({node});
        return;
    }
    for (int nextNode : adj[node]) {
        if (dfsOrder[nextNode]) {
            low[node] = min(low[node], dfsOrder[nextNode]);
            continue;
        }
        dfs(nextNode);
        low[node] = min(low[node], low[nextNode]);
        if (low[nextNode] < dfsOrder[node]) {
            continue;
        }
        vector<int> temp;
        int top = stk.top();
        stk.pop();
        temp.push_back(top);
        while (top != nextNode) {
            top = stk.top();
            stk.pop();
            temp.push_back(top);
        }
        temp.push_back(node);
        container.emplace_back(std::move(temp));
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    init(n);
    for (int i = 0, x, y; i < m; ++i) {
        scanf("%d %d", &x, &y);
        if (x == y) {
            continue;
        }
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    for (int i = 1; i <= n; ++i) {
        if (dfsOrder[i]) {
            continue;
        }
        dfs(i);
        stk.pop();
    }
    printf("%lu\n", container.size());
    for (vector<int> &vec : container) {
        printf("%lu ", vec.size());
        for (int &i : vec) {
            printf("%d ", i);
        }
        printf("\n");
    }
    return 0;
}