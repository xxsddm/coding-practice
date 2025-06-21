// http://oj.daimayuan.top/course/15/problem/819

#include "vector"
#include "iostream"

using namespace std;

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

struct info {
	int val, cumsum;
} *container;

char command[7];
int n, total = 1, *node2idx, *idx2node, *depth, *pre, *top, *sz, *hson;
vector<int> *adj;

int dfs1(int node, int prevnode) {
	int maxsize = 0;
	depth[node] = depth[prevnode] + 1;
	pre[node] = prevnode;
	sz[node] = 1;
	hson[node] = 0;
	for (int &nextnode : adj[node]) {
		if (nextnode != prevnode) {
			int temp = dfs1(nextnode, node);
			sz[node] += temp;
			if (temp > maxsize) {
				maxsize = temp;
				hson[node] = nextnode;
			}
		}
	}
	return sz[node];
}

void dfs2(int node, int prevnode) {
	top[node] = node == hson[prevnode] ? top[prevnode] : node;
	int idx = total++;
	node2idx[node] = idx, idx2node[idx] = node;
	if (hson[node]) {
		dfs2(hson[node], node);
	}
	for (int &nextnode : adj[node]) {
		if (nextnode != prevnode && nextnode != hson[node]) {
			dfs2(nextnode, node);
		}
	}
}

void change(int cur, int start, int end, int idx, int val) {
	if (start == end) {
		container[cur].val = container[cur].cumsum = val;
		return;
	}
	int mid = (start + end) >> 1;
	int next1 = cur << 1, next2 = next1 ^ 1;
	if (idx <= mid) {
		change(next1, start, mid, idx, val);
	} else {
		change(next2, mid + 1, end, idx, val);
	}
	container[cur].val = max(container[next1].val, container[next2].val);
	container[cur].cumsum = container[next1].cumsum + container[next2].cumsum;
}

int querymax(int cur, int start, int end, int left, int right) {
	if (left <= start && right >= end) {
		return container[cur].val;
	}
	int mid = (start + end) >> 1;
	int next1 = cur << 1, next2 = next1 ^ 1;
	if (right <= mid) {
		return querymax(next1, start, mid, left, right);
	} else if (left > mid) {
		return querymax(next2, mid + 1, end, left, right);
	}
	return max(querymax(next1, start, mid, left, right),
	           querymax(next2, mid + 1, end, left, right));
}

int querysum(int cur, int start, int end, int left, int right) {
	if (left <= start && right >= end) {
		return container[cur].cumsum;
	}
	int mid = (start + end) >> 1;
	int next1 = cur << 1, next2 = next1 ^ 1;
	if (right <= mid) {
		return querysum(next1, start, mid, left, right);
	} else if (left > mid) {
		return querysum(next2, mid + 1, end, left, right);
	}
	return querysum(next1, start, mid, left, right) +
	       querysum(next2, mid + 1, end, left, right);
}

int qmax(int node1, int node2) {
	int ans = 0x80000000;
	while (top[node1] != top[node2]) {
		if (depth[top[node1]] < depth[top[node2]]) {
			swap(node1, node2);
		}
		ans = max(ans, querymax(1, 1, n, node2idx[top[node1]], node2idx[node1]));
		node1 = pre[top[node1]];
	}
	if (node2idx[node1] > node2idx[node2]) {
		swap(node1, node2);
	}
	ans = max(ans, querymax(1, 1, n, node2idx[node1], node2idx[node2]));
	return ans;
}

int qsum(int node1, int node2) {
	int ans = 0;
	while (top[node1] != top[node2]) {
		if (depth[top[node1]] < depth[top[node2]]) {
			swap(node1, node2);
		}
		ans += querysum(1, 1, n, node2idx[top[node1]], node2idx[node1]);
		node1 = pre[top[node1]];
	}
	if (node2idx[node1] > node2idx[node2]) {
		swap(node1, node2);
	}
	ans += querysum(1, 1, n, node2idx[node1], node2idx[node2]);
	return ans;
}

int main() {
	int q;
	read(n);
	node2idx = new int[n + 1], idx2node = new int[n + 1], depth = new int[n + 1];
	pre = new int[n + 1], top = new int[n + 1];
	sz = new int[n + 1], hson = new int[n + 1];
	adj = new vector<int>[n + 1];
	container = new info[n << 2];
	for (int i = 1, u, v; i < n; i++) {
		read(u), read(v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	depth[0] = hson[0] = 0;
	dfs1(1, 0);
	dfs2(1, 0);
	for (int i = 1, w; i <= n; i++) {
		read(w);
		change(1, 1, n, node2idx[i], w);
	}
	read(q);
	for (int i = 0, u, v; i < q; i++) {
		scanf("%s", command);
		read(u), read(v);
		if (command[1] == 'H') {
			change(1, 1, n, node2idx[u], v);
		} else if (command[1] == 'M') {
			write(qmax(u, v));
		} else {
			write(qsum(u, v));
		}
	}
	return 0;
}