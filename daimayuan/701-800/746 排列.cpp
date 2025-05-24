// http://oj.daimayuan.top/course/10/problem/746

#include "algorithm"
#include "iostream"

std::pair<int, int> nums[100];

bool solve() {
	int N;
	scanf("%d", &N);
	int total = 0;
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &nums[i].first, &nums[i].second);
		total += nums[i].second;
	}
	if (N == 2) {
		return true;
	}
	sort(nums, nums + N, [] (auto & p1, auto & p2) -> bool {
		if (p1.first != p2.first) {
			return p1.first < p2.first;
		}
		return p1.second > p2.second;
	});
	// 极端情况为其余元素增益全部加入当前位置i, 且i + 1无增益
	for (int i = 0, limit = N - 1; i < limit; i++) {
		if (nums[i].first + total - nums[i].second > nums[i + 1].first) {
			return false;
		}
	}
	return true;
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		printf(solve() ? "Yes\n" : "No\n");
	}
	return 0;
}
