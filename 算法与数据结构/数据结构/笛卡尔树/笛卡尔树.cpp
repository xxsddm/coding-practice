// http://oj.daimayuan.top/course/15/problem/717

#include "stack"
#include "iostream"

template <typename T>
inline void read(T &x) {
	x = 0;
	char c = getchar();
	while (c < 48 || c > 57) {
		c = getchar();
	}
	while (c >= 48 && c <= 57) {
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = getchar();
	}
}

int numstk[30];

template <typename T>
inline void write(T x) {
	int length = 0;
	while (x > 9) {
		numstk[length++] = x % 10;
		x /= 10;
	}
	numstk[length++] = x;
	for (int i = length - 1; i >= 0; i--) {
		putchar(numstk[i] ^ 48);
	}
	putchar(' ');
}

int idx = 1, *nums, *left, *right;

void dfs(int node) {
	if (node == 0) {
		return;
	}
	nums[node] = idx++;
	dfs(left[node]);
	dfs(right[node]);
}

int main() {	// 两种排列笛卡尔树相同, 考虑建树后前序遍历修改值
	int n;
	read(n);
	nums = new int[n + 1];
	left = new int[n + 1], right = new int[n + 1];
	for (int i = 1; i <= n; i++) {
		read(nums[i]);
		left[i] = right[i] = 0;
	}
	int root = 0;
	std::stack<int> stk;
	for (int i = 1; i <= n; i++) {
		int &num = nums[i], last = 0;
		while (!stk.empty() && num < nums[stk.top()]) {
			last = stk.top();
			stk.pop();
		}
		if (stk.empty()) {
			root = i;
		} else {
			right[stk.top()] = i;
		}
		left[i] = last;
		stk.push(i);
	}
	dfs(root);
	for (int i = 1; i <= n; i++) {
		write(nums[i]);
	}
	return 0;
}