// http://oj.daimayuan.top/course/15/problem/796

#include "vector"
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

unsigned int A, B, C;
inline unsigned int rng61() {
	A ^= A << 16;
	A ^= A >> 5;
	A ^= A << 1;
	unsigned int t = A;
	A = B;
	B = C;
	C ^= t ^ A;
	return C;
}

int length = 0, *path, *first, *depth, *lg2;
int **container;
vector<int> *adj;

void dfs(int node, int prevnode) {
	first[node] = length;
	path[length++] = node;
	depth[node] = depth[prevnode] + 1;
	for (int &nextnode : adj[node]) {
		if (nextnode == prevnode) {
			continue;
		}
		dfs(nextnode, node);
		path[length++] = node;
	}
}


int main() {
	int n, m;
	scanf("%d %d %u %u %u", &n, &m, &A, &B, &C);
	path = new int[n << 1];
	first = new int[n + 1], depth = new int[n + 1];
	adj = new vector<int>[n + 1];
	for (int i = 1, u, v; i < n; i++) {
		read(u), read(v);
		adj[u].push_back(v), adj[v].push_back(u);
	}
	depth[0] = -1;
	dfs(1, 0);
	int subLen = 1;
	lg2 = new int[(length >> 1) + 2];
	container = new int*[length];
	lg2[0] = 0;
	for (int i = 1, limit = (length >> 1) + 1; i <= limit; i++) {
		lg2[i] = lg2[i - 1] + (i == (1 << lg2[i - 1]));
	}
	for (int temp = 1, limit = length >> 1; temp <= limit; temp <<= 1) {
		subLen++;
	}
	for (int i = 0; i < length; i++) {
		container[i] = new int[subLen];
		container[i][0] = path[i];
	}
	for (int i = 1, half = 1; i < subLen; i++, half <<= 1) {
		for (int j = 0, limit = length + 1 - half * 2; j < limit; j++) {
			if (depth[container[j][i - 1]] < depth[container[j + half][i - 1]]) {
				container[j][i] = container[j][i - 1];
			} else {
				container[j][i] = container[j + half][i - 1];
			}
		}
	}
	long long ans = 0, lca;
	for (int i = 1, u, v, start, end, temp; i <= m; i++) {
		u = rng61() % n + 1, v = rng61() % n + 1;
		start = first[u], end = first[v];
		if (start > end) {
			swap(start, end);
		}
		temp = lg2[(end - start + 1) >> 1];
		if (depth[container[start][temp]] < depth[container[end - (1 << temp) + 1][temp]]) {
			lca = container[start][temp];
		} else {
			lca = container[end - (1 << temp) + 1][temp];
		}
		ans ^= lca * i;
	}
	printf("%lld", ans);
	return 0;
}