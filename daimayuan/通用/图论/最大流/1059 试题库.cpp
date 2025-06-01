// http://oj.daimayuan.top/course/23/problem/1059

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
	putchar(' ');
}

struct Edge {
	int to, rest;
};

int count = 0, start, end, length, *dist, *first;
vector<int> *adj, *container;
vector<Edge> edges;

void addEdge(int u, int v, int c) {
	adj[u].push_back(count++);
	adj[v].push_back(count++);
	edges.push_back({v, c});
	edges.push_back({u, 0});
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
			auto &[nextnode, rest] = edges[j];
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
		auto &[nextnode, rest] = edges[adj[node][i]];
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

int main() {
	int k, n;
	read(k), read(n);
	start = n + k + 1, end = start + 1, length = end + 1;
	int total = 0, ans = 0;
	dist = new int[length], first = new int[length];
	adj = new vector<int>[length], container = new vector<int>[k + 1];
	for (int i = 1, j; i <= k; i++) {
		read(j);
		addEdge(i + n, end, j);
		total += j;
	}
	for (int i = 1, j, l; i <= n; i++) {
		addEdge(start, i, 1);
		read(j);
		for (int m = 0; m < j; m++) {
			read(l);
			addEdge(i, l + n, 1);
		}
	}
	while (bfs()) {
		ans += dfs(start, 0x7fffffff);
	}
	if (ans != total) {
		puts("No Solution!");
		return 0;
	}
	for (int i = 1; i <= n; i++) {
		for (int &j : adj[i]) {
			if (edges[j].to == start || edges[j].rest == 1) {
				continue;
			}
			container[edges[j].to - n].push_back(i);
		}
	}
	for (int i = 1; i <= k; i++) {
		printf("%d: ", i);
		for (int &j : container[i]) {
			write(j);
		}
		putchar('\n');
	}
	return 0;
}
