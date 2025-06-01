// https://www.luogu.com.cn/problem/P3388

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

bool *visited, *isCutPoint;
vector<int> *adj;
int *order, *low;
int nCutPoint = 0, idx = 0;

void dfs(int node, bool isRoot) {
    visited[node] = true;
    order[node] = low[node] = idx++;
    int count = 0;
    for (int nextNode : adj[node]) {
        if (visited[nextNode]) {
            low[node] = min(low[node], order[nextNode]);
            continue;
        }
        dfs(nextNode, false);
        low[node] = min(low[node], low[nextNode]);
        if (low[nextNode] >= order[node]) {
            ++count;
        }
    }
    if (count > isRoot) {
        ++nCutPoint;
        isCutPoint[node] = true;
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    adj = new vector<int> [n + 1];
    for (int i = 0, x, y; i < m; ++i) {
        scanf("%d %d", &x, &y);
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    visited = new bool[n + 1];
    isCutPoint = new bool[n + 1];
    order = new int[n + 1];
    low = new int[n + 1];
    memset(visited + 1, 0, sizeof(bool) * n);
    memset(isCutPoint + 1, 0, sizeof(bool) * n);
    for (int i = 1; i <= n; ++i) {
        if (visited[i]) {
            continue;
        }
        dfs(i, true);
    }
    printf("%d\n", nCutPoint);
    for (int i = 1; i <= n; ++i) {
        if (isCutPoint[i]) {
            printf("%d ", i);
        }
    }
    return 0;
}