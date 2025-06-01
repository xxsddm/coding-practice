// http://oj.daimayuan.top/course/15/problem/688

#include "array"
#include "algorithm"
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

// 维护各区间长度, 区间最小覆盖次数及最小覆盖次数对应区间长度
struct Node {
	int minnum = 0, count, lazy;
} *nodes;

void build(int cur, int start, int end, int idx, int size) {
	if (idx < start || idx > end) {
		return;
	}
	nodes[cur].lazy = 0;
	if (start == end) {
		nodes[cur].count = size;
		return;
	}
	int mid = (start + end) >> 1;
	int next1 = cur << 1, next2 = next1 ^ 1;
	build(next1, start, mid, idx, size);
	build(next2, mid + 1, end, idx, size);
	nodes[cur].count = nodes[next1].count + nodes[next2].count;
}

void change(int cur, int start, int end, int left, int right, int delta) {
	if (right < start || left > end) {
		return;
	}
	if (left <= start && right >= end) {
		nodes[cur].lazy += delta;
		nodes[cur].minnum += delta;
		return;
	}
	int mid = (start + end) >> 1;
	int next1 = cur << 1, next2 = next1 ^ 1;
	if (nodes[cur].lazy) {
		int temp = nodes[cur].lazy;
		nodes[cur].lazy = 0;
		nodes[next1].lazy += temp, nodes[next1].minnum += temp;
		nodes[next2].lazy += temp, nodes[next2].minnum += temp;
	}
	change(next1, start, mid, left, right, delta);
	change(next2, mid + 1, end, left, right, delta);
	nodes[cur].minnum = std::min(nodes[next1].minnum, nodes[next2].minnum);
	nodes[cur].count = 0;
	if (nodes[cur].minnum == nodes[next1].minnum) {
		nodes[cur].count += nodes[next1].count;
	}
	if (nodes[cur].minnum == nodes[next2].minnum) {
		nodes[cur].count += nodes[next2].count;
	}
}

int *xs;
std::array<int, 4> *container;

int main() {
	int n;
	read(n);
	xs = new int[n << 1];
	container = new std::array<int, 4>[n << 1];
	int total = 0;
	for (int i = 0, x1, x2, y1, y2; i < n; i++) {
		read(x1), read(x2), read(y1), read(y2);
		if (x1 == x2 || y1 == y2) {
			continue;
		}
		xs[total] = x1;
		container[total++] = {y1, x1, x2, 1};
		xs[total] = x2;
		container[total++] = {y2, x1, x2, -1};
	}
	std::sort(xs, xs + total);
	std::sort(container, container + total);
	int length = (int) (std::unique(xs, xs + total) - xs) - 1;
	nodes = new Node[length << 2];
	for (int i = 1; i <= length; i++) {
		build(1, 1, length, i, xs[i] - xs[i - 1]);
	}
	long long ans = 0;
	for (int i = 0, prevy = 0, prevsize = 0, range = xs[length] - xs[0]; i < total;) {
		int cury = container[i][0], start, end;
		while (i < total && container[i][0] == cury) {
			start = std::upper_bound(xs, xs + length, container[i][1]) - xs;
			end = std::lower_bound(xs, xs + length, container[i][2]) - xs;
			change(1, 1, length, start, end, container[i][3]);
			i++;
		}
		ans += (long long) prevsize * (cury - prevy);
		prevsize = range;
		if (nodes[1].minnum == 0) {
			prevsize -= nodes[1].count;
		}
		prevy = cury;
	}
	printf("%lld", ans);
	return 0;
}
