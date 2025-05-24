// https://www.acwing.com/problem/content/11/

#include "cstring"
#include "iostream"

using namespace std;

int mod = 1e9 + 7;

int main() {
	int N, V;
	scanf("%d %d", &N, &V);
	int dp[V + 1], counter[V + 1], maxnum = 0;
	memset(dp, 0, sizeof(dp));
	memset(counter, 0, sizeof(counter));
	counter[0] = 1;
	for (int i = 0; i < N; i++) {
		int v, w;
		scanf("%d %d", &v, &w);
		for (int j = V; j >= v; j--) {
			int temp = dp[j - v] + w;
			if (temp > dp[j]) {
				dp[j] = temp;
				counter[j] = counter[j - v];
				maxnum = max(maxnum, temp);
			} else if (temp == dp[j]) {
				counter[j] = (counter[j] + counter[j - v]) %  mod;
			}
		}
	}
	int ans = 0;
	for (int i = 0; i <= V; i++) {
		if (dp[i] == maxnum) {
			ans = (ans + counter[i]) % mod;
		}
	}
	printf("%d", ans);
	return 0;
}
