#include "vector"
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
	numstk[length++] = x % 10;
	for (int i = length - 1; i >= 0; i--) {
		putchar(numstk[i] ^ 48);
	}
	putchar('\n');
}

int N, idx = 1, mod, *nums;
int *prev, *hson, *depth, *size, *first, *rank, *rank2idx;
int *tree, *lazy;
std::vector<int> *next;

int dfs1(int node) {
	int temp = 0, prevNode = prev[node];
	size[node] = 1;
	hson[node] = 0;
	depth[node] = depth[prevNode] + 1;
	for (int &nextNode : next[node]) {
		if (nextNode != prevNode) {
			prev[nextNode] = node;
			size[node] += dfs1(nextNode);
			if (size[nextNode] > temp) {
				temp = nextNode;
			}
		}
	}
	hson[node] = temp;	// 重子节点为子树最大子节点
	return size[node];
}

void dfs2(int node) {	// 重链遍历
	int prevNode = prev[node];
	rank[node] = idx;	// 重链遍历顺序
	rank2idx[idx] = node;
	idx++;
	if (hson[node]) {
		first[hson[node]] = first[node];
		dfs2(hson[node]);
	}
	for (int &nextNode : next[node]) {
		if (nextNode == prevNode) {
			continue;
		}
		if (nextNode != hson[node]) {
			first[nextNode] = nextNode;
			dfs2(nextNode);
		}
	}
}

void build(int node, int start, int end) {
	lazy[node] = 0;
	if (start == end) {
		tree[node] = nums[rank2idx[start]];
		return;
	}
	int nextNode1 = node << 1, nextNode2 = nextNode1 ^ 1, mid = (start + end) >> 1;
	build(nextNode1, start, mid);
	build(nextNode2, mid + 1, end);
	tree[node] = ((long long) tree[nextNode1] + tree[nextNode2]) % mod;
}

void change(int node, int start, int end, int left, int right, int delta) {
	if (right < start || left > end) {
		return;
	}
	if (start >= left && end <= right) {
		tree[node] += ((long long) end - start + 1) * delta % mod;
		if (start != end) {
			lazy[node] = ((long long) lazy[node] + delta) % mod;
		}
		return;
	}
	int nextNode1 = node << 1, nextNode2 = nextNode1 ^ 1, mid = (start + end) >> 1;
	if (lazy[node]) {
		tree[nextNode1] = (((long long) mid - start + 1) * lazy[node] + tree[nextNode1]) % mod;
		tree[nextNode2] = (((long long) end - mid) * lazy[node] + tree[nextNode2]) % mod;
		lazy[nextNode1] = ((long long) lazy[nextNode1] + lazy[node]) % mod;
		lazy[nextNode2] = ((long long) lazy[nextNode2] + lazy[node]) % mod;
		lazy[node] = 0;
	}
	change(nextNode1, start, mid, left, right, delta);
	change(nextNode2, mid + 1, end, left, right, delta);
	tree[node] = ((long long) tree[nextNode1] + tree[nextNode2]) % mod;
}

int query(int node, int start, int end, int left, int right) {
	if (right < start || left > end) {
		return 0;
	}
	if (start >= left && end <= right) {
		return tree[node];
	}
	int nextNode1 = node << 1, nextNode2 = nextNode1 ^ 1, mid = (start + end) >> 1;
	if (lazy[node]) {
		tree[nextNode1] = (((long long) mid - start + 1) * lazy[node] + tree[nextNode1]) % mod;
		tree[nextNode2] = (((long long) end - mid) * lazy[node] + tree[nextNode2]) % mod;
		lazy[nextNode1] = ((long long) lazy[nextNode1] + lazy[node]) % mod;
		lazy[nextNode2] = ((long long) lazy[nextNode2] + lazy[node]) % mod;
		lazy[node] = 0;
	}
	return ((long long) query(nextNode1, start, mid, left, right) +
	        query(nextNode2, mid + 1, end, left, right)) % mod;
}

void op1(int u, int v, int delta) {
	while (first[u] != first[v]) {
		if (depth[first[u]] > depth[first[v]]) {
			std::swap(u, v);
		}
		change(1, 1, N, rank[first[v]], rank[v], delta);
		v = prev[first[v]];
	}
	if (depth[u] > depth[v]) {
		std::swap(u, v);
	}
	change(1, 1, N, rank[u], rank[v], delta);
}

int op2(int u, int v) {
	int ans = 0;
	while (first[u] != first[v]) {
		if (depth[first[u]] > depth[first[v]]) {
			std::swap(u, v);
		}
		ans = ((long long) ans + query(1, 1, N, rank[first[v]], rank[v])) % mod;
		v = prev[first[v]];
	}
	if (depth[u] > depth[v]) {
		std::swap(u, v);
	}
	ans = ((long long) ans + query(1, 1, N, rank[u], rank[v])) % mod;
	return ans;
}

// DFS遍历标记重子节点和重链遍历索引, 利用遍历索引构建线段树维护索引区间信息
int main() {	// 洛谷P3384测试通过
	int M, root;
	read(N), read(M), read(root), read(mod);
	int length = N << 2;
	nums = new int[N + 1];
	prev = new int[N + 1], hson = new int[N + 1], depth = new int[N + 1], size = new int[N + 1];
	first = new int[N + 1], rank = new int[N + 1], rank2idx = new int[N + 1];
	tree = new int[length], lazy = new int[length];
	next = new std::vector<int>[N + 1];
	for (int i = 1; i <= N; i++) {
		read(nums[i]);
	}
	for (int i = 1, x, y; i < N; i++) {
		read(x), read(y);
		next[x].push_back(y);
		next[y].push_back(x);
	}
	prev[root] = 0;
	depth[0] = 0;
	first[root] = root;
	dfs1(root);
	dfs2(root);
	build(1, 1, N);
	for (int i = 0, op, x, y, z; i < M; i++) {
		read(op), read(x);
		if (op == 1) {
			read(y), read(z);
			op1(x, y, z % mod);
		} else if (op == 2) {
			read(y);
			write(op2(x, y));
		} else if (op == 3) {
			read(z);
			// 根据子树大小推断右端点
			change(1, 1, N, rank[x], rank[x] + size[x] - 1, z % mod);
		} else {
			write(query(1, 1, N, rank[x], rank[x] + size[x] - 1));
		}
	}
	return 0;
}
