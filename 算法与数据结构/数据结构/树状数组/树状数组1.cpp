// http://oj.daimayuan.top/course/15/problem/634

#include "cstring"
#include "iostream"

int n, *nums;
long long *container;

void change(int idx, int val) {
	int delta = val - nums[idx];
	nums[idx] = val;
	while (idx <= n) {
		container[idx] += delta;
		idx += idx & -idx;
	}
}

long long query(int idx) {
	long long ans = 0;
	while (idx) {
		ans += container[idx];
		idx ^= idx & -idx;
	}
	return ans;
}

int main() {	// container[i]包含[i - lowbit(i) + 1, i]信息
	int q;
	scanf("%d %d", &n, &q);
	nums = new int[n + 1];
	container = new long long[n + 1];
	memset(container, 0, sizeof(long long) * (n + 1));
	for (int i = 1, num; i <= n; i++) {
		scanf("%d", &num);
		nums[i] = 0;
		change(i, num);
	}
	for (int i = 0, op, x, d; i < q; i++) {
		scanf("%d %d", &op, &x);
		if (op == 1) {
			scanf("%d", &d);
			change(x, d);
		}
		else {
			printf("%lld\n", query(x));
		}
	}
	return 0;
}
