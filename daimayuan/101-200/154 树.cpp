// http://oj.daimayuan.top/course/11/problem/154

#include "unordered_map"
#include "cstring"
#include "iostream"

int *dp;
std::unordered_map<int, int> *counter;

int main() {
	int n;
	scanf("%d", &n);
	dp = new int[n + 1];
	counter = new std::unordered_map<int, int>[n + 1];
	memset(dp, 0, sizeof(int) * (n + 1));
	for (int i = 1, prev; i < n; i++) {
		scanf("%d", &prev);
		dp[prev]++;
	}
	for (int i = 1; i <= n; i++) {
		counter[1][dp[i]]++;
	}
	dp[1] = 0;
	for (int k = 2; k <= n; k++) {
		dp[k] = -1;
		int temp = n << 1, prev = -1;
		for (int i = 1; i < k; i++) {
			if (dp[i] != -1 && counter[i].count(k - i) && dp[i] + 1 < temp) {
				temp = dp[i] + 1;
				prev = i;
			}
		}
		if (prev == -1) {
			continue;
		}
		dp[k] = temp;
		counter[k] = counter[prev];
		if (--counter[k][k - prev] == 0) {
			counter[k].erase(k - prev);
		}
	}
	for (int i = 1; i <= n; i++) {
		printf("%d ", dp[i]);
	}
	return 0;
}