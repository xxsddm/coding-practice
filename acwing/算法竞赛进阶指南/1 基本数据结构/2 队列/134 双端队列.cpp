// https://www.acwing.com/problem/content/description/136/

#include "algorithm"
#include "iostream"

using namespace std;

int main() {	// 排序后相邻区域原始索引可形成V形即可使用同一双端队列(不可倒V形)
	int N, ans = 0;
	scanf("%d", &N);
	pair<int, int> nums[N];
	for (int i = 0; i < N; i++) {
		scanf("%d", &nums[i].first);
		nums[i].second = i;
	}
	sort(nums, nums + N, [](auto & p1, auto & p2) -> bool {
		if (p1.first != p2.first) {
			return p1.first < p2.first;
		}
		return p1.second < p2.second;
	});
	int idx = 0, prev = 1;
	bool decrease = false;	// 形成V形
	while (idx < N) {
		int num = nums[idx].first, start = nums[idx++].second;
		while (idx < N && nums[idx].first == num) {
			idx++;
		}
		int end = nums[idx - 1].second;
		if (decrease) {
			if (prev > end) {
				prev = start;
			} else {
				prev = end;
				decrease = false;
			}
		} else {
			if (prev < start) {
				prev = end;
			} else {
				prev = start;
				ans++;
				decrease = true;
			}
		}

	}
	printf("%d", ans);
	return 0;
}
