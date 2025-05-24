// https://www.acwing.com/problem/content/1857/

#include "algorithm"
#include "iostream"

using namespace std;

int main() {
	int N, ans = 0;
	cin >> N;
	int nums[N];
	for (int i = 0; i < N; i++) {
		scanf("%d", &nums[i]);
	}
	sort(nums, nums + N);
	for (int i = 0; i < N; i++) {
		int start = i, end = i, radius = 1;
		int left = nums[i], right = left;
		while (start - 1 >= 0 && left - nums[start - 1] <= radius) {
			while (start - 1 >= 0 && left - nums[start - 1] <= radius) {
				start--;
			}
			left = nums[start];
			radius++;
		}
		radius = 1;
		while (end + 1 < N && nums[end + 1] - right <= radius) {
			while (end + 1 < N && nums[end + 1] - right <= radius) {
				end++;
			}
			right = nums[end];
			radius++;
		}
		ans = max(ans, end - start + 1);
	}
	cout << ans;
	return 0;
}
