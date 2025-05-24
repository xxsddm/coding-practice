// https://atcoder.jp/contests/abc240/tasks/abc240_e

#include "vector"
#include "iostream"

using namespace std;

void dfs(int node, int prev, int start, vector<int> *next, int range[][2]) {
	range[node][0] = start;
	int minus = 0;	// 叶节点上界无需-1
	for (int &nextNode : next[node]) {
		if (nextNode == prev) {
			continue;
		}
		minus = 1;
		dfs(nextNode, node, start, next, range);
		start = range[nextNode][1] + 1;	// 下一个子节点起始范围为当前子节点上界+1
	}
	range[node][1] = start - minus;
}

int main() {
	int N;
	scanf("%d", &N);
	vector<int> next[N];
	int range[N][2];
	for (int i = 1; i < N; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		u--, v--;
		next[u].push_back(v);
		next[v].push_back(u);
	}
	dfs(0, -1, 1, next, range);
	for (int node = 0; node < N; node++) {
		printf("%d %d\n", range[node][0], range[node][1]);
	}
	return 0;
}
