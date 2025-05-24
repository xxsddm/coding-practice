// http://oj.daimayuan.top/course/10/problem/454

#include "queue"
#include "iostream"

using namespace std;

struct Edge {
	int u, v, w;
};

int n, m, *root, *size;
deque<Edge> rest;

int find(int idx) {
	while (idx != root[idx]) {
		root[idx] = root[root[idx]];
		idx = root[idx];
	}
	return idx;
}

void merge(int node1, int node2) {
	int idx1 = find(node1), idx2 = find(node2);
	if (idx1 == idx2) {
		return;
	}
	if (size[idx1] >= size[idx2]) {
		size[idx1] += size[idx2];
		root[idx2] = idx1;
	} else {
		size[idx2] += size[idx1];
		root[idx1] = idx2;
	}
}

bool need(int base) {	// 检查该二进制位置是否必须取1
	deque<Edge> back;
	for (int i = 0; i < n; i++) {
		root[i] = i;
		size[i] = 1;
	}
	for (int i = 0, length = (int) rest.size(); i < length; i++) {
		Edge edge = rest.front();
		rest.pop_front();
		if (edge.w & base) {
			back.push_back(edge);
		} else {
			merge(edge.u, edge.v);
			rest.push_back(edge);
		}
	}
	for (int i = 0; i < n; i++) {
		if (size[i] == n) {
			return false;
		}
	}
	while (!back.empty()) {
		rest.push_back(back.front());
		back.pop_front();
	}
	return true;
}

int main() {
	scanf("%d %d", &n, &m);
	int ans = 0, maxnum = 0, base = 1 << 30;
	root = new int[n], size = new int[n];
	for (int i = 0; i < m; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		u--, v--;
		rest.push_back({u, v, w});
		maxnum = max(maxnum, w);
	}
	while (!(maxnum & base)) {
		base >>= 1;
	}
	while (base) {
		if (need(base)) {
			ans ^= base;
		}
		base >>= 1;
	}
	printf("%d", ans);
	return 0;
}
