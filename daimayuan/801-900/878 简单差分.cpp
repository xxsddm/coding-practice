// http://oj.daimayuan.top/course/11/problem/878

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
	numstk[length++] = x % 10;
	for (int i = length - 1; i >= 0; i--) {
		putchar(numstk[i] ^ 48);
	}
	putchar('\n');
}

long long *nums, *add;

int main() {
	int n, m, k;
	read(n), read(m), read(k);
	nums = new long long[n + 2];
	add = new long long[n + 1];
	nums[0] = add[0] = 0;
	for (int i = 1; i <= n; i++) {
		read(nums[i]);
		add[i] = 0;
	}
	for (int i = 0, l, r, x; i < m; i++) {
		read(l), read(r), read(x);
		add[l] += x;
		add[r + 1] -= x;
	}
	for (int i = 1; i <= n; i++) {
		add[i] += add[i - 1];
		nums[i] += nums[i - 1] + add[i];
	}
	for (int i = 0, l, r; i < k; i++) {
		read(l), read(r);
		write(nums[r] - nums[l - 1]);
	}
	return 0;
}