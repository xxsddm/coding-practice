// http://oj.daimayuan.top/course/10/problem/865

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
	numstk[length++] = x % 10;
	for (int i = length - 1; i >= 0; i--) {
		putchar(numstk[i] ^ 48);
	}
	putchar('\n');
}

int *nums, *diff, *lazy;

void change(int node, int start, int end, int left, int right) {
	nums[node]++;
	if (left <= start && right >= end) {
		diff[node]++;
		lazy[node]++;
		return;
	}
	int nextNode1 = node << 1, nextNode2 = nextNode1 ^ 1, mid = (start + end) >> 1;
	if (lazy[node]) {
		int temp = lazy[node];
		nums[nextNode1] += temp, nums[nextNode2] += temp;
		diff[nextNode1] += temp, diff[nextNode2] += temp;
		lazy[nextNode1] += temp, lazy[nextNode2] += temp;
		lazy[node] = 0;
	}
	if (right <= mid) {
		change(nextNode1, start, mid, left, right);
	} else if (left > mid) {
		change(nextNode2, mid + 1, end, left, right);
	} else {
		diff[node]++;
		change(nextNode1, start, mid, left, right);
		change(nextNode2, mid + 1, end, left, right);
	}
}

int query(int node, int start, int end, int left, int right) {
	if (left <= start && right >= end) {
		return nums[node];
	}
	int nextNode1 = node << 1, nextNode2 = nextNode1 ^ 1, mid = (start + end) >> 1;
	if (lazy[node]) {
		int temp = lazy[node];
		nums[nextNode1] += temp, nums[nextNode2] += temp;
		diff[nextNode1] += temp, diff[nextNode2] += temp;
		lazy[nextNode1] += temp, lazy[nextNode2] += temp;
		lazy[node] = 0;
	}
	if (right <= mid) {
		return query(nextNode1, start, mid, left, right);
	}
	if (left > mid) {
		return query(nextNode2, mid + 1, end, left, right);
	}
	return query(nextNode1, start, mid, left, right)
	       + query(nextNode2, mid + 1, end, left, right)
	       - diff[node];
}

int main() {
	int n, m;
	read(n), read(m);
	int length = n << 2;
	nums = new int[length], diff = new int[length], lazy = new int[length];
	for (int i = 0; i < length; i++) {
		nums[i] = diff[i] = lazy[i] = 0;
	}
	for (int i = 0, op, l, r; i < m; i++) {
		read(op), read(l), read(r);
		if (op == 1) {
			change(1, 1, n, l, r);
		} else {
			write(query(1, 1, n, l, r));
		}
	}
	return 0;
}