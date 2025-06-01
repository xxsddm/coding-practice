// http://oj.daimayuan.top/course/15/problem/52

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
	putchar('\n');
}

struct Node {
	int counter[2] = {0, 0};
	Node *next[2] = {nullptr, nullptr};
} *root = new Node();

void add(int num) {
	Node *node = root;
	for (int temp = 1 << 29, i; temp; temp >>= 1) {
		i = num & temp ? 1 : 0;
		node->counter[i]++;
		if (node->next[i] == nullptr) {
			node->next[i] = new Node();
		}
		node = node->next[i];
	}
}

int query(int num, int k) {
	Node *node = root;
	int ans = 0;
	for (int temp = 1 << 29, i; temp; temp >>= 1) {
		i = num & temp ? 1 : 0;
		if (k <= node->counter[i]) {
			node = node->next[i];
		} else {
			ans ^= temp;
			k -= node->counter[i];
			node = node->next[i ^ 1];
		}
	}
	return ans;
}

int main() {
	int n, m;
	read(n), read(m);
	for (int i = 0, num; i < n; i++) {
		read(num);
		add(num);
	}
	for (int i = 0, num, k; i < m; i++) {
		read(num), read(k);
		write(query(num, k));
	}
	return 0;
}