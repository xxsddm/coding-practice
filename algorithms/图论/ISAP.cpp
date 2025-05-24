#include "queue"
#include "vector"
#include "cstring"
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

int idx = 0, n, start, end, *dist, *gap, *first;
std::vector<int> *next;

struct Edge {
	int to, w;
} *edges;

void addEdge(int u, int v, int w) {
	next[u].push_back(idx);
	next[v].push_back(idx ^ 1);
	edges[idx].to = v;
	edges[idx ^ 1].to = u;
	edges[idx].w = w;
	edges[idx ^ 1].w = 0;
	idx += 2;
}

bool bfs() {
	memset(dist, -1, sizeof(int) * (n + 1));
	memset(gap, 0, sizeof(int) * (n + 1));
	std::queue<int> q;
	dist[end] = 0;
	gap[0]++;
	q.push(end);
	while (!q.empty()) {
		int node = q.front();
		q.pop();
		for (int &i : next[node]) {
			int &nextNode = edges[i].to;
			if (edges[i ^ 1].w && dist[nextNode] == -1) {
				dist[nextNode] = dist[node] + 1;
				gap[dist[nextNode]]++;
				q.push(nextNode);
			}
		}
	}
	return dist[start] != -1;
}

long long dfs(int node, int limit) {
	if (node == end || limit == 0) {
		return limit;
	}
	long long ans = 0;
	for (int i = first[node], size = (int) next[node].size(); i < size; i++, first[node]++) {
		int &j = next[node][i], nextNode = edges[j].to;
		if (dist[nextNode] + 1 != dist[node] || !edges[j].w) {
			continue;
		}
		int temp = (int) dfs(nextNode, std::min(edges[j].w, limit));
		if (!temp) {
			continue;
		}
		edges[j].w -= temp;
		edges[j ^ 1].w += temp;
		ans += temp;
		if (node != start) {
			limit -= temp;
			if (limit == 0) {
				return ans;
			}
		}
	}
	// 还有剩余流量时提高与汇点距离, 重置弧优化
	if (--gap[dist[node]] == 0) {
		dist[start] = n;
	}
	gap[++dist[node]]++;
	first[node] = 0;
	return ans;
}

int main() {	// 洛谷P3376测试通过
	int m;
	read(n), read(m), read(start), read(end);
	dist = new int[n + 1], gap = new int[n + 1], first = new int[n + 1];
	next = new std::vector<int>[n + 1];
	edges = new Edge[m << 1];
	for (int i = 0, u, v, w; i < m; i++) {
		read(u), read(v), read(w);
		addEdge(u, v, w);
	}
	if (!bfs()) {
		printf("0");
		return 0;
	}
	long long ans = 0;
	memset(first, 0, sizeof(int) * (n + 1));
	while (dist[start] < n) {
		ans += dfs(start, 0x7fffffff);
	}
	printf("%lld", ans);
	return 0;
}