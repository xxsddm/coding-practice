// https://www.acwing.com/problem/content/1947/

#include "algorithm"
#include "iostream"

using namespace std;

int N;

int bisect(int start, int target, int *nums, bool equal) {
	int left = start, right = N - 1;
	while (left <= right) {
		int mid = (left + right) >> 1;
		if (nums[mid] < target || equal && nums[mid] == target) {
			left = mid + 1;
		} else {
			right = mid - 1;
		}
	}
	return equal ? right : left;
}

int main() {
	cin >> N;
	int nums[N], ans = 0;
	for (int i = 0; i < N; i++) {
		scanf("%d", &nums[i]);
	}
	sort(nums, nums + N);
	// 枚举X, Y位置
	for (int x = 0; x < N - 2; x++) {
		for (int y = x + 1; y < N - 1; y++) {
			int diff = nums[y] - nums[x];
			ans += bisect(y + 1, nums[y] + 2 * diff, nums, true) - bisect(y + 1, nums[y] + diff, nums, false) + 1;
		}
	}
	printf("%d", ans);
	return 0;
}
