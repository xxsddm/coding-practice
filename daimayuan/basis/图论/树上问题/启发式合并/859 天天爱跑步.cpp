// http://oj.daimayuan.top/course/15/problem/859

#include <vector>
#include <cstring>
#include <iostream>

using std::swap;
using std::pair;
using std::vector;

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
	putchar(' ');
}

struct Node {
	int depth, count = 0, ans, w, pre, hson, size, *anc;
	vector<int> next;
	vector<pair<int, int>> log1, log2;
} *nodes;

int n, *lg2, *counter1, *counter2;

int dfs1(int cur, int pre) {
	Node &node = nodes[cur], &prevnode = nodes[pre];
	node.pre = pre;
	node.depth = prevnode.depth + 1;
	node.size = 1;
	node.hson = 0;
	int length = lg2[node.depth], tempsize = 0, maxsize = 0;
	if (length) {
		node.anc = new int[length];
		node.anc[0] = pre;
		for (int i = 1; i < length; i++) {
			node.anc[i] = nodes[node.anc[i - 1]].anc[i - 1];
		}
	}
	for (int &next : node.next) {
		if (next == pre) {
			continue;
		}
		tempsize = dfs1(next, cur);
		node.size += tempsize;
		if (tempsize > maxsize) {
			maxsize = tempsize;
			node.hson = next;
		}
	}
	return node.size;
}

void add(int cur, int pre) {
	Node &node = nodes[cur];
	for (auto &p : node.log1) {
		counter1[p.first] += p.second;
	}
	for (auto &p : node.log2) {
		counter2[p.first] += p.second;
	}
	for (int &next : node.next) {
		if (next != pre) {
			add(next, cur);
		}
	}
}

void remove(int cur, int pre) {
	Node &node = nodes[cur];
	for (auto &p : node.log1) {
		counter1[p.first] -= p.second;
	}
	for (auto &p : node.log2) {
		counter2[p.first] -= p.second;
	}
	for (int &next : node.next) {
		if (next != pre) {
			remove(next, cur);
		}
	}
}

void dfs2(int cur, int pre, bool keep) {
	Node &node = nodes[cur];
	for (int &next : node.next) {
		if (next == node.hson || next == pre) {
			continue;
		}
		dfs2(next, cur, false);
	}
	if (node.hson) {
		dfs2(node.hson, cur, true);
	}
	for (int &next : node.next) {
		if (next == node.hson || next == pre) {
			continue;
		}
		add(next, cur);
	}
	for (auto &p : node.log1) {
		counter1[p.first] += p.second;
	}
	for (auto &p : node.log2) {
		counter2[p.first] += p.second;
	}
	node.ans = counter1[node.w + node.depth] + counter2[node.w - node.depth + n];
	if (!keep) {
		remove(cur, pre);
	}
}

int lca(int u, int v) {
	if (nodes[u].depth < nodes[v].depth) {
		swap(u, v);
	}
	while (nodes[u].depth > nodes[v].depth) {
		u = nodes[u].anc[lg2[nodes[u].depth - nodes[v].depth] - 1];
	}
	if (u == v) {
		return u;
	}
	for (int i = lg2[nodes[u].depth] - 1; i >= 0; i--) {
		if (i < lg2[nodes[u].depth] && nodes[u].anc[i] != nodes[v].anc[i]) {
			u = nodes[u].anc[i], v = nodes[v].anc[i];
		}
	}
	return nodes[u].anc[0];
}

int main() {	// dfs2枚举当前点作为路径中的点出现次数, 计算后非重子节点清除信息
	int m;
	read(n), read(m);
	// counter1, counter2分别记录向上, 下移动信息
	counter1 = new int[n << 1], counter2 = new int[n << 1], lg2 = new int[n + 1];
	nodes = new Node[n + 1];
	for (int i = 1, u, v; i < n; i++) {
		read(u), read(v);
		nodes[u].next.push_back(v);
		nodes[v].next.push_back(u);
	}
	for (int i = 1; i <= n; i++) {
		read(nodes[i].w);
	}
	lg2[0] = 0;
	for (int i = 1; i <= n; i++) {
		lg2[i] = lg2[i - 1] + (i == (1 << lg2[i - 1]));
	}
	nodes[0].depth = -1;
	dfs1(1, 0);
	for (int i = 0, s, t, mid; i < m; i++) {
		read(s), read(t);
		mid = lca(s, t);
		// 移项使与dfs2中枚举的点无关, 路径中任意节点均适用
		if (mid == t) {
			nodes[s].log1.emplace_back(nodes[s].depth, 1);
			nodes[nodes[mid].pre].log1.emplace_back(nodes[s].depth, -1);
		} else if (mid == s) {
			nodes[t].log2.emplace_back(- nodes[mid].depth + n, 1);
			nodes[nodes[mid].pre].log2.emplace_back(- nodes[mid].depth + n, -1);
		} else {
			nodes[s].log1.emplace_back(nodes[s].depth, 1);
			nodes[t].log2.emplace_back(nodes[s].depth - nodes[mid].depth * 2 + n, 1);
			nodes[nodes[mid].pre].log1.emplace_back(nodes[s].depth, -1);
			nodes[mid].log2.emplace_back(nodes[s].depth - nodes[mid].depth * 2 + n, -1);
		}
	}
	memset(counter1, 0, sizeof(int) * (n << 1));
	memset(counter2, 0, sizeof(int) * (n << 1));
	dfs2(1, 0, true);
	for (int i = 1; i <= n; i++) {
		write(nodes[i].ans);
	}
	return 0;
}