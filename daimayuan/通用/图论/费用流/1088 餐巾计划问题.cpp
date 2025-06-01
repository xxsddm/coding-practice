// http://oj.daimayuan.top/course/23/problem/1088

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

int count = 0, start, end, numNode, inf = 0x7fffffff;
int *first, *dist;
long long total = 0;
bool *visited;
vector<int> *next;
vector<Edge> container;

void addEdge(int u, int v, int w, int c) {
    container.push_back({v, w, c});
    container.push_back({u, 0, -c});
    next[u].push_back(count++);
    next[v].push_back(count++);
}

bool spfa() {
    memset(first, 0, sizeof(int) * (numNode + 1));
    memset(dist, 0x3f, sizeof(int) * (numNode + 1));
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
            if (rest && dist[nextnode] > dist[node] + cost) {
                dist[nextnode] = dist[node] + cost;
                if (!visited[nextnode]) {
                    q.push(nextnode);
                    visited[nextnode] = true;
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

// 汇点流量还需流出重复使用, 故源点汇点设置为相同点center
// start, end额外设置, 分别用以连接每日节点的2, 1部分
// 用以描述每日节点两部分的流入流出情况
int main() {
    int n, c0, d1, c1, d2, c2;
    read(n), read(c0), read(d1), read(c1), read(d2), read(c2);
    int base = n, center = n << 1;
    start = center + 1, end = start + 1, numNode = end + 1;
    first = new int[numNode + 1], dist = new int[numNode + 1];
    visited = new bool[numNode + 1];
    next = new vector<int>[numNode + 1];
    memset(visited, false, sizeof(bool) * (numNode + 1));
    container.reserve(n * 7);
    for (int i = 0, j; i < n; i++) {
        read(j);
        addEdge(i, end, j, 0);
        addEdge(start, i + base, j, 0);
    }
    // 新购入
    for (int i = 0; i < n; i++) {
        addEdge(center, i, inf, c0);
        addEdge(i + base, center, inf, 0);
    }
    // 2种重复利用
    for (int i = d1; i < n; i++) {
        addEdge(i - d1 + base, i, inf, c1);
    }
    for (int i = d2; i < n; i++) {
        addEdge(i - d2 + base, i, inf, c2);
    }
    // 转移到下一天
    // 每日节点1部分转移可省略(不会多于购入, 重复利用也可等待需要时使用不会溢出)
    for (int i = 1; i < n; i++) {
        addEdge(i - 1 + base, i + base, inf, 0);
    }
    while (spfa()) {
        dfs(start, inf);
    }
    printf("%lld\n", total);
    return 0;
}