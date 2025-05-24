// http://oj.daimayuan.top/course/11/problem/126

#include "cstring"
#include "iostream"

using namespace std;

int main() {
	int n, mod = 1e9 + 7;
	scanf("%d", &n);
	int dp[n + 1][n + 1];
	memset(dp, 0, sizeof(dp));
	dp[0][1] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			int status;
			scanf("%d", &status);
			if (status) {
				dp[i][j] = (dp[i - 1][j] + dp[i][j - 1]) % mod;
			}
		}
	}
	printf("%d", dp[n][n]);
	return 0;
}
