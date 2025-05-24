// https://www.acwing.com/problem/content/description/274/

#include "cstring"
#include "iostream"

int main() {
	int N;
	scanf("%d", &N);
	int nums1[N + 1], nums2[N + 1];
	for (int i = 0; i < N; i++) {
		scanf("%d", &nums1[i]);
	}
	for (int i = 0; i < N; i++) {
		scanf("%d", &nums2[i]);
	}
	int dp[N + 1][N + 1];
	memset(dp, 0, sizeof(dp));
	// dp[i][j] -> 考虑长度i的序列1子序列部分
	// 以第j个元素为末端的 最长公共递增子序列
	for (int i = 0; i < N; i++) {
		for (int j = 0, prev = 0; j < N; j++) {
			if (nums1[i] != nums2[j]) {
				dp[i + 1][j + 1] = dp[i][j + 1];
				if (nums1[i] > nums2[j]) {
					prev = std::max(prev, dp[i + 1][j + 1]);
				}
			} else {
				dp[i + 1][j + 1] = prev + 1;
			}
		}
	}
	int ans = 0;
	for (int i = 1; i <= N; i++) {
		ans = std::max(ans, dp[N][i]);
	}
	printf("%d", ans);
	return 0;
}