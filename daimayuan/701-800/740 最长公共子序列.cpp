// http://oj.daimayuan.top/course/11/problem/740

#include "iostream"

int *num2idx, *nums, *container;

int main() {
	int n;
	scanf("%d", &n);
	num2idx = new int[n + 1];
	nums = new int[n];
	container = new int[n];
	// 数组1重新编码为1-n
	for (int i = 0, num; i < n; i++) {
		scanf("%d", &num);
		num2idx[num] = i;
	}
	// 数组2按照相同编码方式转换
	for (int i = 0, num; i < n; i++) {
		scanf("%d", &num);
		nums[i] = num2idx[num];
	}
	// lcs
	int length = 0;
	for (int i = 0; i < n; i++) {
		int &num = nums[i], left = 0, right = length - 1, mid;
		while (left <= right) {
			mid = (left + right) >> 1;
			if (container[mid] < num) {
				left = mid + 1;
			} else {
				right = mid - 1;
			}
		}
		container[left] = num;
		if (left == length) {
			length++;
		}
	}
	printf("%d", length);
	return 0;
}
