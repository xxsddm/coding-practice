// http://oj.daimayuan.top/course/10/problem/505

#include "vector"
#include "cstring"
#include "iostream"

using namespace std;

int n, *counter;
long long ans = 0, **dp;

int dfs(int node, int prevNode, vector<int> *next) {
	int count = 1;
	dp[node][0] = 1;
	for (auto &nextNode : next[node]) {
		if (nextNode == prevNode) {
			continue;
		}
		count += dfs(nextNode, node, next);
		// 加入新的子节点后, node子节点中i个子树中各自抽一个节点组合数
		for (int i = 3; i > 0; i--) {
			dp[node][i] += dp[node][i - 1] * counter[nextNode];
		}
	}
	counter[node] = count;
	ans += dp[node][3] + dp[node][2] * (n - count);
	return count;
}

int main() {
	scanf("%d", &n);
	counter = new int[n + 1];
	vector<int> next[n + 1];
	dp = new long long*[n + 1];
	for (int i = 1; i <= n; i++) {
		dp[i] = new long long[4];
		memset(dp[i], 0, sizeof(long long) * 4);
	}
	for (int i = 1; i < n; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		next[u].push_back(v);
		next[v].push_back(u);
	}
	dfs(1, 0, next);
	printf("%lld", ans);
	return 0;
}
