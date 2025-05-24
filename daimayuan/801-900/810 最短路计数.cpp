// http://oj.daimayuan.top/course/11/problem/810

#include "unordered_map"
#include "queue"
#include "cstring"
#include "iostream"

int mod = 100003, *steps, *counter;
std::unordered_map<long long, int> edges;

int main() {
	int N, M;
	scanf("%d %d", &N, &M);
	std::vector<std::pair<int, int>> next[N + 1];
	for (int i = 0, u, v; i < M; i++) {
		scanf("%d %d", &u, &v);
		if (u == v) {
			continue;
		}
		if (u > v) {
			std::swap(u, v);
		}
		edges[(long long) u * (N + 1) + v]++;
	}
	for (auto &[key, num] : edges) {
		int u = key / (N + 1), v = key % (N + 1);
		next[u].emplace_back(v, num);
		next[v].emplace_back(u, num);
	}
	steps = new int[N + 1];
	counter = new int[N + 1];
	memset(steps, 0x3f, sizeof(int) * (N + 1));
	counter[1] = 1;
	steps[1] = 0;
	std::queue<int> q;
	int count = 0;
	q.push(1);
	while (!q.empty()) {
		count++;
		for (int i = 0, node, size = (int) q.size(); i < size; i++) {
			node = q.front();
			q.pop();
			for (auto &[nextNode, num] : next[node]) {
				if (steps[nextNode] < count) {
					continue;
				}
				if (steps[nextNode] > count) {
					steps[nextNode] = count;
					counter[nextNode] = 0;
					q.push(nextNode);
				}
				counter[nextNode] += (counter[node] * num) % mod;
				if (counter[nextNode] >= mod) {
					counter[nextNode] -= mod;
				}
			}
		}
	}
	for (int i = 1; i <= N; i++) {
		if (steps[i] > mod) {
			printf("0\n");
		} else {
			printf("%d\n", counter[i]);
		}
	}
	return 0;
}
