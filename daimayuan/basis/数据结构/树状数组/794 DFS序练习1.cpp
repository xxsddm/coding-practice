// http://oj.daimayuan.top/course/15/problem/794

#include "vector"
#include "iostream"

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

int n, length = 1;
int *idx, *size, *nums;
long long *tree1, *tree2;
std::vector<int> *next;

void dfs(int node, int prevnode) {
	idx[node] = length++;
	int cur = idx[node];
	size[cur] = 1;
	for (int &nextnode : next[node]) {
		if (nextnode == prevnode) {
			continue;
		}
		dfs(nextnode, node);
		size[cur] += size[idx[nextnode]];
	}
}

void change(int cur, long long delta, long long *tree) {
	while (cur <= n) {
		tree[cur] += delta;
		cur += cur & -cur;
	}
}

long long query(int cur, long long *tree) {
	long long ans = 0;
	while (cur) {
		ans += tree[cur];
		cur ^= cur & -cur;
	}
	return ans;
}

int main() {
	int q;
	read(n), read(q);
	idx = new int[n + 1];
	size = new int[n + 1], nums = new int[n + 1];
	tree1 = new long long[n + 1], tree2 = new long long[n + 1];
	next = new std::vector<int>[n + 1];
	for (int i = 1, u, v; i < n; i++) {
		read(u), read(v);
		next[u].push_back(v);
		next[v].push_back(u);
		tree1[i] = tree2[i] = 0;
	}
	tree1[n] = tree2[n] = 0;
	dfs(1, 0);
	for (int i = 1; i <= n; i++) {
		read(nums[i]);
		change(idx[i], nums[i], tree1);
		change(idx[i], nums[i], tree2);
		change(idx[i] + size[idx[i]], - nums[i], tree2);
	}
	for (int i = 0, op, x, y; i < q; i++) {
		read(op), read(x);
		if (op == 1) {
			read(y);
			change(idx[x], y - nums[x], tree1);
			// 子树中任意节点到根节点路径均包含idx[x]值
			change(idx[x], y - nums[x], tree2);
			change(idx[x] + size[idx[x]], nums[x] - y, tree2);
			nums[x] = y;
		} else {
			write(query(idx[x] + size[idx[x]] - 1, tree1) - query(idx[x] - 1, tree1));
			putchar(' ');
			write(query(idx[x], tree2));
			putchar('\n');
		}
	}
	return 0;
}
