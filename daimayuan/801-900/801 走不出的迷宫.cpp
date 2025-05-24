// http://oj.daimayuan.top/course/11/problem/801

#include "iostream"

bool **dp;
char **word;

int main() {
	int H, W;
	scanf("%d %d", &H, &W);
	dp = new bool* [H];
	word = new char* [H];
	for (int i = 0; i < H; i++) {
		dp[i] = new bool [W];
		word[i] = new char [W + 1];
		scanf("%s", word[i]);
	}
	int ans = 0;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (word[i][j] == '#') {
				dp[i][j] = false;
				continue;
			}
			if ((i && dp[i - 1][j]) || (j && dp[i][j - 1]) || (i == 0 && j == 0)) {
				dp[i][j] = true;
				ans = std::max(ans, i + j + 1);
			} else {
				dp[i][j] = false;
			}
		}
	}
	printf("%d", ans);
	return 0;
}
