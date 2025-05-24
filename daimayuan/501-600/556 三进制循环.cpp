// http://oj.daimayuan.top/course/10/problem/556

#include "vector"
#include "iostream"

int *nums, *inc, *dec;	// 节点向下最大递增/递减序列长度

void dfs(int node, int prevNode, std::vector<int> *next) {
	int prevNum = nums[node] == 0 ? 2 : (nums[node] - 1);
	int nextNum = nums[node] == 2 ? 0 : (nums[node] + 1);
	inc[node] = dec[node] = 0;
	for (int &nextNode : next[node]) {
		if (nextNode == prevNode) {
			continue;
		}
		dfs(nextNode, node, next);
		if (nums[nextNode] == prevNum) {
			dec[node] = std::max(dec[node], dec[nextNode] + 1);
		} else if (nums[nextNode] == nextNum) {
			inc[node] = std::max(inc[node], inc[nextNode] + 1);
		}
	}
}

int main() {
	int n;
	scanf("%d", &n);
	nums = new int[n + 1], inc = new int[n + 1], dec = new int[n + 1];
	std::vector<int> next[n + 1];
	for (int i = 1; i < n; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		next[u].push_back(v);
		next[v].push_back(u);
	}
	for (int i = 1; i <= n; i++) {
		scanf("%d", &nums[i]);
	}
	dfs(1, 0, next);
	int ans = 0;
	for (int node = 1; node <= n; node++) {
		ans = std::max(ans, inc[node] + dec[node] + 1);
	}
	printf("%d", ans);
	return 0;
}
