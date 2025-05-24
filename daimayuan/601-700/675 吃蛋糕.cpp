// http://oj.daimayuan.top/course/10/problem/675

#include "cstring"
#include "iostream"

int n;
double ***dp;

double dfs(int num1, int num2, int num3) {
	if (dp[num1][num2][num3] > -0.1) {
		return dp[num1][num2][num3];
	}
	double ans = n;
	if (num1) {
		ans += num1 * dfs(num1 - 1, num2, num3);
	}
	if (num2) {
		ans += num2 * dfs(num1 + 1, num2 - 1, num3);
	}
	if (num3) {
		ans += num3 * dfs(num1, num2 + 1, num3 - 1);
	}
	ans /= (num1 + num2 + num3);
	dp[num1][num2][num3] = ans;
	return ans;
}

int main() {
	scanf("%d", &n);
	int counter[4] = {0, 0, 0, 0};
	for (int i = 0, num; i < n; i++) {
		scanf("%d", &num);
		counter[num]++;
	}
	counter[2] += counter[3];
	dp = new double**[n + 1];
	for (int i = 0; i <= n; i++) {
		dp[i] = new double*[counter[2] + 1];
		for (int j = 0; j <= counter[2]; j++) {
			dp[i][j] = new double[counter[3] + 1];
			memset(dp[i][j], -1, sizeof(double) * (counter[3] + 1));

		}
	}
	counter[2] -= counter[3];
	dp[0][0][0] = 0;
	printf("%.9lf", dfs(counter[1], counter[2], counter[3]));
}