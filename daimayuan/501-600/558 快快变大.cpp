// http://oj.daimayuan.top/course/11/problem/558

#include "iostream"

int main() {	// 区间DP
	int n;
	scanf("%d", &n);
	long long mod = 1000003;
	std::pair<int, long long> dp[n][n];
	for (int i = 0; i < n; i++) {
		scanf("%d", &dp[i][i].first);
		dp[i][i].second = 0;
	}
	for (int start = n - 2; start >= 0; start--) {
		for (int end = start + 1; end < n; end++) {
			int rest = 0;
			long long maxnum = 0;
			for (int mid = start; mid < end; mid++) {
				long long diff = dp[start][mid].first - dp[mid + 1][end].first;
				long long temp = dp[start][mid].second + dp[mid + 1][end].second;
				temp += diff * diff;
				if (temp > maxnum) {
					maxnum = temp;
					rest = (long long) dp[start][mid].first * dp[mid + 1][end].first % mod;
				}
			}
			dp[start][end].first = rest;
			dp[start][end].second = maxnum;
		}
	}
	printf("%lld", dp[0][n - 1].second);
	return 0;
}
