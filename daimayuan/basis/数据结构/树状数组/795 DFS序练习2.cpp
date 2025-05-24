// http://oj.daimayuan.top/course/15/problem/795

#include "vector"
#include "iostream"

typedef long long ll;

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

int numstk[30];

template <typename T>
inline void write(T x) {
	int length = 0;
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	while (x > 9) {
		numstk[length++] = x % 10;
		x /= 10;
	}
	numstk[length++] = x;
	for (int i = length - 1; i >= 0; i--) {
		putchar(numstk[i] ^ 48);
	}
}

int root = 1, count = 1, n, *nums, *idx, *size, *depth, *lg2;
int **anc;
ll total = 0, *tree;
vector<int> *adj;

int dfs(int node, int prevnode) {
	idx[node] = count++;
	int cur = idx[node], prev = idx[prevnode];
	size[cur] = 1;
	depth[cur] = depth[prev] + 1;
	int length = lg2[depth[cur]];
	if (length) {
		anc[cur] = new int[length];
		anc[cur][0] = prev;
		for (int i = 1; i < length; i++) {
			anc[cur][i] = anc[anc[cur][i - 1]][i - 1];
		}
	}
	for (int &nextnode : adj[node]) {
		if (nextnode == prevnode) {
			continue;
		}
		size[cur] += dfs(nextnode, node);
	}
	return size[cur];
}

void change(int cur, long long delta) {
	while (cur <= n) {
		tree[cur] += delta;
		cur += cur & -cur;
	}
}

ll query(int cur) {
	ll ans = 0;
	while (cur) {
		ans += tree[cur];
		cur ^= cur & -cur;
	}
	return ans;
}

ll op2(int x) {
	// 1. x为根节点, 子树和即 总和
	if (x == root) {
		return total;
	}
	int u = idx[x], v = idx[root];
	// 2. root不为x子节点(dfs序), 子树和即 x的dfs序子树和
	if (u > v || u + size[u] <= v) {
		return query(u + size[u] - 1) - query(u - 1);
	}
	// 3. root为x子节点(dfs序), 子树和即 总和 - x连向root的子节点dfs序子树和
	swap(u, v);
	for (int i = lg2[depth[u] - depth[v]] - 1; i >= 0; i--) {
		if (i < lg2[depth[u]] && depth[anc[u][i]] > depth[v]) {
			u = anc[u][i];
		}
	}
	return total - query(u + size[u] - 1) + query(u - 1);
}

int main() {
	int q;
	read(n), read(q);
	nums = new int[n + 1], idx = new int[n + 1];
	size = new int[n + 1], depth = new int[n + 1], lg2 = new int[n];
	anc = new int*[n + 1];
	tree = new ll[n + 1];
	adj = new vector<int>[n + 1];
	lg2[0] = 0;
	tree[n] = 0;
	for (int i = 1, u, v; i < n; i++) {
		read(u), read(v);
		adj[u].push_back(v);
		adj[v].push_back(u);
		tree[i] = 0;
		lg2[i] = lg2[i - 1] + (i == (1 << lg2[i - 1]));
	}
	depth[0] = -1, idx[0] = 0;
	dfs(root, 0);
	for (int i = 1; i <= n; i++) {
		read(nums[i]);
		total += nums[i];
		change(idx[i], nums[i]);
	}
	for (int i = 0, op, x, y; i < q; i++) {
		read(op), read(x);
		if (op == 1) {
			read(y);
			total = total - nums[x] + y;
			change(idx[x], y - nums[x]);
			nums[x] = y;
		} else if (op == 2) {
			write(op2(x));
		} else {
			root = x;
		}
	}
	return 0;
}
