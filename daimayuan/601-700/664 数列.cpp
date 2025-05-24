// http://oj.daimayuan.top/course/10/problem/664

#include "cstring"
#include "iostream"

int main() {
	int t;
	scanf("%d", &t);
	int maxnum, dp[31];
	long long mod;
	while (t--) {
		scanf("%d %lld", &maxnum, &mod);
		int length = 0;
		for (int i = maxnum; i; i >>= 1) {
			length++;
		}
		int ans = 0, limit = 1 << (length - 1);
		memset(dp, 0, sizeof(dp));
		dp[0] = 1;
		// 考虑当前位次为最大二进制1位置后, 能够组成的序列长度及相应种数
		for (int i = 1, count = 1; i <= length; i++, count <<= 1) {
			if (count == limit) {
				count = maxnum - limit + 1;
			}
			for (int j = i; j; j--) {
				dp[j] += ((long long) dp[j - 1] * count) % mod;
				if (dp[j] >= mod) {
					dp[j] -= mod;
				}
			}
		}
		for (int i = 1; i <= length; i++) {
			ans += dp[i];
			if (ans >= mod) {
				ans -= mod;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
