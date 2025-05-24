// https://www.acwing.com/problem/content/1662/

#include "algorithm"
#include "iostream"

using namespace std;

int main() {
	int N;
	scanf("%d", &N);
	pair<int, int> nums[N];
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &nums[i].first, &nums[i].second);
	}
	sort(nums, nums + N);
	int radius = nums[N - 1].first - nums[0].first, ans = 0;
	for (int i = 1; i < N; i++) {
		if (nums[i].second) {
			if (!nums[i - 1].second) {
				radius = min(radius, nums[i].first - nums[i - 1].first - 1);
			}
		} else {
			if (nums[i - 1].second) {
				radius = min(radius, nums[i].first - nums[i - 1].first - 1);
			}
		}
	}
	bool keep = false;
	for (int i = 0; i < N; i++) {
		if (nums[i].second) {
			if (!keep) {
				ans++;
				keep = true;
			} else if (nums[i - 1].first + radius < nums[i].first) {
				ans++;
			}

		} else {
			keep = false;
		}
	}
	printf("%d", ans);
	return 0;
}
