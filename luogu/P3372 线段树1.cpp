// https://www.luogu.com.cn/problem/P3372

#include "cstring"
#include "iostream"

long long *nums, *lazy;

// lazy怠惰标记, lazy[node]表示传递到node(含), 但没有传递到node子节点的更新操作
void add(int node, int start, int end, int left, int right, int delta) {
	if (left > end || right < start) {
		return;
	}
	if (left <= start && right >= end) {
		nums[node] += (long long) (end - start + 1) * delta;
		lazy[node] += delta;
		return;
	}
	int nextNode1 = node << 1, nextNode2 = nextNode1 + 1;
	int mid = (start + end) >> 1;
	if (lazy[node] && start != end) {
		nums[nextNode1] += (long long) (mid - start + 1) * lazy[node];
		nums[nextNode2] += (long long) (end - mid) * lazy[node];
		lazy[nextNode1] += lazy[node];
		lazy[nextNode2] += lazy[node];
		lazy[node] = 0;
	}
	add(nextNode1, start, mid, left, right, delta);
	add(nextNode2, mid + 1, end, left, right, delta);
	nums[node] = nums[nextNode1] + nums[nextNode2];
}

long long query(int node, int start, int end, int left, int right) {
	if (left > end || right < start) {
		return 0;
	}
	if (left <= start && right >= end) {
		return nums[node];
	}
	int nextNode1 = node << 1, nextNode2 = nextNode1 + 1;
	int mid = (start + end) >> 1;
	if (lazy[node] && start != end) {
		nums[nextNode1] += (long long) (mid - start + 1) * lazy[node];
		nums[nextNode2] += (long long) (end - mid) * lazy[node];
		lazy[nextNode1] += lazy[node];
		lazy[nextNode2] += lazy[node];
		lazy[node] = 0;
	}
	return query(nextNode1, start, mid, left, right) +
	       query(nextNode2, mid + 1, end, left, right);
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	nums = new long long[n << 2];
	lazy = new long long[n << 2];
	memset(nums, 0, sizeof(long long) * (n << 2));
	memset(lazy, 0, sizeof(long long) * (n << 2));
	for (int i = 1; i <= n; i++) {
		int num;
		scanf("%d", &num);
		add(1, 1, n, i, i, num);
	}
	for (int i = 0; i < m; i++) {
		int op, x, y, k;
		scanf("%d", &op);
		if (op == 1) {
			scanf("%d %d %d", &x, &y, &k);
			add(1, 1, n, x, y, k);
		} else {
			scanf("%d %d", &x, &y);
			printf("%lld\n", query(1, 1, n, x, y));
		}
	}
	return 0;
}
