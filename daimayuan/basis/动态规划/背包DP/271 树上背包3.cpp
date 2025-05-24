// http://oj.daimayuan.top/course/8/problem/271

#include <iostream>
#include <vector>

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

int n, m, idx = 1, *idx2node, *size, *val, *weight, **dp;
std::vector<int> *next;

int dfs(int node) {
    int cur = idx++;
    idx2node[cur] = node;
    size[cur] = 1;
    for (int &nextnode : next[node]) {
        size[cur] += dfs(nextnode);
    }
    return size[cur];
}

int main() {
    read(n), read(m);
    idx2node = new int[n + 1];
    size = new int[n + 1], dp = new int *[n + 2];
    val = new int[n + 1], weight = new int[n + 1];
    next = new std::vector<int>[n + 1];
    for (int i = 2, j; i <= n; i++) {
        read(j);
        next[j].push_back(i);
    }
    for (int i = 1; i <= n; i++) {
        read(val[i]);
    }
    for (int i = 1; i <= n; i++) {
        read(weight[i]);
    }
    for (int i = 1, neginf = -(1 << 30); i <= n + 1; i++) {
        dp[i] = new int[m + 1];
        dp[i][0] = 0;
        for (int j = 1; j <= m; j++) {
            dp[i][j] = neginf;
        }
    }
    dfs(1);
    for (int cur = n, node; cur >= 1; cur--) {
        node = idx2node[cur];
        for (int i = weight[node] - 1; i >= 0; i--) {
            dp[cur][i] = dp[cur + size[cur]][i];
        }
        for (int i = weight[node]; i <= m; i++) {
            // 跳过当前子树 或 选择当前节点
            // 根节点1被跳过时第一维为n+1, -inf, 故跳过则最后为0
            dp[cur][i] = std::max(dp[cur + size[cur]][i], dp[cur + 1][i - weight[node]] + val[node]);
        }
    }
    for (int i = 0; i <= m; i++) {
        write(std::max(dp[1][i], 0));
    }
    return 0;
}