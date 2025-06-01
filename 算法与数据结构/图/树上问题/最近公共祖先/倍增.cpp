// https://www.luogu.com.cn/problem/P3379

#include "vector"
#include "iostream"

using namespace std;

int *lg, *depth, **anc;

void dfs(int node, int prevNode, vector<int> *next) {
	depth[node] = depth[prevNode] + 1;
	anc[node] = new int[max(lg[depth[node]], 1)];
	anc[node][0] = prevNode;
	for (int i = 1, limit = lg[depth[node]]; i < limit; i++) {
		anc[node][i] = anc[anc[node][i - 1]][i - 1];
	}
	for (int &nextNode : next[node]) {
		if (nextNode == prevNode) {
			continue;
		}
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
		if (i < lg[depth[u]] && anc[u][i] != anc[v][i]) {
			u = anc[u][i], v = anc[v][i];
		}
	}
	return anc[u][0];
}

int main() {	// LCA(倍增)
	int N, M, S, u, v;
	scanf("%d %d %d", &N, &M, &S);
	lg = new int[N + 1], depth = new int[N + 1];
	anc = new int*[N + 1];
	vector<int> next[N + 1];
	for (int i = 1; i < N; i++) {
		scanf("%d %d", &u, &v);
		next[u].push_back(v);
		next[v].push_back(u);
	}
	lg[0] = 0, depth[0] = -1;
	// lg[i] -> log2(i) + 1
	for (int i = 1; i <= N; i++) {
		lg[i] = lg[i - 1] + (i == (1 << lg[i - 1]));
	}
	dfs(S, 0, next);
	for (int i = 0; i < M; i++) {
		scanf("%d %d", &u, &v);
		printf("%d\n", lca(u, v));
	}
	return 0;
}
