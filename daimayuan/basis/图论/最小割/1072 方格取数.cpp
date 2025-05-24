// http://oj.daimayuan.top/course/23/problem/1072

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
    int v, rest;
};

int count = 0, inf = 0x7fffffff, m, n, start, end;
int *first, *dist;
vector<int> *next;
vector<Edge> container;

void addEdge(int u, int v, int w) {
    container.push_back({v, w});
    container.push_back({u, 0});
    next[u].push_back(count++);
    next[v].push_back(count++);
}

bool bfs() {
    memset(first, 0, sizeof(int) * (end + 1));
    memset(dist, 0, sizeof(int) * (end + 1));
    queue<int> q;
    q.push(start);
    dist[start] = 1;
    while (!q.empty() && dist[end] == 0) {
        int node = q.front();
        q.pop();
        for (int &i : next[node]) {
            int &v = container[i].v, &rest = container[i].rest;
            if (dist[v] == 0 && rest) {
                q.push(v);
                dist[v] = dist[node] + 1;
            }
        }
    }
    return dist[end];
}

int dfs(int node, int limit) {
    if (node == end) {
        return limit;
    }
    int ans = 0;
    for (int &i = first[node], j, size = (int)next[node].size(); i < size; i++) {
        j = next[node][i];
        int &v = container[j].v, &rest = container[j].rest;
        if (dist[v] != dist[node] + 1 || rest == 0) {
            continue;
        }
        int temp = dfs(v, std::min(limit, rest));
        rest -= temp;
        container[j ^ 1].rest += temp;
        ans += temp;
        limit -= temp;
        if (limit == 0) {
            return ans;
        }
    }
    return ans;
}

int main() {
    read(m), read(n);
    int total = m * n, ans = 0;
    start = total, end = start + 1;
    first = new int[end + 1], dist = new int[end + 1];
    next = new vector<int>[end + 1];
    for (int node = 0, row, col, val; node < total; node++) {
        read(val);
        row = node / n, col = node % n;
        ans += val;
        // row + col奇偶性判断流量边所属集合
        // 保证当前点和相邻点分属start集和end集(但start集点不与end集所有点相邻)
        // 则最大流使用被剔除的点, 剩余流量即最大割
        if ((row + col) & 1) {
            addEdge(node, end, val);
            continue;
        }
        // 限制边一定由start集连向end集
        addEdge(start, node, val);
        if (row != 0) {
            addEdge(node, node - n, inf);
        }
        if (row + 1 != m) {
            addEdge(node, node + n, inf);
        }
        if (col != 0) {
            addEdge(node, node - 1, inf);
        }
        if (col + 1 != n) {
            addEdge(node, node + 1, inf);
        }
    }
    while (bfs()) {
        ans -= dfs(start, inf);
    }
    printf("%d", ans);
    return 0;
}