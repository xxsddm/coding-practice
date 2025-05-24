#include <queue>
#include <cstring>
#include <iostream>

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
std::vector<std::pair<int, int>> *next;

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
    putchar(' ');
}

int n, m, start, *dist;

int main() { // 洛谷P4779测试通过
    read(n), read(m), read(start);
    next = new std::vector<std::pair<int, int>>[n + 1];
    for (int i = 0, u, v, w; i < m; i++) {
        read(u), read(v), read(w);
        next[u].emplace_back(v, w);
    }
    dist = new int[n + 1];
    memset(dist, -1, sizeof(int) * (n + 1));
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;
    pq.emplace(0, start);
    while (!pq.empty()) {
        int length = pq.top().first, node = pq.top().second;
        pq.pop();
        if (dist[node] != -1) {
            continue;
        }
        dist[node] = length;
        for (auto& p : next[node]) {
            if (dist[p.first] == -1) {
                pq.emplace(length + p.second, p.first);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        write(dist[i]);
    }
    return 0;
}