// http://oj.daimayuan.top/course/15/problem/661

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
	numstk[length++] = x;
	for (int i = length - 1; i >= 0; i--) {
		putchar(numstk[i] ^ 48);
	}
	putchar('\n');
}

int *maxnum;

void change(int node, int start, int end, int idx, int val) {
	if (start > idx || end < idx) {
		return;
	}
	if (start == end) {
		maxnum[node] = val;
		return;
	}
	int mid = (start + end) >> 1;
	int leftnode = node << 1, rightnode = leftnode ^ 1;
	change(leftnode, start, mid, idx, val);
	change(rightnode, mid + 1, end, idx, val);
	maxnum[node] = std::max(maxnum[leftnode], maxnum[rightnode]);
}

void query(int node, int start, int end, int left, int right, int num, int &ans) {
	if (start > right || end < left || maxnum[node] < num || start > ans) {
		return;
	}
	if (start == end) {
		ans = start;
		return;
	}
	int mid = (start + end) >> 1;
	int leftnode = node << 1, rightnode = leftnode ^ 1;
	query(leftnode, start, mid, left, right, num, ans);
	query(rightnode, mid + 1, end, left, right, num, ans);
}

int main() {
	int n, q;
	read(n), read(q);
	int length = n << 2;
	maxnum = new int[length];
	for (int i = 1, num; i <= n; i++) {
		read(num);
		change(1, 1, n, i, num);
	}
	for (int i = 0, op, a, b, c, ans; i < q; i++) {
		read(op), read(a), read(b);
		if (op == 1) {
			change(1, 1, n, a, b);
		} else {
			read(c);
			ans = length;
			query(1, 1, n, a, b, c, ans);
			write(ans == length ? -1 : ans);
		}
	}
	return 0;
}