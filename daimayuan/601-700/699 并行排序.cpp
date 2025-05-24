// http://oj.daimayuan.top/course/10/problem/699

#include "iostream"

int n, length, container[1000000];

int find(int num) {
	int left = 0, right = length - 1;
	while (left <= right) {
		int mid = (left + right) >> 1;
		if (container[mid] > num) {
			left = mid + 1;
		} else if (container[mid] < num) {
			right = mid - 1;
		} else {
			return mid;
		}
	}
	return left;
}

int main() {	// 非减子序列最少数量 = 递减子序列最大长度
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		length = 0;
		for (int i = 0, num, idx; i < n; i++) {
			scanf("%d", &num);
			idx = find(num);
			container[idx] = num;
			if (idx == length) {
				length++;
			}
		}
		printf("%d\n", length);
	}
	return 0;
}
