// http://oj.daimayuan.top/course/15/problem/858

#include <cstring>
#include <iostream>
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

int n, length = 1, *container, *node2idx, *depth, *pre, *top, *hson;
int *tree, *lazy;
vector<int> *adj;

int dfs1(const int &node, const int &prevnode) {
	depth[node] = depth[prevnode] + 1;
	pre[node] = prevnode;
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

void dfs2(const int &node, const int &prevnode) {
	int idx = length++;
	node2idx[node] = idx;
	top[node] = node == hson[prevnode] ? top[prevnode] : node;
	if (hson[node]) {
		dfs2(hson[node], node);
		for (int &nextnode : adj[node]) {
			if (nextnode != prevnode && nextnode != hson[node]) {
				dfs2(nextnode, node);
			}
		}
	}
}

void change(int cur, int start, int end, int left, int right, int delta) {
	if (left <= start && right >= end) {
		tree[cur] += delta;
		lazy[cur] += delta;
		return;
	}
	int mid = (start + end) >> 1, next1 = cur << 1, next2 = next1 ^ 1;
	if (lazy[cur]) {
		int temp = lazy[cur];
		lazy[cur] = 0;
		tree[next1] += temp, tree[next2] += temp;
		lazy[next1] += temp, lazy[next2] += temp;
	}
	if (right <= mid) {
		change(next1, start, mid, left, right, delta);
	} else if (left > mid) {
		change(next2, mid + 1, end, left, right, delta);
	} else {
		change(next1, start, mid, left, right, delta);
		change(next2, mid + 1, end, left, right, delta);
	}
	tree[cur] = tree[next1] + tree[next2];
}

int query(int cur, int start, int end, int idx) {
	if (start == end) {
		return tree[cur];
	}
	int mid = (start + end) >> 1, next1 = cur << 1, next2 = next1 ^ 1;
	if (lazy[cur]) {
		int temp = lazy[cur];
		lazy[cur] = 0;
		tree[next1] += temp, tree[next2] += temp;
		lazy[next1] += temp, lazy[next2] += temp;
	}
	if (idx <= mid) {
		return query(next1, start, mid, idx);
	}
	return query(next2, mid + 1, end, idx);
}

int main() {
	read(n);
	node2idx = new int[n + 1], depth = new int[n + 1];
	pre = new int[n + 1], top = new int[n + 1];
	hson = new int[n + 1], container = new int[n];
	tree = new int[n << 2], lazy = new int[n << 2];
	adj = new vector<int>[n + 1];
	depth[0] = hson[0] = 0;
	memset(tree, 0, sizeof(int) * (n << 2));
	memset(lazy, 0, sizeof(int) * (n << 2));
	for (int i = 0; i < n; i++) {
		read(container[i]);
	}
	for (int i = 1, x, y; i < n; i++) {
		read(x), read(y);
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	dfs1(1, 0);
	dfs2(1, 0);
	memset(hson + 1, 0, sizeof(int) * n);
	for (int i = 1; i < n; i++) {
		int u = container[i], v = container[i - 1];
		if (i != 1) {
			hson[v]++;
		}
		while (top[u] != top[v]) {
			if (depth[top[u]] < depth[top[v]]) {
				swap(u, v);
			}
			change(1, 1, n, node2idx[top[u]], node2idx[u], 1);
			u = pre[top[u]];
		}
		if (depth[u] > depth[v]) {
			swap(u, v);
		}
		change(1, 1, n, node2idx[u], node2idx[v], 1);
	}
	hson[container[n - 1]]++;
	for (int i = 1; i <= n; i++) {
		write(query(1, 1, n, node2idx[i]) - hson[i]);
	}
	return 0;
}