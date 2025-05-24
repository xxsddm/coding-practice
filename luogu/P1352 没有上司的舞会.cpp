// https://www.luogu.com.cn/problem/P1352

#include "cstring"
#include "vector"
#include "iostream"

using namespace std;

int dfs(int node, int *nums, vector<int> *next, int container[][2], bool prev) {
	if (container[node][prev] != -1) {
		return container[node][prev];
	}
	int ans = 0, temp = 0;
	for (int &nextNode : next[node]) {
		temp += dfs(nextNode, nums, next, container, false);
	}
	ans = max(ans, temp);
	if (!prev && nums[node] > 0) {
		temp = nums[node];
		for (int &nextNode : next[node]) {
			temp += dfs(nextNode, nums, next, container, true);
		}
	}
	ans = max(ans, temp);
	container[node][prev] = ans;
	return ans;
}

int main() {	// 记忆化递归
	int n;
	scanf("%d", &n);
	int nums[n], container[n][2];
	bool root[n];
	vector<int> next[n];
	memset(container, -1, sizeof(container));
	memset(root, true, sizeof(root));
	for (int i = 0; i < n; i++) {
		scanf("%d", &nums[i]);
	}
	for (int i = 1; i < n; i++) {
		int l, k;
		scanf("%d %d", &l, &k);
		next[k - 1].push_back(l - 1);
		root[l - 1] = false;
	}
	for (int i = 0; i < n; i++) {
		if (root[i]) {
			printf("%d", dfs(i, nums, next, container, false));
		}
	}
	return 0;
}
