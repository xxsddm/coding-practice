// https://www.acwing.com/problem/content/1954/

#include "algorithm"
#include "iostream"

using namespace std;

int countLess(int target, int length, int *nums, bool strictLess) {
	int left = 0, right = length - 1;
	while (left <= right) {
		int mid = (left + right) >> 1;
		if (target < nums[mid] || strictLess && target == nums[mid]) {
			right = mid - 1;
		} else {
			left = mid + 1;
		}
	}
	return left;
}

int main() {
	int N, X, Y, Z, ans = 0, idx = 0;
	scanf("%d %d %d %d", &N, &X, &Y, &Z);
	int nums1[N], nums2[N];
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &nums1[i], &nums2[i]);
	}
	sort(nums1, nums1 + N);
	sort(nums2, nums2 + N);
	while (idx < N) {
		while (idx + 1 < N && nums1[idx + 1] == nums1[idx]) {
			idx++;
		}
		int numLess = countLess(nums1[idx], N, nums2, true);
		ans = max(ans, (N - idx - 1) * X + numLess * Z + (idx + 1 - numLess) * Y);
		idx++;
	}
	idx = 0;
	while (idx < N) {
		while (idx < N && idx && nums2[idx - 1] == nums2[idx]) {
			idx++;
		}
		if (idx == N) {
			break;
		}
		int numLarge = N - countLess(nums2[idx], N, nums1, false);
		ans = max(ans, numLarge * X + idx * Z + (N - idx - numLarge) * Y);
		idx++;
	}
	printf("%d", ans);
	return 0;
}
