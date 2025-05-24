// http://oj.daimayuan.top/course/10/problem/807

#include "iostream"

int *root, *size;

int find(int idx) {
	while (idx != root[idx]) {
		root[idx] = root[root[idx]];
		idx = root[idx];
	}
	return idx;
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

int main() {	// 连接两个连通块的为当前最后加入
	int n, m;
	scanf("%d %d", &n, &m);
	root = new int[n + 1];
	size = new int[n + 1];
	for (int i = 1; i <= n; i++) {
		root[i] = i;
		size[i] = 1;
	}
	int ans = 0;
	for (int i = 0, x, y; i < m; i++) {
		scanf("%d %d", &x, &y);
		if (!merge(x, y)) {
			ans++;
		}
	}
	printf("%d", ans);
	return 0;
}
