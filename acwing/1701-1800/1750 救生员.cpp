// https://www.acwing.com/problem/content/description/1752/

#include "algorithm"
#include "iostream"

using namespace std;

int main() {
	int N, ans = -1;
	scanf("%d", &N);
	pair<int, int> nums[N];
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &nums[i].first, &nums[i].second);
	}
	sort(nums, nums + N, [](auto & p1, auto & p2) -> bool {
		if (p1.first != p2.first) {
			return p1.first < p2.first;
		}
		return p1.second < p2.second;
	});
	for (int remove = 0; remove < N; remove++) {
		int temp = 0;
		for (int i = 0, end = 0; i < N; i++) {
			if (nums[i].second <= end || i == remove) {
				continue;
			}
			int left = nums[i].first, right = nums[i].second;
			temp += right - max(end, left);
			end = right;
		}
		ans = max(ans, temp);
	}
	printf("%d", ans);
	return 0;
}
