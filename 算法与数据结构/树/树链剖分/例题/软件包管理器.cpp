// http://oj.daimayuan.top/course/15/problem/840

#include <vector>
#include <cstring>
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

int n, root = 0, idx = 1, *node2idx, *pre, *top, *hson, *size;
int *counter, *lazy;
std::vector<int> *adj;

int dfs1(int node) {
	size[node] = 1;
	hson[node] = -1;
	int maxsize = 0;
	for (int &nextnode : adj[node]) {
		int temp = dfs1(nextnode);
		size[node] += temp;
		if (temp > maxsize) {
			maxsize = temp;
			hson[node] = nextnode;
		}
	}
	return size[node];
}

void dfs2(int node) {
	node2idx[node] = idx++;
	if (hson[node] != -1) {
		top[hson[node]] = top[node];
		dfs2(hson[node]);
		for (int &nextnode : adj[node]) {
			if (nextnode != hson[node]) {
				top[nextnode] = nextnode;
				dfs2(nextnode);
			}
		}
	}
}

int change(int cur, int start, int end, int left, int right, bool install) {
	int ans;
	if (left <= start && right >= end) {
		if (install) {
			ans = end - start + 1 - counter[cur];
			counter[cur] = end - start + 1;
			lazy[cur] = 1;
		} else {
			ans = counter[cur];
			counter[cur] = 0;
			lazy[cur] = -1;
		}
		return ans;
	}
	int mid = (start + end) >> 1, next1 = cur << 1, next2 = next1 ^ 1;
	if (lazy[cur] == 1) {
		lazy[cur] = 0;
		lazy[next1] = lazy[next2] = 1;
		counter[next1] = mid - start + 1;
		counter[next2] = end - mid;
	} else if (lazy[cur] == -1) {
		lazy[cur] = 0;
		lazy[next1] = lazy[next2] = -1;
		counter[next1] = counter[next2] = 0;
	}
	if (right <= mid) {
		ans = change(next1, start, mid, left, right, install);
	} else if (left > mid) {
		ans = change(next2, mid + 1, end, left, right, install);
	} else {
		ans = change(next1, start, mid, left, right, install)
		      + change(next2, mid + 1, end, left, right, install);
	}
	counter[cur] = counter[next1] + counter[next2];
	return ans;
}

inline int install(int node) {	// 安装时节点到根节点状态改变
	int ans = 0;
	while (top[node] != root) {
		ans += change(1, 1, n, node2idx[top[node]], node2idx[node], true);
		node = pre[top[node]];
	}
	ans += change(1, 1, n, node2idx[root], node2idx[node], true);
	return ans;
}

inline int uninstall(int node) {	// 卸载时节点的子树状态改变
	return change(1, 1, n, node2idx[node], node2idx[node] + size[node] - 1, false);
}

int main() {
	int q;
	read(n);
	node2idx = new int[n], pre = new int[n];
	top = new int[n], hson = new int[n], size = new int[n];
	counter = new int[n << 2], lazy = new int[n << 2];
	adj = new std::vector<int>[n + 1];
	for (int i = 1, j; i < n; i++) {
		read(j);
		adj[j].push_back(i);
		pre[i] = j;
	}
	top[root] = root;
	dfs1(root);
	dfs2(root);
	memset(counter, 0, sizeof(int) * (n << 2));
	memset(lazy, 0, sizeof(int) * (n << 2));
	read(q);
	char command[10];
	for (int i = 0, x; i < q; i++) {
		scanf("%s", command);
		read(x);
		if (command[0] == 'i') {
			write(install(x));
		} else {
			write(uninstall(x));
		}
	}
	return 0;
}