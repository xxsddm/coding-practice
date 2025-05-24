// http://oj.daimayuan.top/course/10/problem/846

#include "stack"
#include "iostream"

void read(int &x) {
	x = 0;
	char c = getchar();
	while (c >= 48 && c <= 57) {
		x = (x << 3) + (x << 1) + c - 48;
		c = getchar();
	}
}

int *nums, *left, *right, *left2, *right2;

int main() {
	int N;
	read(N);
	nums = new int[N], left = new int[N], right = new int[N];
	left2 = new int[N], right2 = new int[N];
	for (int i = 0; i < N; i++) {
		read(nums[i]);
		left2[i] = -1;
		right2[i] = N;
	}
	std::stack<int> stk, stk2, container;	// 双单调栈, 辅助栈维护单调性
	for (int i = 0, num; i < N; i++) {
		num = nums[i];
		while (!stk2.empty() && nums[stk2.top()] < num) {
			right2[stk2.top()] = i;	// 找到第二个更大值
			stk2.pop();
		}
		while (!stk.empty() && nums[stk.top()] < num) {
			right[stk.top()] = i;
			container.push(stk.top());	// 找到第一个更大值时, 入辅助栈
			stk.pop();
		}
		while (!container.empty()) {
			stk2.push(container.top());	// 由辅助栈移入单调栈2, 保持单调性
			container.pop();
		}
		stk.push(i);	// 移入单调栈1
	}
	while (!stk.empty()) {
		right[stk.top()] = N;
		stk.pop();
	}
	while (!stk2.empty()) {
		stk2.pop();
	}
	for (int i = N - 1, num; i >= 0; i--) {
		num = nums[i];
		while (!stk2.empty() && nums[stk2.top()] < num) {
			left2[stk2.top()] = i;
			stk2.pop();
		}
		while (!stk.empty() && nums[stk.top()] < num) {
			left[stk.top()] = i;
			container.push(stk.top());
			stk.pop();
		}
		while (!container.empty()) {
			stk2.push(container.top());
			container.pop();
		}
		stk.push(i);
	}
	while (!stk.empty()) {
		left[stk.top()] = -1;
		stk.pop();
	}
	long long ans = 0;
	for (int i = 0; i < N; i++) {
		if (left[i] != -1) {
			ans += ((long long) left[i] - left2[i]) * (right[i] - i) * nums[i];
		}
		if (right[i] != N) {
			ans += ((long long) right2[i] - right[i]) * (i - left[i]) * nums[i];
		}
	}
	printf("%lld", ans);
	return 0;
}
