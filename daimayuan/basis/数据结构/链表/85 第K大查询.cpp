// http://oj.daimayuan.top/course/15/problem/85

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

struct Node {
	int idx;
	Node *prev = nullptr, *next = nullptr;
} **num2node;

inline void del(Node *node) {
	if (node->prev != nullptr) {
		node->prev->next = node->next;
	}
	if (node->next != nullptr) {
		node->next->prev = node->prev;
	}
}

int main() {
	int n, k;
	read(n), read(k);
	num2node = new Node*[n + 1];
	num2node[0] = new Node();
	Node *prev = num2node[0];
	for (int i = 1, num; i <= n; i++) {
		read(num);
		Node *temp = new Node();
		temp->idx = i;
		prev->next = temp;
		temp->prev = prev;
		num2node[num] = temp;
		prev = temp;
	}
	del(num2node[0]);
	long long ans = 0;
	for (int i = 1, m = n - k + 1; i <= m; i++) {
		Node *left = num2node[i], *right = left;
		int countLeft = 0, countRight = 0;
		while (countLeft < k - 1 && left->prev != nullptr) {
			left = left->prev;
			countLeft++;
		}
		while (countLeft + countRight < k - 1) {
			right = right->next;
			countRight++;
		}
		while (countRight <= k - 1 && right != nullptr) {
			long long leftPart = left->idx - (left->prev == nullptr ? 0 : left->prev->idx);
			long long rightPart = (right->next == nullptr ? n + 1 : right->next->idx) - right->idx;
			ans += leftPart * rightPart * i;
			left = left->next;
			right = right->next;
			countRight++;
		}
		del(num2node[i]);
	}
	printf("%lld", ans);
	return 0;
}
