// http://oj.daimayuan.top/course/23/problem/1065

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

int numstk[20];

template <typename T>
inline void write(T x) {
    int tempLen = 0;
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    while (x > 9) {
        numstk[tempLen++] = x % 10;
        x /= 10;
    }
    numstk[tempLen++] = x;
    for (int i = tempLen - 1; i >= 0; i--) {
        putchar(numstk[i] ^ 48);
    }
    putchar('\n');
}

struct Edge {
    int v, rest;
};

int count = 0, start, end, *first, *dist, *nums, *dp;
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
    int n, s = 1;
    read(n);
    start = n * 2, end = start + 1;
    nums = new int[n], dp = new int[n];
    first = new int[end + 1], dist = new int[end + 1];
    for (int i = 0; i < n; i++) {
        read(nums[i]);
    }
    // 确定每个元素在最长非减子序列的相对位置(维护序列中位置)
    for (int i = 0; i < n; i++) {
        dp[i] = 1;
        for (int j = 0; j < i; j++) {
            if (nums[i] >= nums[j] && dp[i] <= dp[j]) {
                dp[i] = dp[j] + 1;
                if (dp[i] > s) {
                    s = dp[i];
                }
            }
        }
    }
    write(s);
    if (s == 1) {
        write(n);
        write(n);
        return 0;
    }
    // 各节点对应延伸节点, 维护流量1有向边控制元素使用次数
    next = new vector<int>[end + 1];
    for (int i = 0; i < n; i++) {
        addEdge(i, i + n, 1);
        if (dp[i] == 1) {
            addEdge(start, i, 1);
        } else if (dp[i] == s) {
            addEdge(i + n, end, 1);
        }
        for (int j = 0; j < i; j++) {
            if (nums[i] >= nums[j] && dp[j] + 1 == dp[i]) {
                addEdge(j + n, i, 1);
            }
        }
    }
    int ans = 0;
    while (bfs()) {
        ans += dfs(start, 1 << 30);
    }
    write(ans);
    ans = 0;
    for (int i = 0, size = (int)container.size(); i < size; i += 2) {
        container[i].rest += container[i ^ 1].rest;
        container[i ^ 1].rest = 0;
    }
    for (int &i : next[start]) {
        if (container[i].v == 0) {
            container[i].rest = 1 << 30;
            break;
        }
    }
    for (int &i : next[0]) {
        if (container[i].v == n) {
            container[i].rest = 1 << 30;
            break;
        }
    }
    for (int &i : next[n - 1]) {
        if (container[i].v == 2 * n - 1) {
            container[i].rest = 1 << 30;
            break;
        }
    }
    if (dp[n - 1] == s) {
        for (int &i : next[2 * n - 1]) {
            if (container[i].v == end) {
                container[i].rest = 1 << 30;
                break;
            }
        }
    }
    while (bfs()) {
        ans += dfs(start, 1 << 30);
    }
    write(ans);
    return 0;
}