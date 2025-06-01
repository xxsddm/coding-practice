// http://oj.daimayuan.top/course/15/problem/635

#include "cstring"
#include "iostream"

typedef unsigned long long ull;

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

int n;
ull *nums1, *nums2;

void change(int left, int right, ull delta) {
	int idx = left;
	ull temp = delta * left;
	while (idx <= n) {
		nums1[idx] += delta;
		nums2[idx] += temp;
		idx += idx & -idx;
	}
	idx = right + 1;
	temp = delta * idx;
	while (idx <= n) {
		nums1[idx] -= delta;
		nums2[idx] -= temp;
		idx += idx & -idx;
	}
}

ull query(int idx) {
	ull ans = 0;
	int temp = idx;
	while (idx) {
		ans += nums1[idx] * (temp + 1);
		ans -= nums2[idx];
		idx ^= idx & -idx;
	}
	return ans;
}

int main() {	// 各元素表示为差分的和, 再次求和找规律
	int q;
	read(n), read(q);
	nums1 = new ull[n + 1];
	nums2 = new ull[n + 1];
	memset(nums1, 0, sizeof(ull) * (n + 1));
	memset(nums2, 0, sizeof(ull) * (n + 1));
	ull d;
	for (int i = 0, op, l, r, x; i < q; i++) {
		read(op);
		if (op == 1) {	// (x + 1) sum(diff[i]) - sum(i * diff[i])
			read(l), read(r), read(d);
			change(l, r, d);
		} else {
			read(x);
			write(query(x));
		}
	}
	return 0;
}