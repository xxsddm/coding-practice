// https://codeforces.com/contest/1051/problem/F

#include "unordered_set"
#include "algorithm"
#include "vector"
#include "queue"
#include "iostream"

using namespace std;

struct Edge {
	int u, v, w;
	bool operator < (Edge &other) {
		return w < other.w;
	}
} *edges;

int n, *root, *counter, *lg, *depth, **anc;
long long inf = 1e18, *container, **dist;
bool *used;

int find(int idx) {
	while (idx != root[idx]) {
		root[idx] = root[root[idx]];
		idx = root[idx];
	}
	return idx;
}

bool merge(int &node1, int &node2) {
	int idx1 = find(node1), idx2 = find(node2);
	if (idx1 == idx2) {
		return false;
	}
	if (counter[idx1] >= counter[idx2]) {
		counter[idx1] += counter[idx2];
		root[idx2] = idx1;
	} else {
		counter[idx2] += counter[idx1];
		root[idx1] = idx2;
	}
	return true;
}

void dfs(int node, int prevNode, vector<pair<int, int>> *next) {
	depth[node] = depth[prevNode] + 1;
	int length = lg[depth[node]];
	if (length) {
		anc[node] = new int[length];
		anc[node][0] = prevNode;
		for (int i = 1, limit = length; i < limit; i++) {
			anc[node][i] = anc[anc[node][i - 1]][i - 1];
		}
	}
	for (auto &edge : next[node]) {
		if (edge.first == prevNode) {
			continue;
		}
		int &nextNode = edge.first;
		container[nextNode] = container[node] + edge.second;
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
		if (i <= lg[depth[u]] - 1 && anc[u][i] != anc[v][i]) {
			u = anc[u][i], v = anc[v][i];
		}
	}
	return anc[u][0];
}

void dijkstra(int start, int idx, vector<pair<int, int>> *next) {
	int count = 0;
	for (int i = 1; i <= n; i++) {
		dist[idx][i] = inf;
		used[i] = false;
	}
	dist[idx][start] = 0;
	priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
	pq.emplace(0, start);
	while (!pq.empty() && count < n) {
		pair<long long, int> p = pq.top();
		pq.pop();
		int node = p.second;
		if (used[node]) {
			continue;
		}
		used[node] = true;
		count++;
		for (auto &nextp : next[node]) {
			if (used[nextp.first]) {
				continue;
			}
			int &nextNode = nextp.first, &nextW = nextp.second;
			if (dist[idx][nextNode] > dist[idx][node] + nextW) {
				dist[idx][nextNode] = dist[idx][node] + nextW;
				pq.emplace(dist[idx][nextNode], nextNode);
			}
		}
	}
}

int main() {
	int m;
	scanf("%d %d", &n, &m);
	root = new int[n + 1], counter = new int[n + 1];
	lg = new int[n + 1], depth = new int[n + 1];
	used = new bool[n + 1];
	container = new long long[n + 1];
	anc = new int*[n + 1];
	edges = new Edge[m];
	vector<int> back;
	vector<pair<int, int>> next[n + 1];
	for (int i = 1; i <= n; i++) {
		root[i] = i;
		counter[i] = 1;
	}
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
	}
	sort(edges, edges + m);
	for (int i = 0; i < m; i++) {
		Edge &edge = edges[i];
		if (merge(edge.u, edge.v)) {
			next[edge.u].emplace_back(edge.v, edge.w);
			next[edge.v].emplace_back(edge.u, edge.w);
		} else {
			back.push_back(i);
		}
	}
	delete []root;
	delete []counter;
	lg[0] = 0, depth[0] = -1, container[1] = 0;
	for (int i = 1; i <= n; i++) {
		lg[i] = lg[i - 1] + (1 << lg[i - 1] == i ? 1 : 0);
	}
	dfs(1, 0, next);
	unordered_set<int> memo;
	for (int &i : back) {
		auto &edge = edges[i];
		next[edge.u].emplace_back(edge.v, edge.w);
		next[edge.v].emplace_back(edge.u, edge.w);
		memo.insert(edge.u);
	}
	int idx = 0;
	if (!memo.empty()) {
		dist = new long long*[memo.size()];
		for (int source : memo) {
			dist[idx] = new long long[n + 1];
			dijkstra(source, idx++, next);
		}
	}
	int q;
	scanf("%d", &q);
	while (q--) {
		int u, v;
		scanf("%d %d", &u, &v);
		long long ans = container[u] + container[v] - 2 * container[lca(u, v)];
		for (int i = 0; i < idx; i++) {
			ans = min(ans, dist[i][u] + dist[i][v]);
		}
		printf("%lld\n", ans);
	}
	return 0;
}