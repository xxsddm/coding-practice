// https://www.luogu.com.cn/problem/P3373

#include "cstring"
#include "iostream"

int p, *nums, *lazyAdd, *lazyMul;

void push(int &node, int &start, int &end) {
	if (lazyMul[node] == 1 && lazyAdd[node] == 0) {
		return;
	}
	int mid = (start + end) >> 1;
	int nextNode1 = node << 1, nextNode2 = nextNode1 + 1;
	if (lazyMul[node] != 1) {
		nums[nextNode1] = (long long) nums[nextNode1] * lazyMul[node] % p;
		nums[nextNode2] = (long long) nums[nextNode2] * lazyMul[node] % p;
		lazyMul[nextNode1] = (long long) lazyMul[nextNode1] * lazyMul[node] % p;
		lazyMul[nextNode2] = (long long) lazyMul[nextNode2] * lazyMul[node] % p;
	}
	if (lazyAdd[node]) {
		nums[nextNode1] = (nums[nextNode1] + (long long) (mid - start + 1) * lazyAdd[node]) % p;
		nums[nextNode2] = (nums[nextNode2] + (long long) (end - mid) * lazyAdd[node]) % p;
	}
	lazyAdd[nextNode1] = ((long long) lazyAdd[nextNode1] * lazyMul[node] + lazyAdd[node]) % p;
	lazyAdd[nextNode2] = ((long long) lazyAdd[nextNode2] * lazyMul[node] + lazyAdd[node]) % p;
	lazyMul[node] = 1;
	lazyAdd[node] = 0;
}

void add(int node, int start, int end, int left, int right, int delta) {
	if (start > right || end < left) {
		return;
	}
	if (start >= left && end <= right) {
		nums[node] = (nums[node] + (long long) (end - start + 1) * delta) % p;
		lazyAdd[node] = (lazyAdd[node] + delta) % p;
		return;
	}
	push(node, start, end);
	int mid = (start + end) >> 1;
	int nextNode1 = node << 1, nextNode2 = nextNode1 + 1;
	add(nextNode1, start, mid, left, right, delta);
	add(nextNode2, mid + 1, end, left, right, delta);
	nums[node] = (nums[nextNode1] + nums[nextNode2]) % p;
}

void mul(int node, int start, int end, int left, int right, int k) {
	if (start > right || end < left) {
		return;
	}
	if (start >= left && end <= right) {
		nums[node] = (long long) nums[node] * k % p;
		lazyMul[node] = (long long) lazyMul[node] * k % p;
		lazyAdd[node] = (long long) lazyAdd[node] * k % p;
		return;
	}
	push(node, start, end);
	int mid = (start + end) >> 1;
	int nextNode1 = node << 1, nextNode2 = nextNode1 + 1;
	mul(nextNode1, start, mid, left, right, k);
	mul(nextNode2, mid + 1, end, left, right, k);
	nums[node] = (nums[nextNode1] + nums[nextNode2]) % p;
}

int query(int node, int start, int end, int left, int right) {
	if (start > right || end < left) {
		return 0;
	}
	if (start >= left && end <= right) {
		return nums[node];
	}
	push(node, start, end);
	int mid = (start + end) >> 1;
	int nextNode1 = node << 1, nextNode2 = nextNode1 + 1;
	return (query(nextNode1, start, mid, left, right) +
	        query(nextNode2, mid + 1, end, left, right)) % p;
}

int main() {
	int n, m;
	scanf("%d %d %d", &n, &m, &p);
	nums = new int[n << 2];
	lazyAdd = new int[n << 2];
	lazyMul = new int[n << 2];
	memset(nums, 0, sizeof(int) * (n << 2));
	memset(lazyAdd, 0, sizeof(int) * (n << 2));
	for (int i = 1, limit = n << 2; i < limit; i++) {
		lazyMul[i] = 1;
	}
	for (int i = 1; i <= n; i++) {
		long long num;
		scanf("%lld", &num);
		add(1, 1, n, i, i, (int) (num % p));
	}
	for (int i = 0; i < m; i++) {
		int op, x, y;
		scanf("%d", &op);
		if (op == 3) {
			scanf("%d %d", &x, &y);
			printf("%d\n", query(1, 1, n, x, y));
			continue;
		}
		long long k;
		scanf("%d %d %lld", &x, &y, &k);
		int kmod = k % p;
		if (op == 1) {
			mul(1, 1, n, x, y, kmod);
		} else {
			add(1, 1, n, x, y, kmod);
		}
	}
	return 0;
}

/*
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

int mod;

void passadd(Node &node, Node &leftnode, Node &rightnode, int start, int end) {
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

void passmul(Node &node, Node &leftnode, Node &rightnode) {
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

void passchange(Node &node, Node &leftnode, Node &rightnode, int start, int end) {
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

void pass(int cur, int start, int end) {
	if (start == end) {
		return;
	}
	int next1 = cur << 1, next2 = next1 ^ 1;
	Node &node = nodes[cur], &leftnode = nodes[next1], &rightnode = nodes[next2];
	passchange(node, leftnode, rightnode, start, end);
	passmul(node, leftnode, rightnode);
	passadd(node, leftnode, rightnode, start, end);
}

void add(int cur, int start, int end, int left, int right, int delta) {
	if (start > right || end < left) {
		return;
	}
	Node &node = nodes[cur];
	pass(cur, start, end);
	if (start >= left && end <= right) {
		node.add = delta;
		node.sum = (node.sum + (long long) delta * (end - start + 1)) % mod;
		return;
	}
	int mid = (start + end) >> 1;
	int next1 = cur << 1, next2 = next1 ^ 1;
	add(next1, start, mid, left, right, delta);
	add(next2, mid + 1, end, left, right, delta);
	node.sum = nodes[next1].sum + nodes[next2].sum;
	if (node.sum >= mod) {
		node.sum -= mod;
	}
}

void mul(int cur, int start, int end, int left, int right, int num) {
	if (start > right || end < left) {
		return;
	}
	Node &node = nodes[cur];
	pass(cur, start, end);
	if (start >= left && end <= right) {
		node.mul = num;
		node.sum = (long long) num * node.sum % mod;
		return;
	}
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
	pass(cur, start, end);
	if (start >= left && end <= right) {
		node.change = num;
		node.sum = (long long) num * (end - start + 1) % mod;
		return;
	}
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
	int mid = (start + end) >> 1;
	int next1 = cur << 1, next2 = next1 ^ 1;
	pass(cur, start, end);
	int ans = query(next1, start, mid, left, right)
	          + query(next2, mid + 1, end, left, right);
	if (ans >= mod) {
		ans -= mod;
	}
	return ans;
}

int main() {
	int n, m;
	read(n), read(m), read(mod);
	int length = n << 2;
	nodes = new Node[length];
	for (int i = 1, num; i <= n; i++) {
		read(num);
		change(1, 1, n, i, i, num);
	}
	for (int i = 0, op, l, r, d; i < m; i++) {
		read(op), read(l), read(r);
		if (op == 1) {
			read(d);
			mul(1, 1, n, l, r, d);
		} else if (op == 2) {
			read(d);
			add(1, 1, n, l, r, d);
		} else if (op == 3) {
			write(query(1, 1, n, l, r));
		}
	}
	return 0;
}
 */