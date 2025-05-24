// http://oj.daimayuan.top/course/11/problem/289

#include "iostream"

using namespace std;

int main() {
	int n;
	scanf("%d", &n);
	int ans = 0, nums[n], dp[n];
	for (int i = 0; i < n; i++) {
		scanf("%d", &nums[i]);
		dp[i] = nums[i];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {
			if (nums[i] > nums[j]) {
				dp[i] = max(dp[i], dp[j] + nums[i]);
			}
		}
		ans = max(ans, dp[i]);
	}
	printf("%d", ans);
	return 0;
}
