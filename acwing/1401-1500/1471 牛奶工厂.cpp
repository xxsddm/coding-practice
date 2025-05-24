// https://www.acwing.com/problem/content/1473/

#include "vector"
#include "queue"
#include "cstring"
#include "iostream"

using namespace std;

int main() {
	int N;
	scanf("%d", &N);
	int indegree[N + 1], counter[N + 1], ans = -1;
	vector<int> next[N + 1];
	queue<int> q;
	memset(indegree, 0, sizeof(indegree));
	memset(counter, 0, sizeof(counter));
	for (int i = 1; i < N; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		indegree[b]++;
		next[a].push_back(b);
	}
	for (int start = 1; start <= N; start++) {
		if (indegree[start] == 0) {
			q.push(start);
		}
	}
	while (!q.empty()) {
		int node = q.front();
		q.pop();
		counter[node]++;
		for (int &nextNode : next[node]) {
			counter[nextNode] += counter[node];
			if (--indegree[nextNode] == 0) {
				q.push(nextNode);
			}
		}
	}
	for (int node = 1; node <= N; node++) {
		if (counter[node] == N) {
			ans = node;
		}
	}
	printf("%d", ans);
	return 0;
}
