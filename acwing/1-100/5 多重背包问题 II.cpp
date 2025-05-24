// https://www.acwing.com/problem/content/5/

#include "iostream"
#include "cstring"

using namespace std;

int V;

void change(int v, int w, int *dp) {
	for (int i = V; i >= v; i--) {
		dp[i] = max(dp[i], dp[i - v] + w);
	}
}

int main() {
	int N, ans = 0;
	scanf("%d %d", &N, &V);
	int dp[V + 1];
	memset(dp, 0, sizeof(dp));
	for (int i = 0; i < N; i++) {
		int v, w, s;
		scanf("%d %d %d", &v, &w, &s);
		int limit = 11, weight = v, value = w;
		while (s - (1 << limit) + 1 < 0) {
			limit--;
		}
		int temp = s - (1 << limit) + 1;
		if (temp) {
			change(temp * v, temp * w, dp);
		}
		for (int power = 0, weight = v, value = w; power < limit; power++, weight <<= 1, value <<= 1) {
			change(weight, value, dp);
		}
	}
	printf("%d", dp[V]);
	return 0;
}

