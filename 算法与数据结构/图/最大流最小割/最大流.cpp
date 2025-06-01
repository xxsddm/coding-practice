// http://oj.daimayuan.top/course/23/problem/1058

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using std::queue;
using std::vector;

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
	int v;
	long long rest;
} *edges;

vector<int> *adj;

int count = 0, n, start, end;
int *dist, *first;

void addEdge(int from, int to, long long rest) {
	edges[count].v = to, edges[count].rest = rest;
	adj[from].push_back(count++);
	edges[count].v = from, edges[count].rest = 0;
	adj[to].push_back(count++);
}

bool bfs() {
	queue<int> q;
	q.push(start);
	memset(first + 1, 0, sizeof(int) * n);
	memset(dist + 1, 0, sizeof(int) * n);
	dist[start] = 1;
	while (!dist[end] && !q.empty()) {
		int node = q.front();
		q.pop();
		for (int &i : adj[node]) {
			if (edges[i].rest && dist[edges[i].v] == 0) {
				dist[edges[i].v] = dist[node] + 1;
				q.push(edges[i].v);
			}
		}
	}
	return dist[end];
}

long long dfs(int node, long long limit) {
	if (node == end || limit == 0) {
		return limit;
	}
	long long ans = 0;
	for (int &i = first[node], j, tempDist = dist[node] + 1, size = (int) adj[node].size(); i < size && limit; i++) {
		j = adj[node][i];
		Edge &e = edges[j];
		if (dist[e.v] != tempDist) {
			continue;
		}
		long long temp = dfs(e.v, std::min(limit, e.rest));
		e.rest -= temp;
		edges[j ^ 1].rest += temp;
		if (node != start) {
			limit -= temp;
		}
		ans += temp;
	}
	return ans;
}

int main() {
	int m;
	read(n), read(m), read(start), read(end);
	adj = new vector<int>[n + 1];
	dist = new int[n + 1], first = new int[n + 1];
	edges = new Edge[m << 1];
	for (int i = 0, u, v, c; i < m; i++) {
		read(u), read(v), read(c);
		addEdge(u, v, c);
	}
	long long ans = 0;
	while (bfs()) {
		ans += dfs(start, 1LL << 60);
	}
	write(ans);
	return 0;
}
