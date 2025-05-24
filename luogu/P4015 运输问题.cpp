// https://www.luogu.com.cn/problem/P4015

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

int count = 0, total = 0, inf = 0x7fffffff, start, end;
int *first, *dist;
bool *visited;
vector<int> *next;
vector<Edge> container;

void addEdge(int u, int v, int w, int c) {
    container.push_back({v, w, c});
    container.push_back({u, 0, -c});
    next[u].push_back(count++);
    next[v].push_back(count++);
}

bool spfa1() {
    memset(first, 0, sizeof(int) * (end + 1));
    memset(dist, 0x3f, sizeof(int) * (end + 1));
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
                    q.push(v);
                    visited[v] = true;
                }
            }
        }
    }
    return dist[end] != 0x3f3f3f3f;
}

bool spfa2() {
    int limit = 0x80000000;
    memset(first, 0, sizeof(int) * (end + 1));
    for (int i = 0; i <= end; i++) {
        dist[i] = limit;
    }
    queue<int> q;
    dist[start] = 0;
    q.push(start);
    visited[start] = true;
    while (!q.empty()) {
        int node = q.front();
        q.pop(), visited[node] = false;
        for (int &i : next[node]) {
            int &v = container[i].v, &rest = container[i].rest, &cost = container[i].cost;
            if (rest && dist[v] < dist[node] + cost) {
                dist[v] = dist[node] + cost;
                if (!visited[v]) {
                    q.push(v);
                    visited[v] = true;
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
    int m, n;
    read(m), read(n);
    start = m + n, end = start + 1;
    next = new vector<int>[end + 1];
    container.reserve((m * n + m + n) << 1);
    for (int i = 0, a; i < m; i++) {
        read(a);
        addEdge(start, i, a, 0);
    }
    for (int i = m, b; i < start; i++) {
        read(b);
        addEdge(i, end, b, 0);
    }
    for (int i = 0, c; i < m; i++) {
        for (int j = m; j < start; j++) {
            read(c);
            addEdge(i, j, inf, c);
        }
    }
    first = new int[end + 1], dist = new int[end + 1];
    visited = new bool[end + 1];
    memset(visited, false, sizeof(bool) * (end + 1));
    while (spfa1()) {
        dfs(start, inf);
    }
    printf("%d\n", total);
    total = 0;
    for (int i = 0, size = (int)container.size(); i < size; i += 2) {
        container[i].rest += container[i ^ 1].rest;
        container[i ^ 1].rest = 0;
    }
    while (spfa2()) {
        dfs(start, inf);
    }
    printf("%d", total);
    return 0;
}