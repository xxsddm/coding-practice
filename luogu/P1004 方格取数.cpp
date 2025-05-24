// https://www.luogu.com.cn/problem/P1004

#include "cstring"
#include "iostream"

using namespace std;

int main() {	// DP
	int N;
	cin >> N;
	// dp[i][j][k] -> 走i步, p1走到row=j, p2走到row=k, 此时最大总和 (第一维度i可省)
	int nums[N][N], dp[2 * N - 1][N][N];
	memset(nums, 0, sizeof(nums));
	memset(dp, 0, sizeof(dp));
	while (true) {
		int row, col, num;
		cin >> row >> col >> num;
		if (row == 0) {
			break;
		}
		nums[row - 1][col - 1] = num;
	}
	dp[0][0][0] = nums[0][0];
	for (int s = 1, numStep = 2 * N - 2; s <= numStep; s++) {
		for (int row1 = max(0, s - N - 1), limit = min(s, N - 1); row1 <= limit; row1++) {
			int col1 = s - row1;
			for (int row2 = max(0, s - N - 1); row2 <= limit; row2++) {
				int col2 = s - row2;
				int *ptr = &dp[s][row1][row2];
				if (row1 > 0 && row2 > 0) {
					*ptr = max(*ptr, dp[s - 1][row1 - 1][row2 - 1]);
				}
				if (row1 > 0 && col2 > 0) {
					*ptr = max(*ptr, dp[s - 1][row1 - 1][row2]);
				}
				if (col1 > 0 && row2 > 0) {
					*ptr = max(*ptr, dp[s - 1][row1][row2 - 1]);
				}
				if (col1 > 0 && col2 > 0) {
					*ptr = max(*ptr, dp[s - 1][row1][row2]);
				}
				*ptr += nums[row1][col1];
				if (row1 != row2) {
					*ptr += nums[row2][col2];
				}
			}
		}
	}
	cout << dp[2 * N - 2][N - 1][N - 1];
	return 0;
}
