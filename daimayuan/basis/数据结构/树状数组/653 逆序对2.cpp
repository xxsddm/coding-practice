// http://oj.daimayuan.top/course/15/problem/653

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

const int length = 100001;
int counter[length];

int query(int idx) {
	int ans = 0;
	while (idx) {
		ans += counter[idx];
		idx ^= idx & -idx;
	}
	return ans;
}

void change(int idx) {
	while (idx <= length) {
		counter[idx]++;
		idx += idx & -idx;
	}
}

int main() {
	int n;
	read(n);
	long long ans = 0;
	for (int i = 0, num; i < n; i++) {
		read(num);
		ans += i - query(num);
		change(num);
	}
	printf("%lld", ans);
	return 0;
}