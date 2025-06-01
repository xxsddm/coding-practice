// http://oj.daimayuan.top/course/15/problem/719

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
	putchar('\n');
}

int n, t = 0, *root;
long long *diff;

int find(int node) {
	if (node == root[node]) {
		return node;
	}
	int ans = find(root[node]);
	diff[node] += diff[root[node]];
	root[node] = ans;
	return ans;
}

void merge(int left, int right, long long x) {
	int idx1 = find(left), idx2 = find(right);
	if (idx1 == idx2 && diff[left] - diff[right] != x) {
		return;
	}
	root[idx1] = idx2;
	// nums[left] - nums[right] = x
	// nums[left] - nums[idx1]
	// nums[right] - nums[idx2]
	// nums[idx1] - nums[idx2] ?
	diff[idx1] = diff[right] - diff[left] + x;
}

void query(int left, int right) {
	if (find(left) != find(right)) {
		return;
	}
	t = (std::abs(diff[left] - diff[right])) % n;
	write(diff[left] - diff[right]);
}

int main() {
	int q;
	read(n), read(q);
	root = new int[n + 1];
	diff = new long long[n + 1];
	for (int i = 1; i <= n; i++) {
		root[i] = i;
		diff[i] = 0;
	}
	for (int i = 0, op, l, r; i < q; i++) {
		read(op), read(l), read(r);
		l = (l + t) % n + 1;
		r = (r + t) % n + 1;
		if (op == 1) {
			long long x;
			read(x);
			merge(l, r, x);
		} else {
			query(l, r);
		}
	}
	return 0;
}