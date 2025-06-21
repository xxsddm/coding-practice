// https://loj.ac/p/137

#include "algorithm"
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

int stk[40];

inline void write(int x) {
	int length = 0;
	while (x > 9) {
		stk[length++] = x % 10;
		x /= 10;
	}
	stk[length++] = x % 10;
	for (int i = length - 1; i >= 0; i--) {
		putchar(stk[i] ^ 48);
	}
}

int n, m, idx, a, b, c, p;
int *root, *val, *lg, *depth, **anc, **next;

inline int rnd() {
	return a = (a * b % p + c) % p;
}

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
	next[idx] = new int[2];
	next[idx][0] = idx1, next[idx][1] = idx2;
	val[idx++] = weight;
}

void dfs(int node, int prevNode) {
	if (depth[node]) {
		int length = lg[depth[node]];
		anc[node] = new int[length];
		anc[node][0] = prevNode;
		for (int i = 1; i < length; i++) {
			anc[node][i] = anc[anc[node][i - 1]][i - 1];
		}
	}
	if (node <= n) {
		return;
	}
	for (int i = 0, nextNode; i < 2; i++) {
		nextNode = next[node][i];
		depth[nextNode] = depth[node] + 1;
		dfs(nextNode, node);
	}
}

int lca(int u, int v) {
	if (depth[u] > depth[v]) {
		std::swap(u, v);
	}
	while (depth[u] < depth[v]) {
		v = anc[v][lg[depth[v] - depth[u]] - 1];
	}
	if (u == v) {
		return u;
	}
	for (int i = lg[depth[u]] - 1; i >= 0; i--) {
		if (i < lg[depth[u]] && anc[u][i] != anc[v][i]) {
			u = anc[u][i], v = anc[v][i];
		}
	}
	return anc[u][0];
}

int main() {
	read(n), read(m);
	edges = new Edge[m];
	for (int i = 0; i < m; i++) {
		read(edges[i].u), read(edges[i].v), read(edges[i].w);
	}
	int length = n << 1;
	idx = n + 1;
	root = new int[length], val = new int[length];
	lg = new int[length], depth = new int[length];
	anc = new int*[length], next = new int*[length];
	lg[0] = 0;
	for (int i = 1; i < length; i++) {
		root[i] = i;
		lg[i] = lg[i - 1] + (i == (1 << lg[i - 1]));
	}
	std::sort(edges, edges + m);
	for (int i = 0; i < m && idx < length; i++) {
		addNode(edges[i].u, edges[i].v, edges[i].w);
	}
	depth[idx - 1] = 0;
	dfs(idx - 1, 0);
	int q, ans = 0;
	read(q), read(a), read(b), read(c), read(p);
	for (int i = 0, u, v, mod = 1e9 + 7; i < q; i++) {
		u = rnd() % n + 1, v = rnd() % n + 1;
		if (u != v) {
			ans = (ans + val[lca(u, v)]) % mod;
		}
	}
	write(ans);
	return 0;
}

/*
#include "algorithm"
#include "vector"
#include "iostream"

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

int numstk[40];

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
}

struct Edge {
	int u, v, w;

	bool operator < (Edge &other) {
		return w < other.w;
	}
} *edges;

int n, m, idx = 1, ans = 0, mod = 1e9 + 7, a, b, c, p;
int *root, *val, **next;
std::vector<int> *query;

inline int rnd() {
	return a = (a * b % p + c) % p;
}

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
	root[idx1] = root[idx2] = idx + n;
	next[idx] = new int[2];
	next[idx][0] = idx1, next[idx][1] = idx2;
	val[idx++] = weight;
}

void dfs(int node) {
	root[node] = node;
	if (node <= n) {
		for (int &other : query[node]) {
			if (root[other] != -1) {
				ans = (ans + val[find(other) - n]) % mod;
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
	root = new int[length], val = new int[n];
	next = new int*[n];
	query = new std::vector<int>[n + 1];
	std::sort(edges, edges + m);
	for (int i = 1; i < length; i++) {
		root[i] = i;
	}
	for (int i = 0; i < m && idx < n; i++) {
		addNode(edges[i].u, edges[i].v, edges[i].w);
	}
	int q;
	read(q), read(a), read(b), read(c), read(p);
	for (int i = 0, u, v; i < q; i++) {
		u = rnd() % n + 1, v = rnd() % n + 1;
		if (u != v) {
			query[u].push_back(v);
			query[v].push_back(u);
		}
	}
	for (int i = 1; i < length; i++) {
		root[i] = -1;
	}
	dfs(length - 1);
	write(ans);
	return 0;
}

 */