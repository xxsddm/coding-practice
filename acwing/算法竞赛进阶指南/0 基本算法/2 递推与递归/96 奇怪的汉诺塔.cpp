// https://www.acwing.com/problem/content/description/98/

#include "cstring"
#include "iostream"

using namespace std;

int main() {	// DP
	// 首先计算3个柱子时最小移动次数
	int dp[13], counter[13];
	dp[0] = 0, counter[0] = 0, counter[1] = 1;
	for (int n = 1; n <= 12; n++) {
		dp[n] = (dp[n - 1] << 1) + 1;
	}
	// 首先将A中上部分按照 4个柱子 最优情况移动到B(子问题已计算)
	// 再由A中将下部分按照 3个柱子 最优情况移动到D
	// 枚举上部分数量, 计算最优解
	for (int n = 2; n <= 12; n++) {
		int temp = 0x7fffffff;
		for (int up = 1; up < n; up++) {
			temp = min(temp, (counter[up] << 1) + dp[n - up]);
		}
		counter[n] = temp;
	}
	for (int n = 1; n <= 12; n++) {
		printf("%d\n", counter[n]);
	}
	return 0;
}
