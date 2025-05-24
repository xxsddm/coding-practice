// https://www.luogu.com.cn/problem/P3425

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using std::vector;
using std::queue;

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

struct Edge {
	int to, rest, idx, status;
	Edge(int a, int b, int c, int d): to(a), rest(b), idx(c), status(d) {}
};

int count = 0, start, end, length, *dist, *first, *container;
vector<int> *adj;
vector<Edge> edges;

void addEdge(int u, int v, int c, int idx = -1, int status = -1) {
	edges.emplace_back(v, c, idx, status);
	edges.emplace_back(u, 0, -1, -1);
	adj[u].push_back(count++);
	adj[v].push_back(count++);
}

bool bfs() {
	memset(dist, 0, sizeof(int) * length);
	memset(first, 0, sizeof(int) * length);
	dist[start] = 1;
	queue<int> q;
	q.push(start);
	while (!dist[end] && !q.empty()) {
		int node = q.front();
		q.pop();
		for (int &j : adj[node]) {
			int &nextnode = edges[j].to, &rest = edges[j].rest;
			if (rest && dist[nextnode] == 0) {
				dist[nextnode] = dist[node] + 1;
				q.push(nextnode);
			}
		}
	}
	return dist[end];
}

int dfs(int node, int limit) {
	if (node == end) {
		return limit;
	}
	int ans = 0;
	for (int &i = first[node], j = dist[node] + 1, size = (int) adj[node].size(); i < size; i++) {
		int &nextnode = edges[adj[node][i]].to, &rest = edges[adj[node][i]].rest;
		if (rest == 0 || dist[nextnode] != j) {
			continue;
		}
		int temp = dfs(nextnode, std::min(limit, rest));
		rest -= temp;
		edges[adj[node][i] ^ 1].rest += temp;
		ans += temp;
		if (limit != start) {
			limit -= temp;
			if (limit == 0) {
				return ans;
			}
		}
	}
	return ans;
}

int calculate(int count) {
	for (int i = 0, size = (int) edges.size(); i < size; i += 2) {
		edges[i].rest += edges[i ^ 1].rest;
		edges[i ^ 1].rest = 0;
	}
	for (int &i : adj[start]) {
		edges[i].rest = count;
	}
	int ans = 0;
	while (bfs()) {
		ans += dfs(start, 1 << 30);
	}
	return ans;
}

int main() {	// 各比赛建点, 限流1
	int n, m;
	read(n), read(m);
	start = n + m + 1, end = start + 1, length = end + 1;
	dist = new int[length], first = new int[length], container = new int[m + 1];
	adj = new vector<int>[length];
	for (int i = 1, a, b; i <= m; i++) {	// 比赛节点设置为i+n
		read(a), read(b);
		addEdge(i + n, end, 1);
		addEdge(a, i + n, 1, i, 1);
		addEdge(b, i + n, 1, i, 0);
	}
	for (int i = 1; i <= n ; i++) {
		addEdge(start, i, 0);
	}
	int left = 1, right = m;
	while (left <= right) {
		int mid = (left + right) >> 1;
		if (calculate(mid) >= m) {
			right = mid - 1;
		} else {
			left = mid + 1;
		}
	}
	calculate(left);
	write(left);
	for (Edge &edge : edges) {
		if (edge.status != -1 && edge.rest == 0) {
			container[edge.idx] = edge.status;
		}
	}
	for (int i = 1; i <= m; i++) {
		write(container[i]);
	}
	return 0;
}
