// http://oj.daimayuan.top/course/15/problem/659

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
	while (x > 9) {
		numstk[length++] = x % 10;
		x /= 10;
	}
	numstk[length++] = x;
	for (int i = length - 1; i >= 0; i--) {
		putchar(numstk[i] ^ 48);
	}
	putchar('\n');
}

long long *maxnum, *lazy;

void build(int node, int start, int end, int idx, int num) {
	if (start > idx || end < idx) {
		return;
	}
	lazy[node] = 0;
	if (start == end) {
		maxnum[node] = num;
		return;
	}
	int mid = (start + end) >> 1;
	int leftnode = node << 1, rightnode = leftnode ^ 1;
	build(leftnode, start, mid, idx, num);
	build(rightnode, mid + 1, end, idx, num);
	maxnum[node] = std::max(maxnum[leftnode], maxnum[rightnode]);
}

void change(int node, int start, int end, int left, int right, long long delta) {
	if (start > right || end < left) {
		return;
	}
	if (start >= left && end <= right) {
		maxnum[node] += delta;
		lazy[node] += delta;
		return;
	}
	int mid = (start + end) >> 1;
	int leftnode = node << 1, rightnode = leftnode ^ 1;
	if (lazy[node]) {
		long long temp = lazy[node];
		lazy[node] = 0;
		maxnum[leftnode] += temp, maxnum[rightnode] += temp;
		lazy[leftnode] += temp, lazy[rightnode] += temp;
	}
	change(leftnode, start, mid, left, right, delta);
	change(rightnode, mid + 1, end, left, right, delta);
	maxnum[node] = std::max(maxnum[leftnode], maxnum[rightnode]);
}

void query(int node, int start, int end, int left, int right, long long &ans) {
	if (start > right || end < left || maxnum[node] <= ans) {
		return;
	}
	if (start >= left && end <= right) {
		ans = maxnum[node];
		return;
	}
	int mid = (start + end) >> 1;
	int leftnode = node << 1, rightnode = leftnode ^ 1;
	if (lazy[node]) {
		long long temp = lazy[node];
		lazy[node] = 0;
		maxnum[leftnode] += temp, maxnum[rightnode] += temp;
		lazy[leftnode] += temp, lazy[rightnode] += temp;
	}
	query(leftnode, start, mid, left, right, ans);
	query(rightnode, mid + 1, end, left, right, ans);
}

int main() {
	int n, q;
	read(n), read(q);
	int length = n << 2;
	maxnum = new long long[length];
	lazy = new long long[length];
	for (int i = 1, num; i <= n; i++) {
		read(num);
		build(1, 1, n, i, num);
	}
	long long d, ans;
	for (int i = 0, op, l, r; i < q; i++) {
		read(op), read(l), read(r);
		if (op == 1) {
			read(d);
			change(1, 1, n, l, r, d);
		} else {
			ans = 0;
			query(1, 1, n, l, r, ans);
			write(ans);
		}
	}
	return 0;
}
