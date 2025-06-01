// http://oj.daimayuan.top/course/23/problem/1084

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

int count = 0, total = 0, inf = 0x7fffffff, n, start, end;
int *first, *dist;
bool *visited;
vector<int> *next;
vector<Edge> container;

void addEdge(int u, int v, int w, int c) {
    container.push_back({v, w, c});
    container.push_back({u, 0, -c});  // 反向边使用相反费用
    next[u].push_back(count++);
    next[v].push_back(count++);
}

bool spfa() {
    memset(first, 0, sizeof(int) * (n + 1));
    memset(dist, 0x3f, sizeof(int) * (n + 1));
    queue<int> q;
    dist[start] = 0;
    q.push(start);
    visited[start] = true;
    while (!q.empty()) {
        int node = q.front();
        q.pop(), visited[node] = false;
        for (int &i : next[node]) {
            int &v = container[i].v, &rest = container[i].rest, &cost = container[i].cost;
            if (rest && dist[v] > dist[node] + cost) {
                dist[v] = dist[node] + cost;
                if (!visited[v]) {
                    q.push(v), visited[v] = true;
                }
            }
        }
    }
    return dist[end] != 0x3f3f3f3f;
}

int dfs(int node, int limit) {
    if (node == end) {
        return limit;
    }
    int ans = 0;
    // visited记录当前正在dfs中的节点, 避免形成环路
    visited[node] = true;
    for (int &i = first[node], j, size = (int)next[node].size(); i < size; i++) {
        j = next[node][i];
        int &v = container[j].v, &rest = container[j].rest, &cost = container[j].cost;
        if (visited[v] || dist[v] != dist[node] + cost || rest == 0) {
            continue;
        }
        int temp = dfs(v, std::min(limit, rest));
        if (temp == 0) {
            continue;
        }
        total += temp * cost;
        rest -= temp;
        container[j ^ 1].rest += temp;
        ans += temp;
        limit -= temp;
        if (limit == 0) {
            break;
        }
    }
    visited[node] = false;
    return ans;
}

int main() {
    int m;
    read(n), read(m);
    start = 1, end = n;
    next = new vector<int>[n + 1];
    container.reserve(m << 1);
    for (int i = 0, u, v, w, c; i < m; i++) {
        read(u), read(v), read(w), read(c);
        addEdge(u, v, w, c);
    }
    first = new int[n + 1], dist = new int[n + 1];
    visited = new bool[n + 1];
    memset(visited, false, sizeof(bool) * (n + 1));
    int ans = 0;
    while (spfa()) {
        ans += dfs(start, inf);
    }
    printf("%d %d", ans, total);
    return 0;
}