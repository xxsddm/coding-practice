// https://www.luogu.com.cn/problem/P4013

#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

using std::queue;
using std::vector;

template <typename T>
inline void read(T &x) {
    x = 0;
    bool neg = false;
    char c = getchar();
    while (c < 48 || c > 57) {
        if (c == '-') {
            neg = true;
        }
        c = getchar();
    }
    while (c >= 48 && c <= 57) {
        x = (x << 3) + (x << 1) + (c ^ 48);
        c = getchar();
    }
    if (neg) {
        x = -x;
    }
}

struct Edge {
    int v, rest, cost;
};

int count = 0, start, end, base, numNode, total = 0, inf = 0x7fffffff;
int *first, *dist, loc2node[21][40];
bool *visited;
vector<int> *next, back1, back2;
vector<Edge> container;

void addEdge(int u, int v, int w, int c) {
    container.push_back({v, w, c});
    container.push_back({u, 0, -c});
    next[u].push_back(count++);
    next[v].push_back(count++);
}

bool bfs() {
    int limit = 0x80000000;
    memset(first, 0, sizeof(int) * (numNode + 1));
    for (int i = 0; i <= numNode; i++) {
        dist[i] = limit;
    }
    queue<int> q;
    q.push(start);
    visited[start] = true;
    dist[start] = 0;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        visited[node] = false;
        for (int &i : next[node]) {
            int &nextnode = container[i].v, &rest = container[i].rest,
                &cost = container[i].cost;
            if (rest && dist[nextnode] < dist[node] + cost) {
                dist[nextnode] = dist[node] + cost;
                if (!visited[nextnode]) {
                    q.push(nextnode);
                    visited[nextnode] = true;
                }
            }
        }
    }
    return dist[end] != limit;
}

int dfs(int node, int limit) {
    if (node == end) {
        return limit;
    }
    int ans = 0;
    visited[node] = true;
    for (int &i = first[node], size = (int)next[node].size(); i < size; i++) {
        int &j = next[node][i];
        int &nextnode = container[j].v, &rest = container[j].rest,
            &cost = container[j].cost;
        if (visited[nextnode] || !rest || dist[nextnode] != dist[node] + cost) {
            continue;
        }
        int temp = dfs(nextnode, std::min(limit, rest));
        limit -= temp;
        rest -= temp;
        ans += temp;
        container[j ^ 1].rest += temp;
        total += (long long)cost * temp;
        if (!limit) {
            break;
        }
    }
    visited[node] = false;
    return ans;
}

void reset() {
    total = 0;
    for (int i = 0, size = (int)container.size(); i < size; i += 2) {
        container[i].rest += container[i ^ 1].rest;
        container[i ^ 1].rest = 0;
    }
}

int main() {
    int m, n;
    read(m), read(n);
    base = m * n + n * (n - 1) / 2;
    start = (base << 1) ^ 1, end = start + 1;
    numNode = end + 1;
    first = new int[numNode + 1], dist = new int[numNode + 1];
    visited = new bool[numNode + 1];
    next = new vector<int>[numNode + 1];
    container.reserve(base << 1);
    memset(visited, false, sizeof(bool) * (numNode + 1));
    for (int i = 1, node = 1, num; i <= n; i++) {
        for (int j = 1; j < m + i; j++) {
            read(num);
            // 各节点拆分为2部分, 通过限流为1使该点只能使用1次
            addEdge(node, node + base, 1, num);
            back1.push_back(count - 2);
            loc2node[i][j] = node++;
        }
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m + i; j++) {
            int node = loc2node[i][j];
            int next1 = loc2node[i + 1][j], next2 = loc2node[i + 1][j + 1];
            // 向下一行节点连接, 通过限流为1使该边只能使用1次
            addEdge(node + base, next1, 1, 0);
            back2.push_back(count - 2);
            addEdge(node + base, next2, 1, 0);
            back2.push_back(count - 2);
        }
    }
    for (int i = 1; i <= m; i++) {
        addEdge(start, loc2node[1][i], 1, 0);
    }
    for (int i = 1; i < m + n; i++) {
        addEdge(loc2node[n][i] + base, end, inf, 0);
    }
    while (bfs()) {
        dfs(start, inf);
    }
    printf("%d\n", total);
    reset();
    for (int &i : back1) {
        container[i].rest = inf;
    }
    while (bfs()) {
        dfs(start, inf);
    }
    printf("%d\n", total);
    reset();
    for (int &i : back2) {
        container[i].rest = inf;
    }
    while (bfs()) {
        dfs(start, inf);
    }
    printf("%d\n", total);
    return 0;
}