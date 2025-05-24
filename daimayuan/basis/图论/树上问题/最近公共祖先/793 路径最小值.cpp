// http://oj.daimayuan.top/course/15/problem/793

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

struct Edge {
	int to, w;
};

// minnum[node][i] -> [node, anc[node][i]]路径最小边权
int *lg2, *depth, **anc, **minnum;
std::vector<Edge> *next;

void dfs(int node, int prevnode) {
	for (Edge &edge : next[node]) {
		int &nextnode = edge.to;
		if (nextnode == prevnode) {
			continue;
		}
		depth[nextnode] = depth[node] + 1;
		int length = lg2[depth[nextnode]];
		anc[nextnode] = new int[length], minnum[nextnode] = new int[length];
		anc[nextnode][0] = node, minnum[nextnode][0] = edge.w;
		for (int i = 1; i < length; i++) {
			anc[nextnode][i] = anc[anc[nextnode][i - 1]][i - 1];
			minnum[nextnode][i] = std::min(minnum[nextnode][i - 1],
			                               minnum[anc[nextnode][i - 1]][i - 1]);
		}
		dfs(nextnode, node);
	}
}

int query(int u, int v) {
	if (depth[u] < depth[v]) {
		std::swap(u, v);
	}
	int ans = 0x7fffffff;
	for (int temp; depth[u] > depth[v];) {
		temp = lg2[depth[u] - depth[v]] - 1;
		ans = std::min(ans, minnum[u][temp]);
		u = anc[u][temp];
	}
	if (u == v) {
		return ans;
	}
	for (int i = lg2[depth[u]] - 1; i >= 0; i--) {
		if (i < lg2[depth[u]] && anc[u][i] != anc[v][i]) {
			ans = std::min(ans, minnum[u][i]);
			ans = std::min(ans, minnum[v][i]);
			u = anc[u][i];
			v = anc[v][i];
		}
	}
	ans = std::min(ans, minnum[u][0]);
	ans = std::min(ans, minnum[v][0]);
	return ans;
}

int main() {
	int n, q;
	read(n), read(q);
	next = new std::vector<Edge>[n + 1];
	for (int i = 1, u, v, w; i < n; i++) {
		read(u), read(v), read(w);
		next[u].push_back({v, w});
		next[v].push_back({u, w});
	}
	lg2 = new int[n + 1], depth = new int[n + 1];
	anc = new int*[n + 1], minnum = new int*[n + 1];
	lg2[0] = 0;
	for (int i = 1; i <= n; i++) {
		lg2[i] = lg2[i - 1] + (i == (1 << lg2[i - 1]));
	}
	depth[1] = 0;
	dfs(1, 0);
	for (int i = 0, u, v; i < q; i++) {
		read(u), read(v);
		write(query(u, v));
	}
	return 0;
}