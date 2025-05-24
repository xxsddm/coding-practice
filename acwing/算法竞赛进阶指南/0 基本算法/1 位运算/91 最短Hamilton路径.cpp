// https://www.acwing.com/problem/content/description/93/

#include "cstring"
#include "unordered_map"
#include "iostream"

using namespace std;

int dist[20][20], dp[1 << 19][20];

int calculateIdx(int num) {
	int ans = -1;
	while (num) {
		ans++;
		num >>= 1;
	}
	return ans;
}

int main() {	// DP
	int n, last, ans = 0x7fffffff;
	cin >> n;
	last = (1 << (n - 1)) - 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> dist[i][j];
		}
	}
	memset(dp, 0x3f, sizeof(dp));
	// dp: [已访问状态][当前点] -> 最短路径
	dp[1][0] = 0;
	for (int visited = 1; visited < last; visited++) {
		// 从一个已访问状态, 访问一个未访问节点, 枚举已访问节点作为当前节点对该节点访问
		for (int nextNode = 1, temp1 = 2; nextNode < n - 1; nextNode++, temp1 <<= 1) {
			if (visited & temp1) {
				continue;
			}
			int nextVisited = visited ^ temp1;
			for (int node = 0, temp2 = 1; node < n - 1; node++, temp2 <<= 1) {
				if (visited & temp2) {
					// dp[visited][0]=inf不会导致0点复用(visited=1除外)
					dp[nextVisited][nextNode] = min(dp[nextVisited][nextNode], dp[visited][node] + dist[node][nextNode]);
				}
			}
		}
	}
	for (int node = 1; node < n - 1; node++) {
		ans = min(ans, dp[last][node] + dist[node][n - 1]);
	}
	cout << ans;
	return 0;
}
