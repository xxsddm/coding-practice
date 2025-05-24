// https://www.luogu.com.cn/problem/P5854

#include "iostream"
#include "stack"
#include "cstring"

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

int *left, *right;

int main() {
	int n;
	read(n);
	left = new int[n + 1];
	right = new int[n + 1];
	memset(left + 1, 0, sizeof(int) * n);
	memset(right + 1, 0, sizeof(int) * n);
	int root = 0;
	std::stack<std::pair<int, int>> stk;
	for (int i = 1, num; i <= n; i++) {
		read(num);
		int last = 0;
		while (!stk.empty() && num < stk.top().second) {
			last = stk.top().first;
			stk.pop();
		}
		if (stk.empty()) {
			root = i;
		} else {
			right[stk.top().first] = i;
		}
		left[i] = last;
		stk.push({i, num});
	}
	long long ans = 0;
	for (int i = 1; i <= n; i++) {
		ans ^= (long long) i * (left[i] + 1);
	}
	printf("%lld ", ans);
	ans = 0;
	for (int i = 1; i <= n; i++) {
		ans ^= (long long) i * (right[i] + 1);
	}
	printf("%lld", ans);
	return 0;
}