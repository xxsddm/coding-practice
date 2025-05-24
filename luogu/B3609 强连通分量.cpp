// https://www.luogu.com.cn/problem/B3609

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using std::vector;
using std::stack;

vector<vector<int>> adj, sccList;
vector<int> dfsOrder, lowDfsOrder, nodeIdx2SccIdx;
int dfsCount = 0;
vector<int> stkStatus;  // 一定要用节点的栈状态, 不可使用拓扑排序中的状态标记法
stack<int> stk;

void dfs(int node) {
    stkStatus[node] = 1;
    stk.push(node);
    dfsOrder[node] = lowDfsOrder[node] = dfsCount;
    ++dfsCount;
    for (int nextNode : adj[node]) {
        if (stkStatus[nextNode] == 0) {
            dfs(nextNode);
            lowDfsOrder[node] = std::min(lowDfsOrder[node], lowDfsOrder[nextNode]);
        } else if (stkStatus[nextNode] == 1) {
            lowDfsOrder[node] = std::min(lowDfsOrder[node], dfsOrder[nextNode]);
        }
    }
    if (lowDfsOrder[node] != dfsOrder[node]) {
        return;
    }
    int sccIdx = (int) sccList.size();
    int temp = -1;
    sccList.emplace_back();
    vector<int>& scc = sccList.back();
    do {
        temp = stk.top();
        stk.pop();
        nodeIdx2SccIdx[temp] = sccIdx;
        scc.push_back(temp);
        stkStatus[temp] = 2;
    } while (temp != node);
}

void init(int n) {
    adj.resize(n + 1);
    stkStatus.resize(n + 1, 0);
    dfsOrder.resize(n + 1, 0);
    lowDfsOrder.resize(n + 1, 0);
    nodeIdx2SccIdx.resize(n + 1, -1);
    dfsCount = 0;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    init(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u].push_back(v);
    }
    for (int i = 1; i <= n; ++i) {
        if (stkStatus[i] == 0) {
            dfs(i);
        }
    }
    printf("%llu\n", sccList.size());
    for (int idx = 1; idx <= n; ++idx) {
        int sccIdx = nodeIdx2SccIdx[idx];
        if (stkStatus[sccIdx] == 3) {
            continue;
        }
        stkStatus[sccIdx] = 3;
        vector<int>& scc = sccList[sccIdx];
        std::sort(scc.begin(), scc.end());
        for (int nodeIdx : scc) {
            printf("%d ", nodeIdx);
        }
        putchar('\n');
    }
}