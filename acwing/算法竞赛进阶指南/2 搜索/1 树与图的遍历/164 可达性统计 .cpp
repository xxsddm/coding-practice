// https://www.acwing.com/problem/content/166/

#include "bitset"
#include "queue"
#include "cstring"
#include "iostream"

using namespace std;

int main() {	// BFS
	const int n = 30000;
	int N, M;
	scanf("%d %d", &N, &M);
	int outdegree[N];
	bitset<n> counter[N];	// n位01哈希
	vector<int> prev[N];
	memset(outdegree, 0, sizeof(outdegree));
	for (int i = 0; i < M; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		x--, y--;
		outdegree[x]++;
		prev[y].push_back(x);
	}
	queue<int> q;
	for (int i = 0; i < N; i++) {
		if (outdegree[i] == 0) {
			q.push(i);
		}
	}
	while (!q.empty()) {
		int node = q.front();
		q.pop();
		counter[node].set(node, 1);
		for (int &prevNode : prev[node]) {
			counter[prevNode] |= counter[node];
			if (--outdegree[prevNode] == 0) {
				q.push(prevNode);
			}
		}
	}
	for (int i = 0; i < N; i++) {
		printf("%d\n", (int) counter[i].count());
	}
	return 0;
}
