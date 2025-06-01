// http://oj.daimayuan.top/course/15/problem/818

#include "vector"
#include "unordered_map"
#include "iostream"

typedef long long ll;

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

int total = 0, k, ans = 1 << 20;
int *node2idx, *idx2node, *depth, *size, *hson;
ll *dist;
std::vector<std::pair<int, int>> *adj;
std::unordered_map<ll, int> memo;

int dfs1(int node, int prevnode) {
	node2idx[node] = total;
	idx2node[total++] = node;
	size[node] = 1, hson[node] = -1;
	int maxsize = 0;
	for (auto &[nextnode, weight] : adj[node]) {
		if (nextnode == prevnode) {
			continue;
		}
		depth[nextnode] = depth[node] + 1;
		dist[nextnode] = dist[node] + weight;
		int temp = dfs1(nextnode, node);
		size[node] += temp;
		if (temp > maxsize) {
			hson[node] = nextnode;
			maxsize = temp;
		}
	}
	return size[node];
}

void dfs2(int node, int prevnode, bool heavy) {
	// 轻节点
	for (auto &[nextnode, weight] : adj[node]) {
		if (nextnode == prevnode || nextnode == hson[node]) {
			continue;
		}
		dfs2(nextnode, node, false);
	}
	// 重节点
	if (hson[node] != -1) {
		dfs2(hson[node], node, true);
	}
	// 自身
	if (memo.count(dist[node] + k)) {
		ans = std::min(ans, memo[dist[node] + k] - depth[node]);
	}
	if (memo.count(dist[node])) {
		memo[dist[node]] = std::min(memo[dist[node]], depth[node]);
	} else {
		memo[dist[node]] = depth[node];
	}
	// 加入dfs中被消除的轻节点
	for (auto &[nextnode, weight] : adj[node]) {
		if (nextnode == prevnode || nextnode == hson[node]) {
			continue;
		}
		for (int i = node2idx[nextnode], limit = i + size[nextnode], cur; i < limit; i++) {
			cur = idx2node[i];
			ll key = dist[node] * 2 - dist[cur] + k;
			if (memo.count(key)) {
				ans = std::min(ans, memo[key] + depth[cur] - depth[node] * 2);
			}
		}
		for (int i = node2idx[nextnode], limit = i + size[nextnode], temp; i < limit; i++) {
			temp = depth[idx2node[i]];
			ll key = dist[idx2node[i]];
			if (memo.count(key)) {
				memo[key] = std::min(memo[key], temp);
			} else {
				memo[key] = temp;
			}
		}
	}

	if (!heavy) {
		memo.clear();
	}
}

int main() {
	int n;
	read(n), read(k);
	node2idx = new int[n], idx2node = new int[n];
	depth = new int[n], dist = new long long[n];
	size = new int[n], hson = new int[n];
	adj = new std::vector<std::pair<int, int>>[n];
	for (int i = 1, x, y, w; i < n; i++) {
		read(x), read(y), read(w);
		adj[x].emplace_back(y, w);
		adj[y].emplace_back(x, w);
	}
	depth[0] = 0, dist[0] = 0;
	dfs1(0, -1);
	dfs2(0, -1, true);
	write(ans == (1 << 20) ? -1 : ans);
	return 0;
}