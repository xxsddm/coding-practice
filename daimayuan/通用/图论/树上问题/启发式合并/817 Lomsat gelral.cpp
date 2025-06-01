// http://oj.daimayuan.top/course/15/problem/817

#include "vector"
#include "iostream"

typedef long long ll;

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

int total = 0, maxcount = 0, *size, *hson, *node2idx, *idx2node, *nums, *counter;
ll *cumsum, *ans;
std::vector<int> *adj;

int dfs1(int node, int prevnode) {
	node2idx[node] = total;
	idx2node[total++] = node;
	size[node] = 1;
	hson[node] = 0;
	int maxsize = 0;
	for (int &nextnode : adj[node]) {
		if (nextnode == prevnode) {
			continue;
		}
		int temp = dfs1(nextnode, node);
		size[node] += temp;
		if (temp > maxsize) {
			maxsize = temp;
			hson[node] = nextnode;
		}
	}
	return size[node];
}

void add(int node) {
	for (int i = node2idx[node], limit = i + size[node], nextnode, temp; i < limit; i++) {
		nextnode = idx2node[i];
		temp = ++counter[nums[nextnode]];
		cumsum[temp - 1] -= nums[nextnode];
		cumsum[temp] += nums[nextnode];
		maxcount = std::max(maxcount, temp);
	}
}

void del(int node) {
	for (int i = node2idx[node], limit = i + size[node], nextnode, temp; i < limit; i++) {
		nextnode = idx2node[i];
		temp = --counter[nums[nextnode]];
		cumsum[temp + 1] -= nums[nextnode];
		cumsum[temp] += nums[nextnode];
		if (cumsum[maxcount] == 0) {
			maxcount--;
		}
	}
}

void dfs2(int node, int prevnode, bool heavy) {
	for (int &nextnode : adj[node]) {
		if (nextnode != hson[node] && nextnode != prevnode) {
			dfs2(nextnode, node, false);
		}
	}
	if (hson[node]) {
		dfs2(hson[node], node, true);
	}
	for (int &nextnode : adj[node]) {
		if (nextnode != hson[node] && nextnode != prevnode) {
			add(nextnode);
		}
	}
	int temp = ++counter[nums[node]];
	cumsum[temp - 1] -= nums[node];
	cumsum[temp] += nums[node];
	maxcount = std::max(maxcount, temp);
	ans[node] = cumsum[maxcount];
	if (!heavy) {
		del(node);
	}
}

int main() {
	int n;
	read(n);
	size = new int[n + 1], hson = new int[n + 1];
	node2idx = new int[n + 1], idx2node = new int[n];
	nums = new int[n + 1], counter = new int[n + 1];
	adj = new std::vector<int>[n + 1];
	cumsum = new ll[n + 1], ans = new ll[n + 1];
	for (int i = 1; i <= n; i++) {
		read(nums[i]);
		counter[i] = 0;
		cumsum[i] = 0;
	}
	for (int i = 1, x, y; i < n; i++) {
		read(x), read(y);
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	dfs1(1, 0);
	dfs2(1, 0, true);
	for (int i = 1; i <= n; i++) {
		write(ans[i]);
	}
	return 0;
}