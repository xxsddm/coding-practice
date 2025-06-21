// https://codeforces.com/problemset/problem/1527/E

#include <cstring>
#include <iostream>

template <typename T>
inline void read(T &x) {
	x = 0;
	bool neg = false;
	char c = getchar();
	while (c < 48 || c > 57) {
		if (c == '-') {
			neg = true;
		}
		c = getchar();
	}
	while (c >= 48 && c <= 57) {
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = getchar();
	}
	if (neg) {
		x = -x;
	}
}

int *pre, *dp, *num2idx, *tree, *lazy;

void build(int cur, int start, int end) {
	lazy[cur] = 0;
	if (start == end) {
		tree[cur] = dp[start - 1];
		return;
	}
	int mid = (start + end) >> 1, next1 = cur << 1, next2 = next1 ^ 1;
	build(next1, start, mid);
	build(next2, mid + 1, end);
	tree[cur] = std::min(tree[next1], tree[next2]);
}

void change(int cur, int start, int end, int left, int right, int delta) {
	if (left <= start && right >= end) {
		tree[cur] += delta;
		lazy[cur] += delta;
		return;
	}
	int mid = (start + end) >> 1, next1 = cur << 1, next2 = next1 ^ 1;
	if (lazy[cur]) {
		int temp = lazy[cur];
		lazy[cur] = 0;
		tree[next1] += temp, tree[next2] += temp;
		lazy[next1] += temp, lazy[next2] += temp;
	}
	if (right <= mid) {
		change(next1, start, mid, left, right, delta);
	} else if (left > mid) {
		change(next2, mid + 1, end, left, right, delta);
	} else {
		change(next1, start, mid, left, right, delta);
		change(next2, mid + 1, end, left, right, delta);
	}
	tree[cur] = std::min(tree[next1], tree[next2]);
}

int query(int cur, int start, int end, int left, int right) {
	if (left <= start && right >= end) {
		return tree[cur];
	}
	int mid = (start + end) >> 1, next1 = cur << 1, next2 = next1 ^ 1;
	if (lazy[cur]) {
		int temp = lazy[cur];
		lazy[cur] = 0;
		tree[next1] += temp, tree[next2] += temp;
		lazy[next1] += temp, lazy[next2] += temp;
	}
	if (right <= mid) {
		return query(next1, start, mid, left, right);
	} else if (left > mid) {
		return query(next2, mid + 1, end, left, right);
	}
	return std::min(query(next1, start, mid, left, right),
	                query(next2, mid + 1, end, left, right));
}

int main() {
	int n, k;
	read(n), read(k);
	pre = new int[n + 1], dp = new int[n + 1], num2idx = new int[n + 1];
	tree = new int[n << 2], lazy = new int[n << 2];
	memset(num2idx + 1, 0, sizeof(int) * n);
	dp[0] = 0;
	for (int i = 1, num; i <= n; i++) {
		read(num);
		pre[i] = num2idx[num];
		num2idx[num] = i;
		dp[i] = dp[i - 1];
		if (pre[i]) {
			dp[i] += i - pre[i];
		}
	}
	// 线段树维护[1, j]切分时最后一段起点的位置及该分配方式取值
	// j = j + 1时, 有前驱元素则最后一段起点位于[1, pre[j]]取值增加
	for (int i = 2; i <= k; i++) {
		build(1, 1, n);
		for (int j = i; j <= n; j++) {
			if (pre[j]) {
				change(1, 1, n, 1, pre[j], j - pre[j]);
			}
			dp[j] = query(1, 1, n, 1, j);
		}
	}
	printf("%d\n", dp[n]);
	return 0;
}
