// http://oj.daimayuan.top/course/15/problem/793

#include "array"
#include "unordered_set"
#include "algorithm"
#include "iostream"

using namespace std;

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

int numstk[20];

template <typename T>
inline void write(T x) {
	int tempLen = 0;
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	while (x > 9) {
		numstk[tempLen++] = x % 10;
		x /= 10;
	}
	numstk[tempLen++] = x;
	for (int i = tempLen - 1; i >= 0; i--) {
		putchar(numstk[i] ^ 48);
	}
	putchar('\n');
}

int *parent, *ans;
array<int, 3> *edges;
unordered_set<int> *query;

int find(int idx) {
	while (idx != parent[idx]) {
		idx = parent[idx] = parent[parent[idx]];
	}
	return idx;
}

int main() {
	int n, q;
	read(n), read(q);
	parent = new int[n + 1], ans = new int[q];
	edges = new array<int, 3>[n - 1];
	query = new unordered_set<int>[n + 1];
	for (int i = 0; i < n - 1; i++) {
		read(edges[i][0]), read(edges[i][1]), read(edges[i][2]);
		parent[i] = i;
	}
	parent[n - 1] = n - 1;
	parent[n] = n;
	for (int i = 0, u, v; i < q; i++) {
		read(u), read(v);
		query[u].insert(i);
		query[v].insert(i);
	}
	sort(edges, edges + n - 1, [&] (auto & e1, auto & e2) -> bool {
		return e1[2] > e2[2];
	});
	for (int i = 0, u, v, w; i < n - 1; i++) {
		u = find(edges[i][0]), v = find(edges[i][1]), w = edges[i][2];
		if (query[u].size() > query[v].size()) {
			swap(u, v);
		}
		for (int idx : query[u]) {
			if (query[v].count(idx)) {
				ans[idx] = w;
				query[v].erase(idx);
			} else {
				query[v].insert(idx);
			}
		}
		query[u].clear();
		parent[u] = v;
	}
	for (int i = 0; i < q; i++) {
		write(ans[i]);
	}
	return 0;
}