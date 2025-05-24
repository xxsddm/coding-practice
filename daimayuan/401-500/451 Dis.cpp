// http://oj.daimayuan.top/problem/451

#include "vector"
#include "iostream"

using namespace std;

int *nums, *container, *lg, *depth, **anc;

void dfs(int node, int prevNode, vector<int> *next) {
	depth[node] = depth[prevNode] + 1;
	if (depth[node]) {
		anc[node] = new int[lg[depth[node]]];
		anc[node][0] = prevNode;
		for (int i = 1, limit = lg[depth[node]]; i < limit; i++) {
			anc[node][i] = anc[anc[node][i - 1]][i - 1];
		}
	}
	int &num = container[node];
	for (int &nextNode : next[node]) {
		if (nextNode == prevNode) {
			continue;
		}
		container[nextNode] ^= num;
		dfs(nextNode, node, next);
	}
}

int lca(int u, int v) {
	if (depth[u] < depth[v]) {
		swap(u, v);
	}
	while (depth[u] > depth[v]) {
		u = anc[u][lg[depth[u] - depth[v]] - 1];
	}
	if (u == v) {
		return u;
	}
	for (int i = lg[depth[u]] - 1; i >= 0; i--) {
		if (anc[u][i] != anc[v][i]) {
			u = anc[u][i], v = anc[v][i];
		}
	}
	return anc[u][0];
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	nums = new int[n + 1], container = new int[n + 1];
	lg = new int[n + 1], depth = new int[n + 1];
	anc = new int*[n + 1];
	vector<int> next[n + 1];
	lg[0] = 0, depth[0] = -1;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &nums[i]);
		container[i] = nums[i];
	}
	for (int i = 1; i < n; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		next[u].push_back(v);
		next[v].push_back(u);
	}
	// lg[i] -> log2(i) + 1
	for (int i = 1; i <= n; i++) {
		lg[i] = lg[i - 1] + ((1 << lg[i - 1]) == i ? 1 : 0);
	}
	dfs(1, 0, next);
	for (int i = 0; i < m; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		printf("%d\n", (container[u] ^ container[v] ^ nums[lca(u, v)]));
	}
	return 0;
}
