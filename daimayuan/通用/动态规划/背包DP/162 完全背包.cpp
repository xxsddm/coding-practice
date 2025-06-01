// http://oj.daimayuan.top/course/5/problem/162

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

int main() {
	int n, m;
	read(n), read(m);
	int dp[m + 1];
	memset(dp, 0, sizeof(dp));
	for (int i = 0, v, w; i < n; i++) {
		read(v), read(w);
		for (int j = v; j <= m; j++) {
			dp[j] = std::max(dp[j], dp[j - v] + w);
		}
	}
	printf("%d", dp[m]);
	return 0;
}