// http://oj.daimayuan.top/course/11/problem/672

#include "algorithm"
#include "iostream"

long long mod = 1e9 + 7;
std::pair<int, int> *nums;

int main() {
	int n;
	scanf("%d", &n);
	nums = new std::pair<int, int>[n];
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &nums[i].first, &nums[i].second);
	}
	// 观察1, 2项交换位置后变化, 贪心
	sort(nums, nums + n, [] (auto & p1, auto & p2) -> bool {
		return (long long) p2.first * p1.second + p2.second >
		(long long) p1.first * p2.second + p1.second;
	});
	int ans = 0;
	for (int i = n - 1, cum = 1; i >= 0; i--) {
		ans = (ans + (long long) nums[i].second * cum) % mod;
		cum = ((long long) cum * nums[i].first) % mod;
	}
	printf("%d", ans);
	return 0;
}
