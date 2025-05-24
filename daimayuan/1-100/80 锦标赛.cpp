// http://oj.daimayuan.top/course/11/problem/80

#include "algorithm"
#include "iostream"

using namespace std;

int *nums;

int main() {
	int n, k;
	scanf("%d %d", &n, &k);
	nums = new int[n];
	for (int i = 0; i < n; i++) {
		scanf("%d", &nums[i]);
	}
	sort(nums, nums + n);
	int ans = n;
	for (int i = n - 2; i >= 0; i--) {
		if (nums[i + 1] - nums[i] > k) {
			ans = n - i - 1;
			break;
		}
	}
	printf("%d", ans);
	return 0;
}
