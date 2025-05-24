// https://www.acwing.com/problem/content/684/

#include "cstring"
#include "iostream"

long long mod = 998244353;
int dp[2][201][3], cumsum[201][2];

int main() {
	int n;
	scanf("%d", &n);
	int cur = 1, nums[n + 1];
	memset(dp, 0, sizeof(dp));
	memset(cumsum, 0, sizeof(cumsum));
	for (int i = 1; i <= n; i++) {
		scanf("%d", &nums[i]);
	}
	for (int i = nums[1] ? nums[1] : 1, limiti = nums[1] ? nums[1] : 200; i <= limiti; i++) {
		for (int j = nums[2] ? nums[2] : 1, limitj = nums[2] ? nums[2] : 200; j <= limitj; j++) {
			if (i == j) {
				dp[0][j][1]++;
			} else if (i < j) {
				dp[0][j][2]++;
			}
		}
	}
	for (int i = 3; i <= n; i++) {
		int prev = 1 - cur;
		for (int j = 1; j <= 200; j++) {
			cumsum[j][0] = ((long long) cumsum[j - 1][0] + dp[prev][j][0] + dp[prev][j][1]) % mod;
			cumsum[j][1] = ((long long) cumsum[j - 1][1] + dp[prev][j][0] + dp[prev][j][1] + dp[prev][j][2]) % mod;
		}
		for (int j = nums[i] ? nums[i] : 1, limit = nums[i] ? nums[i] : 200; j <= limit; j++) {
			dp[cur][j][0] = (cumsum[200][0] - cumsum[j][0] + mod) % mod;
			dp[cur][j][1] = ((long long) dp[prev][j][0] + dp[prev][j][1] + dp[prev][j][2]) % mod;
			dp[cur][j][2] = cumsum[j - 1][1];
		}
		if (nums[i] && i != n) {
			for (int j = 1, limit = nums[i]; j < limit; j++) {
				dp[cur][j][0] = dp[cur][j][1] = dp[cur][j][2] = 0;
			}
			for (int j = nums[i] + 1; j <= 200; j++) {
				dp[cur][j][0] = dp[cur][j][1] = dp[cur][j][2] = 0;
			}
		}
		cur = prev;
	}
	long long ans = 0;
	for (int i = nums[n] ? nums[n] : 1, limit = nums[n] ? nums[n] : 200; i <= limit; i++) {
		ans = (ans + dp[1 - cur][i][0] + dp[1 - cur][i][1]) % mod;
	}
	printf("%lld", ans);
	return 0;
}

/*
long long mod = 998244353;
int dp[10002][201][3], cumsum[201][2];	// dp: 当前索引, 选择数字, <=>前面数字的组合数量

int main() {
	int n;
	scanf("%d", &n);
	int nums[n + 1];
	memset(dp, 0, sizeof(dp));
	memset(cumsum, 0, sizeof(cumsum));
	for (int i = 1; i <= n; i++) {
		scanf("%d", &nums[i]);
	}
	for (int i = nums[1] ? nums[1] : 1, limiti = nums[1] ? nums[1] : 200; i <= limiti; i++) {
		for (int j = nums[2] ? nums[2] : 1, limitj = nums[2] ? nums[2] : 200; j <= limitj; j++) {
			if (i == j) {
				dp[2][j][1]++;
			} else if (i < j) {
				dp[2][j][2]++;
			}
		}
	}
	for (int i = 1; i <= 200; i++) {
		cumsum[i][0] = (cumsum[i - 1][0] + dp[2][i][0] + dp[2][i][1]) % mod;
		cumsum[i][1] = (cumsum[i - 1][1] + dp[2][i][0] + dp[2][i][1] + dp[2][i][2]) % mod;
	}
	for (int i = 3; i <= n; i++) {
		for (int j = nums[i] ? nums[i] : 1, limit = nums[i] ? nums[i] : 200; j <= limit; j++) {
			dp[i][j][0] = (cumsum[200][0] - cumsum[j][0] + mod) % mod;
			dp[i][j][1] = ((long long) dp[i - 1][j][0] + dp[i - 1][j][1] + dp[i - 1][j][2]) % mod;
			dp[i][j][2] = cumsum[j - 1][1];
		}
		for (int j = 1; j <= 200; j++) {
			cumsum[j][0] = ((long long) cumsum[j - 1][0] + dp[i][j][0] + dp[i][j][1]) % mod;
			cumsum[j][1] = ((long long) cumsum[j - 1][1] + dp[i][j][0] + dp[i][j][1] + dp[i][j][2]) % mod;
		}
	}
	long long ans = 0;
	for (int i = nums[n] ? nums[n] : 1, limit = nums[n] ? nums[n] : 200; i <= limit; i++) {
		ans = (ans + dp[n][i][0] + dp[n][i][1]) % mod;
	}
	printf("%lld", ans);
	return 0;
}
*/
