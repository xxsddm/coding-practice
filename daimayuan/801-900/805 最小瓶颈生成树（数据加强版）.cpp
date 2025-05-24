// http://oj.daimayuan.top/course/10/problem/805

#include "algorithm"
#include "vector"
#include "iostream"

struct Edge {
	int u, v, w;

	bool operator < (Edge &other) {
		return w < other.w;
	}
} *edges;

template <typename T>
inline void read(T &x) {
	x = 0;
	char c = getchar();
	while (c < 48 || c > 57) {
		c = getchar();
	}
	while (c >= 48 && c <= 57) {
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = getchar();
	}
}

int numstk[30];

inline void write(int x) {
	int length = 0;
	while (x > 9) {
		numstk[length++] = x % 10;
		x /= 10;
	}
	numstk[length++] = x % 10;
	for (int i = length - 1; i >= 0; i--) {
		putchar(numstk[i] ^ 48);
	}
	putchar('\n');
}

int n, m, idx, *ans, *root, *val, **next;
std::vector<std::pair<int, int>> *query;

int find(int node) {
	while (node != root[node]) {
		root[node] = root[root[node]];
		node = root[node];
	}
	return node;
}

void addNode(int node1, int node2, int weight) {
	int idx1 = find(node1), idx2 = find(node2);
	if (idx1 == idx2) {
		return;
	}
	root[idx1] = root[idx2] = idx;
	next[idx - n] = new int[2];
	next[idx - n][0] = idx1, next[idx - n][1] = idx2;
	val[idx - n] = weight;
	idx++;
}

void dfs(int node) {
	root[node] = node;
	if (node <= n) {
		for (auto &[other, i] : query[node]) {
			if (root[other] != -1) {
				ans[i] = find(other);
			}
		}
		return;
	}
	for (int i = 0; i < 2; i++) {
		int &nextNode = next[node - n][i];
		dfs(nextNode);
		root[nextNode] = node;
	}
}

int main() {
	read(n), read(m);
	edges = new Edge[m];
	for (int i = 0; i < m; i++) {
		read(edges[i].u), read(edges[i].v), read(edges[i].w);
	}
	int length = n << 1;
	idx = n + 1;
	root = new int[length], val = new int[n];
	next = new int*[n];
	query = new std::vector<std::pair<int, int>>[n + 1];
	for (int i = 1; i < length; i++) {
		root[i] = i;
	}
	std::sort(edges, edges + m);
	for (int i = 0; i < m && idx < length; i++) {
		addNode(edges[i].u, edges[i].v, edges[i].w);
	}
	for (int i = 1; i < length; i++) {
		root[i] = -1;
	}
	int q;
	read(q);
	ans = new int[q];
	for (int i = 0, s, t; i < q; i++) {
		read(s), read(t);
		query[s].emplace_back(t, i);
		query[t].emplace_back(s, i);
	}
	dfs(idx - 1);
	for (int i = 0; i < q; i++) {
		write(val[ans[i] - n]);
	}
	return 0;
}
