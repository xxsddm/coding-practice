// http://oj.daimayuan.top/course/15/problem/636

#include "cstring"
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

int n, start = 1, *container;
long long *nums;

void change(int idx, long long delta) {
	while (idx <= n) {
		nums[idx] += delta;
		idx += idx & -idx;
	}
}

int query(long long cumsum) {
	int ans = 0;
	for (int i = start; i && cumsum; i >>= 1) {
		if ((ans ^ i) <= n && cumsum >= nums[ans ^ i]) {
			ans ^= i;
			cumsum -= nums[ans];
		}
	}
	return ans;
}

int main() {
	int q;
	read(n), read(q);
	container = new int[n + 1];
	nums = new long long[n + 1];
	memset(nums + 1, 0, sizeof(long long) * n);
	while ((start << 1) <= n) {
		start <<= 1;
	}
	for (int i = 1; i <= n; i++) {
		read(container[i]);
		change(i, container[i]);
	}
	long long s;
	for (int i = 0, op, x, d; i < q; i++) {
		read(op);
		if (op == 1) {
			read(x), read(d);
			change(x, d - container[x]);
			container[x] = d;
		} else {
			read(s);
			write(query(s));
		}
	}
	return 0;
}
