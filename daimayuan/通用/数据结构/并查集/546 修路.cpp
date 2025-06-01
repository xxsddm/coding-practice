// http://oj.daimayuan.top/course/7/problem/546

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

int *root, *size;

int find(int node) {
	while (node != root[node]) {
		root[node] = root[root[node]];
		node = root[node];
	}
	return node;
}

bool merge(int node1, int node2) {
	int idx1 = find(node1), idx2 = find(node2);
	if (idx1 == idx2) {
		return false;
	}
	if (size[idx1] >= size[idx2]) {
		size[idx1] += size[idx2];
		root[idx2] = idx1;
	} else {
		size[idx2] += size[idx1];
		root[idx1] = idx2;
	}
	return true;
}

int main() {
	int n, m;
	read(n), read(m);
	root = new int[n + 1], size = new int[n + 1];
	for (int i = 1; i <= n; i++) {
		root[i] = i;
		size[i] = 1;
	}
	int count = 0;
	for (int i = 0, x, y; i < m; i++) {
		read(x), read(y);
		if (merge(x, y)) {
			count++;
		}
	}
	printf("%d", n - 1 - count);
	return 0;
}