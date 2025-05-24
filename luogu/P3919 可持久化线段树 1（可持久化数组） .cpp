// https://www.luogu.com.cn/problem/P3919

#include "iostream"

template <typename T>
inline void read(T &x) {
	x = 0;
	char c = getchar();
	bool neg = false;
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

int N, total = 0, *nums, *root, *val, *leftNode, *rightNode;

int build(int start, int end) {
	int node = total++;
	if (start == end) {
		val[node] = nums[start];
	} else {
		int mid = (start + end) >> 1;
		leftNode[node] = build(start, mid);
		rightNode[node] = build(mid + 1, end);
	}
	return node;
}

int change(int start, int end, int idx, int prevNode, int value) {
	int node = total++;
	if (start == end) {
		val[node] = value;
	} else {
		int mid = (start + end) >> 1;
		if (idx <= mid) {
			leftNode[node] = change(start, mid, idx, leftNode[prevNode], value);
			rightNode[node] = rightNode[prevNode];
		} else {
			leftNode[node] = leftNode[prevNode];
			rightNode[node] = change(mid + 1, end, idx, rightNode[prevNode], value);
		}
	}
	return node;
}

int query(int start, int end, int idx, int node) {
	while (start < end) {
		int mid = (start + end) >> 1;
		if (idx <= mid) {
			end = mid;
			node = leftNode[node];
		} else {
			start = mid + 1;
			node = rightNode[node];
		}
	}
	return val[node];
}

int main() {
	int M;
	read(N), read(M);
	root = new int[M + 1];
	int length = (N << 2) + 20 * M;
	nums = new int[N + 1];
	val = new int[length];
	leftNode = new int[length], rightNode = new int[length];
	for (int i = 1; i <= N; i++) {
		read(nums[i]);
	}
	root[0] = build(1, N);
	for (int i = 1, v, opt, loc, value; i <= M; i++) {
		read(v), read(opt), read(loc);
		if (opt == 1) {
			read(value);
			root[i] = change(1, N, loc, root[v], value);
		} else {
			root[i] = root[v];
			write(query(1, N, loc, root[i]));
		}
	}
	return 0;
}