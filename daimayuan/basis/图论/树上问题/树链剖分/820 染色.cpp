// http://oj.daimayuan.top/course/15/problem/820

#include <iostream>
#include <cstring>
#include <vector>

using std::swap;
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

struct info {
    int left, right, count = -1;
} * container;

inline info merge(const info &p1, const info &p2) {
    if (p1.count == -1) {
        return p2;
    }
    if (p2.count == -1) {
        return p1;
    }
    info ans;
    ans.left = p1.left, ans.right = p2.right;
    ans.count = p1.count + p2.count - (p1.right == p2.left);
    return ans;
}

int total = 1, n, *nums, *depth, *node2idx, *hson, *top, *pre, *lazy;
vector<int> *adj;

int dfs1(int node, int prevnode) {
    pre[node] = prevnode;
    depth[node] = depth[prevnode] + 1;
    hson[node] = 0;
    int count = 1, maxsize = 0;
    for (int &nextnode : adj[node]) {
        if (nextnode != prevnode) {
            int temp = dfs1(nextnode, node);
            count += temp;
            if (temp > maxsize) {
                maxsize = temp;
                hson[node] = nextnode;
            }
        }
    }
    return count;
}

void dfs2(int node, int prevnode) {
    int idx = total++;
    node2idx[node] = idx;
    top[node] = hson[prevnode] == node ? top[prevnode] : node;
    if (hson[node]) {
        dfs2(hson[node], node);
        for (int &nextnode : adj[node]) {
            if (nextnode != hson[node] && nextnode != prevnode) {
                dfs2(nextnode, node);
            }
        }
    }
}

void change(int cur, int start, int end, int left, int right, int val) {
    if (left <= start && right >= end) {
        container[cur].left = container[cur].right = val;
        container[cur].count = 1;
        lazy[cur] = val;
        return;
    }
    int mid = (start + end) >> 1, next1 = cur << 1, next2 = next1 ^ 1;
    if (lazy[cur]) {
        container[next1].left = container[next1].right = lazy[cur];
        container[next2].left = container[next2].right = lazy[cur];
        container[next1].count = container[next2].count = 1;
        lazy[next1] = lazy[next2] = lazy[cur];
        lazy[cur] = 0;
    }
    if (right <= mid) {
        change(next1, start, mid, left, right, val);
    } else if (left > mid) {
        change(next2, mid + 1, end, left, right, val);
    } else {
        change(next1, start, mid, left, right, val);
        change(next2, mid + 1, end, left, right, val);
    }
    container[cur] = merge(container[next1], container[next2]);
}

info query(int cur, int start, int end, int left, int right) {
    if (left <= start && right >= end) {
        return container[cur];
    }
    int mid = (start + end) >> 1, next1 = cur << 1, next2 = next1 ^ 1;
    if (lazy[cur]) {
        container[next1].left = container[next1].right = lazy[cur];
        container[next2].left = container[next2].right = lazy[cur];
        container[next1].count = container[next2].count = 1;
        lazy[next1] = lazy[next2] = lazy[cur];
        lazy[cur] = 0;
    }
    if (right <= mid) {
        return query(next1, start, mid, left, right);
    } else if (left > mid) {
        return query(next2, mid + 1, end, left, right);
    }
    return merge(query(next1, start, mid, left, right), query(next2, mid + 1, end, left, right));
}

void op1(int u, int v, int val) {
    while (top[u] != top[v]) {
        if (depth[top[u]] < depth[top[v]]) {
            swap(u, v);
        }
        change(1, 1, n, node2idx[top[u]], node2idx[u], val);
        u = pre[top[u]];
    }
    if (depth[u] > depth[v]) {
        swap(u, v);
    }
    change(1, 1, n, node2idx[u], node2idx[v], val);
}

int op2(int u, int v) {
    info ans1, ans2;
    while (top[u] != top[v]) {
        if (depth[top[u]] < depth[top[v]]) {
            swap(u, v);
            swap(ans1, ans2);
        }
        ans1 = merge(query(1, 1, n, node2idx[top[u]], node2idx[u]), ans1);
        u = pre[top[u]];
    }
    if (depth[u] > depth[v]) {
        swap(u, v);
        swap(ans1, ans2);
    }
    ans2 = merge(query(1, 1, n, node2idx[u], node2idx[v]), ans2);
    swap(ans1.left, ans1.right);
    return merge(ans1, ans2).count;
}

int main() {    // 维护区间端点值和区间内段数
    int m;
    read(n), read(m);
    nums = new int[n + 1], depth = new int[n + 1];
    node2idx = new int[n + 1], hson = new int[n + 1];
    top = new int[n + 1], pre = new int[n + 1];
    adj = new vector<int>[n + 1];
    for (int i = 1; i <= n; i++) {
        read(nums[i]);
    }
    for (int i = 1, u, v; i < n; i++) {
        read(u), read(v);
        adj[u].push_back(v), adj[v].push_back(u);
    }
    depth[0] = hson[0] = 0;
    dfs1(1, 0);
    dfs2(1, 0);
    lazy = new int[n << 2];
    container = new info[n << 2];
    memset(lazy, 0, sizeof(int) * (n << 2));
    for (int i = 1; i <= n; i++) {
        change(1, 1, n, node2idx[i], node2idx[i], nums[i]);
    }
    char command;
    for (int i = 0, a, b, c; i < m; i++) {
        command = getchar();
        while (command != 'C' && command != 'Q') {
            command = getchar();
        }
        read(a), read(b);
        if (command == 'C') {
            read(c);
            op1(a, b, c);
        } else {
            write(op2(a, b));
        }
    }
    return 0;
}