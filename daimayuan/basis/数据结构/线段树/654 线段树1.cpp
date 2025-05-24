// http://oj.daimayuan.top/course/15/problem/654

#include "cstring"
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
}

int *minnum, *counter;

void change(int node, int start, int end, int idx, int num) {
	if (start > idx || end < idx) {
		return;
	}
	if (start == end) {
		minnum[node] = num;
		counter[node] = 1;
		return;
	}
	int mid = (start + end) >> 1;
	int leftnode = node << 1, rightnode = leftnode ^ 1;
	change(leftnode, start, mid, idx, num);
	change(rightnode, mid + 1, end, idx, num);
	minnum[node] = std::min(minnum[leftnode], minnum[rightnode]);
	counter[node] = 0;
	if (minnum[leftnode] == minnum[node]) {
		counter[node] += counter[leftnode];
	}
	if (minnum[rightnode] == minnum[node]) {
		counter[node] += counter[rightnode];
	}
}

void query(int node, int start, int end, int left, int right, int &val, int &count) {
	if (start > right || end < left) {
		return;
	}
	if (minnum[node] > val) {
		return;
	}
	if (start >= left && end <= right) {
		if (minnum[node] < val) {
			val = minnum[node];
			count = counter[node];
		} else {
			count += counter[node];
		}
		return;
	}
	int mid = (start + end) >> 1;
	int leftnode = node << 1, rightnode = leftnode ^ 1;
	query(leftnode, start, mid, left, right, val, count);
	query(rightnode, mid + 1, end, left, right, val, count);
}

int main() {
	int n, q;
	read(n), read(q);
	int length = n << 2;
	minnum = new int[length], counter = new int[length];
	memset(minnum, 0x3f, sizeof(int) * length);
	for (int i = 1, num; i <= n; i++) {
		read(num);
		change(1, 1, n, i, num);
	}
	for (int i = 0, op, x, d, l, r, val, count; i < q; i++) {
		read(op);
		if (op == 1) {
			read(x), read(d);
			change(1, 1, n, x, d);
		} else {
			val = 0x7fffffff, count = 0;
			read(l), read(r);
			query(1, 1, n, l, r, val, count);
			write(val);
			putchar(' ');
			write(count);
			putchar('\n');
		}
	}
	return 0;
}