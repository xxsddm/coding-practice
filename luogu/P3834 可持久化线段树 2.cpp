// https://www.luogu.com.cn/problem/P3834

#include "algorithm"
#include "iostream"

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

int numstk[30];

template <typename T>
inline void write(T x) {
	int length = 0;
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	while (x > 9) {
		numstk[length++] = x % 10;
		x /= 10;
	}
	numstk[length++] = x % 10;
	for (int i = length - 1; i >= 0; i--) {
		putchar(numstk[i] ^ 48);
	}
	putchar('\n');
}

int total = 0, *root, *nums, *container, *counter, *leftNode, *rightNode;

int build(int start, int end) {
	int node = total++;
	counter[node] = 0;
	if (start != end) {
		int mid = (start + end) >> 1;
		leftNode[node] = build(start, mid);
		rightNode[node] = build(mid + 1, end);
	}
	return node;
}

// 加入元素, 相当于修改当前加入元素所在二叉树路径中所有节点包含元素数量
int change(int start, int end, int idx, int prevNode) {
	int node = total++;
	if (start < end) {
		int mid = (start + end) >> 1;
		if (idx <= mid) {
			leftNode[node] = change(start, mid, idx, leftNode[prevNode]);
			rightNode[node] = rightNode[prevNode];
		} else {
			leftNode[node] = leftNode[prevNode];
			rightNode[node] = change(mid + 1, end, idx, rightNode[prevNode]);
		}
	}
	// 记录node包含的区间[start, end]中已加入元素数量
	counter[node] = counter[prevNode] + 1;
	return node;
}

int query(int start, int end, int node1, int node2, int k) {
	if (start == end) {
		return start;
	}
	int mid = (start + end) >> 1;
	// 左节点中包含元素数量(node1, node2均包含[start, end]信息)
	int count = counter[leftNode[node2]] - counter[leftNode[node1]];
	if (k <= count) {
		return query(start, mid, leftNode[node1], leftNode[node2], k);
	}
	return query(mid + 1, end, rightNode[node1], rightNode[node2], k - count);
}

int main() {
	int n, m;
	read(n), read(m);
	nums = new int[n + 1], container = new int[n + 1];
	for (int i = 1; i <= n; i++) {
		read(nums[i]);
		container[i] = nums[i];
	}
	std::sort(container + 1, container + n + 1);
	int subLen = std::unique(container + 1, container + n + 1) - container - 1;
	int length = (subLen << 2) + n * 21;
	root = new int[n + 1];
	counter = new int[length], leftNode = new int[length], rightNode = new int[length];
	root[0] = build(1, subLen);
	for (int i = 1, idx; i <= n; i++) {
		idx = std::lower_bound(container + 1, container + subLen + 1, nums[i]) - container;
		root[i] = change(1, subLen, idx, root[i - 1]);
	}
	for (int i = 0, l, r, k; i < m; i++) {
		read(l), read(r), read(k);
		write(container[query(1, subLen, root[l - 1], root[r], k)]);
	}
	return 0;
}
