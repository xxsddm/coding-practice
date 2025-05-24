// https://www.acwing.com/problem/content/2/

#include "cstring"
#include "iostream"

using namespace std;

int main() {
	int N, V;
	scanf("%d %d", &N, &V);
	int dp[V + 1];
	memset(dp, 0, sizeof(dp));
	for (int i = 0; i < N; i++) {
		int v, w;
		scanf("%d %d", &v, &w);
		for (int j = V; j >= v; j--) {
			dp[j] = max(dp[j], dp[j - v] + w);
		}
	}
	printf("%d", dp[V]);
	return 0;
}
