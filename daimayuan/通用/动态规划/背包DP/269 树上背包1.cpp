// http://oj.daimayuan.top/course/8/problem/269

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

int neginf = -(1 << 30), *val, *size, **dp;
std::vector<int> *next;

int dfs1(int node) {
    size[node] = 1;
    for (int &nextnode : next[node]) {
        int temp = dfs1(nextnode);
        size[node] += temp;
    }
    dp[node] = new int[size[node] + 1];
    for (int i = 2; i <= size[node]; i++) {
        dp[node][i] = neginf;
    }
    dp[node][0] = 0;
    dp[node][1] = val[node];
    return size[node];
}

void dfs2(int node) {
    size[node] = 1;
    for (int &nextnode : next[node]) {
        dfs2(nextnode);
        for (int i = size[node] + size[nextnode]; i >= 2; i--) {
            for (int j = std::min(size[nextnode], i - 1), limit = std::max(1, i - size[node]); j >= limit; j--) {
                dp[node][i] = std::max(dp[node][i], dp[node][i - j] + dp[nextnode][j]);
            }
        }
        size[node] += size[nextnode];
    }
}

int main() {
    int n, q;
    read(n), read(q);
    val = new int[n + 1], size = new int[n + 1];
    dp = new int *[n + 1];
    next = new std::vector<int>[n + 1];
    for (int i = 2, j; i <= n; i++) {
        read(j);
        next[j].push_back(i);
    }
    for (int i = 1; i <= n; i++) {
        read(val[i]);
    }
    dfs1(1);
    dfs2(1);
    for (int i = 0, u, m; i < q; i++) {
        read(u), read(m);
        write(dp[u][m]);
    }
    return 0;
}
