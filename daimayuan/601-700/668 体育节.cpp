// http://oj.daimayuan.top/course/10/problem/668

#include "algorithm"
#include "iostream"

int *nums;
long long **dp;

int main() {
	int n;
	scanf("%d", &n);
	nums = new int[n];
	dp = new long long*[n];
	for (int i = 0; i < n; i++) {
		scanf("%d", &nums[i]);
		dp[i] = new long long[n];
		dp[i][i] = 0;
	}
	std::sort(nums, nums + n);
	for (int left = n - 2; left >= 0; left--) {
		for (int right = left + 1; right < n; right++) {
			dp[left][right] = std::min(dp[left + 1][right], dp[left][right - 1]) + nums[right] - nums[left];
		}
	}
	printf("%lld", dp[0][n - 1]);
	return 0;
}
