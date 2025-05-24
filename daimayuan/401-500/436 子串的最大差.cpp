// http://oj.daimayuan.top/course/10/problem/436

#include "stack"
#include "iostream"

using namespace std;

int main() {	// 相同元素则考虑右侧元素有效范围可向左延伸, 即确定左边界时需严格大于/小于才可出栈
	int n;
	scanf("%d", &n);
	long long ans = 0;
	int nums[n], left[n], right[n];
	stack<int> stk;
	for (int i = 0; i < n; i++) {
		scanf("%d", &nums[i]);
	}
	for (int i = 0; i < n; i++) {
		int &num = nums[i];
		while (!stk.empty() && num >= nums[stk.top()]) {
			right[stk.top()] = i;
			stk.pop();
		}
		stk.push(i);
	}
	while (!stk.empty()) {
		right[stk.top()] = n;
		stk.pop();
	}
	for (int i = n - 1; i >= 0; i--) {
		int &num = nums[i];
		while (!stk.empty() && num > nums[stk.top()]) {
			left[stk.top()] = i;
			stk.pop();
		}
		stk.push(i);
	}
	while (!stk.empty()) {
		left[stk.top()] = -1;
		stk.pop();
	}
	for (int i = 0; i < n; i++) {
		ans += 1LL * (right[i] - i) * (i - left[i]) * nums[i];
	}
	for (int i = 0; i < n; i++) {
		int &num = nums[i];
		while (!stk.empty() && num <= nums[stk.top()]) {
			right[stk.top()] = i;
			stk.pop();
		}
		stk.push(i);
	}
	while (!stk.empty()) {
		right[stk.top()] = n;
		stk.pop();
	}
	for (int i = n - 1; i >= 0; i--) {
		int &num = nums[i];
		while (!stk.empty() && num < nums[stk.top()]) {
			left[stk.top()] = i;
			stk.pop();
		}
		stk.push(i);
	}
	while (!stk.empty()) {
		left[stk.top()] = -1;
		stk.pop();
	}
	for (int i = 0; i < n; i++) {
		ans -= 1LL * (right[i] - i) * (i - left[i]) * nums[i];
	}
	printf("%lld", ans);
	return 0;
}
