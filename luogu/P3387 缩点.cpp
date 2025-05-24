// https://www.luogu.com.cn/problem/P3387

#include "unordered_set"
#include "queue"
#include "vector"
#include "cstring"
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

int length, *nums, *node2block, *topo, *counter, *indegree;
vector<int> *adj1, *adj2, *adj3;
unordered_set<int> memo;

void dfs1(int node) {
	node2block[node] = -1;
	for (int &nextnode : adj2[node]) {
		if (node2block[nextnode] == 0) {
			dfs1(nextnode);
		}
	}
	topo[length--] = node;
}

void dfs2(int node) {
	node2block[node] = length;
	for (int &nextnode : adj1[node]) {
		if (node2block[nextnode] == -1) {
			dfs2(nextnode);
		}
	}
}

int bfs(int start) {
	queue<int> q;
	int ans = 0;
	q.push(start);
	node2block[start] = counter[start];
	while (!q.empty()) {
		int idx = q.front(), cumsum = node2block[idx];
		ans = max(ans, cumsum);
		q.pop();
		for (int &nextidx : adj3[idx]) {
			int temp = cumsum + counter[nextidx];
			if (node2block[nextidx] < temp) {
				node2block[nextidx] = temp;
				q.push(nextidx);
			}
		}
	}
	return ans;
}

int main() {
	int n, m;
	read(n), read(m);
	length = n - 1;
	nums = new int[n + 1], node2block = new int[n + 1], topo = new int[n];
	memset(node2block + 1, 0 , sizeof(int) * n);
	adj1 = new vector<int>[n + 1];
	adj2 = new vector<int>[n + 1];
	for (int i = 1; i <= n; i++) {
		read(nums[i]);
	}
	for (int i = 0, u, v; i < m; i++) {
		read(u), read(v);
		adj1[u].push_back(v);
		adj2[v].push_back(u);
	}
	for (int i = 1; i <= n; i++) {
		if (node2block[i] == 0) {
			dfs1(i);
		}
	}
	for (int i = 0; i < n; i++) {
		if (node2block[topo[i]] == -1) {
			length++;
			dfs2(topo[i]);
		}
	}
	length++;
	counter = new int[length], indegree = new int[length];
	adj3 = new vector<int>[length];
	memset(counter, 0, sizeof(int) * length);
	memset(indegree, 0, sizeof(int) * length);
	for (int node = 1; node <= n; node++) {
		counter[node2block[node]] += nums[node];
		int idx1 = node2block[node];
		for (int &nextnode : adj1[node]) {
			int idx2 = node2block[nextnode];
			if (idx1 == idx2) {
				continue;
			}
			int key = idx1 * (length + 1) + idx2;
			if (!memo.count(key)) {
				adj3[idx1].push_back(idx2);
				indegree[idx2]++;
			}
		}
	}
	int ans = 0;
	memset(node2block, 0, sizeof(int) * (length));
	for (int i = 0; i < length; i++) {
		if (indegree[i] == 0) {
			ans = max(ans, bfs(i));
		}
	}
	printf("%d", ans);
	return 0;
}