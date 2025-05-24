// http://oj.daimayuan.top/course/11/problem/463

#include "cstring"
#include "iostream"

using namespace std;

int n, *nums;
long long k;

bool check(int round) {	// k是否可以完成round轮
	long long total = 0;
	for (int i = 0; i < n && total <= k; i++) {
		total += min(nums[i], round);
	}
	return total <= k;
}

int main() {	// 二分查找可完整完成的轮数, 最后剩余部分模拟
	int maxnum = 0;
	long long total = 0;
	scanf("%d %lld", &n, &k);
	nums = new int[n];
	for (int i = 0; i < n; i++) {
		scanf("%d", &nums[i]);
		total += nums[i];
		maxnum = max(maxnum, nums[i]);
	}
	if (total < k) {
		printf("%d", -1);
		return 0;
	}
	int left = 0, right = maxnum;
	bool container[2 * n + 1];
	memset(container, false, sizeof(container));
	total = 0;
	while (left <= right) {
		int mid = (left + right) >> 1;
		if (check(mid)) {
			left = mid + 1;
		} else {
			right = mid - 1;
		}
	}
	for (int i = 0; i < n; i++) {
		int temp = nums[i] < right ? nums[i] : right;
		nums[i] -= temp;
		total += temp;
	}
	for (int i = 0; i < n; i++) {
		if (!nums[i]) {
			continue;
		}
		if (total < k) {
			total++;
			if (--nums[i]) {
				container[i + 1 + n] = true;
			}
		} else {
			container[i + 1] = true;
		}
	}
	for (int i = 1, length = 2 * n + 1; i < length; i++) {
		if (container[i]) {
			printf("%d ", i > n ? i - n : i);
		}
	}
	return 0;
}
