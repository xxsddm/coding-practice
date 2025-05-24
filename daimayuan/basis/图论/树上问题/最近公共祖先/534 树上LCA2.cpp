// http://oj.daimayuan.top/course/15/problem/534

#include "array"
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

int numstk[30];

template <typename T>
inline void write(T x) {
	int length = 0;
	while (x > 9) {
		numstk[length++] = x % 10;
		x /= 10;
	}
	numstk[length++] = x;
	for (int i = length - 1; i >= 0; i--) {
		putchar(numstk[i] ^ 48);
	}
	putchar('\n');
}

int *ans, *parent;
std::vector<int> *next;
std::vector<std::pair<int, int>> *query;

int find(int idx) {
	while (idx != parent[idx]) {
		parent[idx] = parent[parent[idx]];
		idx = parent[idx];
	}
	return idx;
}

void dfs(int node, int prevnode) {
	parent[node] = node;
	for (auto &[nextnode, idx] : query[node]) {
		if (parent[nextnode] != -1) {
			ans[idx] = parent[find(nextnode)];
		}
	}
	for (int &nextnode : next[node]) {
		if (nextnode == prevnode) {
			continue;
		}
		dfs(nextnode, node);
	}
	parent[node] = prevnode;
}

int main() {	// Tarjan
	int n, m;
	read(n);
	parent = new int[n + 1];
	next = new std::vector<int>[n + 1];
	query = new std::vector<std::pair<int, int>>[n + 1];
	parent[1] = 1;
	for (int i = 1, u, v; i < n; i++) {
		read(u), read(v);
		next[u].push_back(v), next[v].push_back(u);
		parent[i + 1] = -1;
	}
	read(m);
	ans = new int[m];
	for (int i = 0, u, v; i < m; i++) {
		read(u), read(v);
		query[u].emplace_back(v, i), query[v].emplace_back(u, i);
	}
	dfs(1, -1);
	for (int i = 0; i < m; i++) {
		write(ans[i]);
	}
	return 0;
}
