// http://oj.daimayuan.top/course/15/problem/660

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

struct Node {
	int add = 0, mul = 1, change = 0, sum = 0;
} *nodes;

const long long mod = 1e9 + 7;

void pushadd(Node &node, Node &leftnode, Node &rightnode, int start, int end) {
	if (node.add == 0) {
		return;
	}
	int mid = (start + end) >> 1;
	long long temp = node.add;
	node.add = 0;
	leftnode.add += temp, rightnode.add += temp;
	if (leftnode.add >= mod) {
		leftnode.add -= mod;
	}
	if (rightnode.add >= mod) {
		rightnode.add -= mod;
	}
	leftnode.sum = (leftnode.sum + temp * (mid - start + 1)) % mod;
	rightnode.sum = (rightnode.sum + temp * (end - mid)) % mod;
}

void pushmul(Node &node, Node &leftnode, Node &rightnode) {
	if (node.mul == 1) {
		return;
	}
	long long temp = node.mul;
	node.mul = 1;
	leftnode.mul = temp * leftnode.mul % mod;
	rightnode.mul = temp * rightnode.mul % mod;
	leftnode.add = temp * leftnode.add % mod;
	rightnode.add = temp * rightnode.add % mod;
	leftnode.sum = (temp * leftnode.sum) % mod;
	rightnode.sum = (temp * rightnode.sum) % mod;
}

void pushchange(Node &node, Node &leftnode, Node &rightnode, int start, int end) {
	if (node.change == 0) {
		return;
	}
	int mid = (start + end) >> 1;
	long long temp = node.change;
	node.change = 0;
	leftnode.add = rightnode.add = 0;
	leftnode.mul = rightnode.mul = 1;
	leftnode.change = rightnode.change = temp;
	leftnode.sum = temp * (mid - start + 1) % mod;
	rightnode.sum = temp * (end - mid) % mod;
}

void push(int cur, int start, int end) {
	if (start == end) {
		return;
	}
	int next1 = cur << 1, next2 = next1 ^ 1;
	Node &node = nodes[cur], &leftnode = nodes[next1], &rightnode = nodes[next2];
	pushchange(node, leftnode, rightnode, start, end);
	pushmul(node, leftnode, rightnode);
	pushadd(node, leftnode, rightnode, start, end);
}

void add(int cur, int start, int end, int left, int right, int delta) {
	if (start > right || end < left) {
		return;
	}
	Node &node = nodes[cur];
	if (start >= left && end <= right) {
		node.add += delta;
		if (node.add >= mod) {
			node.add -= mod;
		}
		node.sum = (node.sum + (long long) delta * (end - start + 1)) % mod;
		return;
	}
	push(cur, start, end);
	int mid = (start + end) >> 1;
	int next1 = cur << 1, next2 = next1 ^ 1;
	add(next1, start, mid, left, right, delta);
	add(next2, mid + 1, end, left, right, delta);
	node.sum = nodes[next1].sum + nodes[next2].sum;
	if (node.sum >= mod) {
		node.sum -= mod;
	}
}

void mul(int cur, int start, int end, int left, int right, long long num) {
	if (start > right || end < left) {
		return;
	}
	Node &node = nodes[cur];
	if (start >= left && end <= right) {
		node.mul = (num * node.mul) % mod;
		if (node.add) {
			node.add = (num * node.add) % mod;
		}
		node.sum = num * node.sum % mod;
		return;
	}
	push(cur, start, end);
	int mid = (start + end) >> 1;
	int next1 = cur << 1, next2 = next1 ^ 1;
	mul(next1, start, mid, left, right, num);
	mul(next2, mid + 1, end, left, right, num);
	node.sum = nodes[next1].sum + nodes[next2].sum;
	if (node.sum >= mod) {
		node.sum -= mod;
	}
}

void change(int cur, int start, int end, int left, int right, int num) {
	if (start > right || end < left) {
		return;
	}
	Node &node = nodes[cur];
	if (start >= left && end <= right) {
		node.change = num;
		node.add = 0;
		node.mul = 1;
		node.sum = (long long) num * (end - start + 1) % mod;
		return;
	}
	push(cur, start, end);
	int mid = (start + end) >> 1;
	int next1 = cur << 1, next2 = next1 ^ 1;
	change(next1, start, mid, left, right, num);
	change(next2, mid + 1, end, left, right, num);
	node.sum = nodes[next1].sum + nodes[next2].sum;
	if (node.sum >= mod) {
		node.sum -= mod;
	}
}

int query(int cur, int start, int end, int left, int right) {
	if (start > right || end < left) {
		return 0;
	}
	Node &node = nodes[cur];
	if (start >= left && end <= right) {
		return node.sum;
	}
	push(cur, start, end);
	int mid = (start + end) >> 1;
	int next1 = cur << 1, next2 = next1 ^ 1;
	int ans = query(next1, start, mid, left, right)
	          + query(next2, mid + 1, end, left, right);
	if (ans >= mod) {
		ans -= mod;
	}
	return ans;
}

int main() {	// 注意三种标记的先后顺序和影响
	int n, q;
	read(n), read(q);
	int length = n << 2;
	nodes = new Node[length];
	for (int i = 1, num; i <= n; i++) {
		read(num);
		change(1, 1, n, i, i, num);
	}
	for (int i = 0, op, l, r, d; i < q; i++) {
		read(op), read(l), read(r);
		if (op == 1) {
			read(d);
			add(1, 1, n, l, r, d);
		} else if (op == 2) {
			read(d);
			mul(1, 1, n, l, r, d);
		} else if (op == 3) {
			read(d);
			change(1, 1, n, l, r, d);
		} else {
			write(query(1, 1, n, l, r));
		}
	}
	return 0;
}