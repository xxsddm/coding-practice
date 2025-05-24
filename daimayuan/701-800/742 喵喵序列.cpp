// http://oj.daimayuan.top/course/11/problem/742

#include "algorithm"
#include "iostream"

int n, *left, *right;
std::pair<long long, int> *nums;

void change(int idx, int delta, int *container) {
	while (idx <= n) {
		container[idx] += delta;
		idx += idx & -idx;
	}
}

int query(int idx, int *container) {
	int ans = 0;
	while (idx) {
		ans += container[idx];
		idx ^= idx & -idx;
	}
	return ans;
}

int main() {
	scanf("%d", &n);
	left = new int[n + 1];
	right = new int[n + 1];
	nums = new std::pair<long long, int>[n + 1];
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &nums[i].first);
		nums[i].second = i;
		left[i] = right[i] = 0;
	}
	long long ans = 0;
	std::sort(nums + 1, nums + n + 1);
	for (int i = 1; i <= n; i++) {
		change(i, 1, right);
	}
	int idx = 1, totalRight = n;
	while (idx <= n) {
		int start = idx;
		long long &temp = nums[idx].first;
		while (idx + 1 <= n && nums[idx + 1].first == temp) {
			idx++;
		}
		int end = idx++;
		for (int i = start; i <= end; i++) {
			change(nums[i].second, -1, right);
		}
		totalRight -= end - start + 1;
		for (int i = start; i <= end; i++) {	// 枚举中间元素原始索引
			ans += (long long) query(nums[i].second - 1, left) * (totalRight - query(nums[i].second, right));
		}
		for (int i = start; i <= end; i++) {
			change(nums[i].second, 1, left);
		}
	}
	printf("%lld", ans);
	return 0;
}
