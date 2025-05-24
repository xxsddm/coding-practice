// http://oj.daimayuan.top/course/11/problem/554

#include "iostream"

int main() {
	int t, n;
	int add = 1000000, nums[40];
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%d", &nums[i]);
			nums[i] += add;
		}
		bool judge = true;
		int num = nums[0];
		for (int i = 1; i < n; i++) {
			if (nums[i] != num) {
				judge = false;
				break;
			}
		}
		if (judge) {
			printf("-1\n");
			continue;
		}
		for (int k = add << 1; k > 0; k--) {
			int num = nums[0] % k;
			judge = true;
			for (int i = 1; i < n; i++) {
				if (nums[i] % k != num) {
					judge = false;
					break;
				}
			}
			if (judge) {
				printf("%d\n", k);
				break;
			}
		}
	}
	return 0;
}
