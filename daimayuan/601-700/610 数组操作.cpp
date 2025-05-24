// http://oj.daimayuan.top/course/11/problem/610

#include "iostream"

int nums[200001];

int main() {
	int t, n;
	scanf("%d", &t);
	while (t--) {
		// 末尾元素无法改变, 则贪心使用尾部元素覆盖前部分
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &nums[i]);
		}
		int ans = 0, idx = n, target = nums[n];
		while (idx > 1) {
			while (idx > 1 && nums[idx - 1] == target) {
				idx--;
			}
			if (idx > 1) {
				int length = n - idx + 1;
				idx = n - length * 2 + 1;
				ans++;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
