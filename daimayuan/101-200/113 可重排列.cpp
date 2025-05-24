// http://oj.daimayuan.top/course/11/problem/113

#include "iostream"

int length = 0, *nums, *counter;

void output() {
	for (int i = 0; i < length; i++) {
		printf("%d ", nums[i]);
	}
	printf("\n");
}

int main() {
	int n;
	scanf("%d", &n);
	counter = new int[n + 1];
	for (int i = 1; i <= n; i++) {
		scanf("%d", &counter[i]);
		length += counter[i];
	}
	nums = new int[length];
	for (int i = 1, idx = 0; i <= n; i++) {
		for (int j = 0, limit = counter[i]; j < limit; j++) {
			nums[idx++] = i;
		}
	}
	bool keep = true;
	while (keep) {
		output();
		int idx1 = -1, idx2 = 0;
		for (int i = length - 2; i >= 0; i--) {
			if (nums[i] < nums[i + 1]) {
				idx1 = i;
				break;
			}
		}
		if (idx1 == -1) {
			keep = false;
			continue;
		}
		for (int i = length - 1; i >= 0; i--) {
			if (nums[i] > nums[idx1]) {
				idx2 = i;
				break;
			}
		}
		std::swap(nums[idx1], nums[idx2]);
		int left = idx1 + 1, right = length - 1;
		while (left < right) {
			std::swap(nums[left++], nums[right--]);
		}
	}
	return 0;
}
