// http://oj.daimayuan.top/course/15/problem/780

#include "iostream"

typedef long long ll;

using namespace std;

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

const int length = 200000;
ll container[length + 1];

ll query(int idx) {
	ll ans = 0;
	while (idx) {
		ans = max(ans, container[idx]);
		idx ^= idx & -idx;
	}
	return ans;
}

void change(int idx, ll val) {
	while (idx <= length) {
		if (val <= container[idx]) {
			return;
		}
		container[idx] = val;
		idx += idx & -idx;
	}
}

int main() {
	int n;
	read(n);
	ll ans = 0;
	for (int i = 0, num; i < n; i++) {
		read(num);
		// 计算当前值为上升序列末端时的最大累和
		ll temp = query(num - 1) + num;
		change(num, temp);
		ans = max(ans, temp);
	}
	printf("%lld\n", ans);
	return 0;
}
