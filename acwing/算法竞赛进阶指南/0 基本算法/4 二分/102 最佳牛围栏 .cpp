// https://www.acwing.com/problem/content/description/104/

#include "iostream"

using namespace std;

int N, F;

bool check(int mean, int* nums) {
	long long cumsum = 0;	// 长度不小于F-1的最大前缀和
	int left = 0, right = F - 1;
	for (int i = left; i < right; i++) {
		cumsum += nums[i] - mean;
	}
	long long prev = cumsum;	// F-1长度的和
	while (right < N) {
		cumsum += nums[right] - mean;
		prev += nums[right] - mean;
		cumsum = max(cumsum, prev);	// 当前数选择两者较大值拼接连续子数组
		if (cumsum >= 0) {
			return true;
		}
		prev -= nums[left++] - mean;
		right++;
	}
	return false;
}

int main() {
	scanf("%d %d", &N, &F);
	int nums[N], left = 2000000, right = 1000;
	for (int i = 0; i < N; i++) {
		scanf("%d", &nums[i]);
		nums[i] *= 1000;
		left = min(left, nums[i]);
		right = max(right, nums[i]);
	}
	while (left <= right) {
		int mid = (left + right) >> 1;
		if (check(mid, nums)) {
			left = mid + 1;
		} else {
			right = mid - 1;
		}
	}
	printf("%d", right);
	return 0;
}
