// http://oj.daimayuan.top/course/10/problem/613

#include "unordered_map"
#include "iostream"

int n, nums[200001], left[200001], right[200001];

bool dfs(int start, int end) {
	if (start >= end) {
		return true;
	}
	// 避免O(n)复杂度查找区间内单一元素
	for (int idx1 = start, idx2 = end; idx1 <= idx2; idx1++, idx2--) {
		if (left[idx1] < start && right[idx1] > end) {
			return dfs(start, idx1 - 1) && dfs(idx1 + 1, end);
		}
		if (left[idx2] < start && right[idx2] > end) {
			return dfs(start, idx2 - 1) && dfs(idx2 + 1, end);
		}
	}
	return false;
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%d", &nums[i]);
		}
		// 记录每种元素左右侧最近相同元素位置
		std::unordered_map<int, int> memo;
		for (int i = 0; i < n; i++) {
			int &num = nums[i];
			if (!memo.count(num)) {
				left[i] = -1;
			} else {
				left[i] = memo[num];
			}
			memo[num] = i;
		}
		memo.clear();
		for (int i = n - 1; i >= 0; i--) {
			int &num = nums[i];
			if (!memo.count(num)) {
				right[i] = n;
			} else {
				right[i] = memo[num];
			}
			memo[num] = i;
		}
		printf(dfs(0, n - 1) ? "non-boring\n" : "boring\n");
	}
	return 0;
}
