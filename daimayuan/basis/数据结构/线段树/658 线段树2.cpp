// http://oj.daimayuan.top/course/15/problem/658

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
	numstk[length++] = x;
	for (int i = length - 1; i >= 0; i--) {
		putchar(numstk[i] ^ 48);
	}
	putchar('\n');
}

struct Node {	// 结构体便于维护递归过程中复杂信息
	long long left, right, maxsum, total;

	Node operator + (const Node &rightnode) {
		long long l = std::max(left, total + rightnode.left);
		long long r = std::max(rightnode.right, rightnode.total + right);
		long long ms = std::max(right + rightnode.left, std::max(maxsum, rightnode.maxsum));
		long long t = total + rightnode.total;
		return {l, r, ms, t};
	}
} *nodes;

void change(int cur, int start, int end, int idx, int num) {
	if (start > idx || end < idx) {
		return;
	}
	if (start == end) {
		Node &node = nodes[cur];
		node.left = node.right = node.maxsum = node.total = num;
		return;
	}
	int mid = (start + end) >> 1;
	int leftnode = cur << 1, rightnode = leftnode ^ 1;
	change(leftnode, start, mid, idx, num);
	change(rightnode, mid + 1, end, idx, num);
	nodes[cur] = nodes[leftnode] + nodes[rightnode];
}

Node query(int cur, int start, int end, int left, int right) {
	if (start >= left && end <= right) {
		return nodes[cur];
	}
	int mid = (start + end) >> 1;
	int leftnode = cur << 1, rightnode = leftnode ^ 1;
	if (left > mid) {
		return query(rightnode, mid + 1, end, left, right);
	} else if (right <= mid) {
		return query(leftnode, start, mid, left, right);
	}
	return query(leftnode, start, mid, left, right)
	       + query(rightnode, mid + 1, end, left, right);
}

int main() {
	int n, q;
	read(n), read(q);
	int length = n << 2;
	nodes = new Node[length];
	for (int i = 1, num; i <= n; i++) {
		read(num);
		change(1, 1, n, i, num);
	}
	for (int i = 0, op, x, d, l, r; i < q; i++) {
		read(op);
		if (op == 1) {
			read(x), read(d);
			change(1, 1, n, x, d);
		} else {
			read(l), read(r);
			write(query(1, 1, n, l, r).maxsum);
		}
	}
	return 0;
}