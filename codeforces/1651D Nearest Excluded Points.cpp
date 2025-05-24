// https://codeforces.com/problemset/problem/1651/D

#include "set"
#include "map"
#include "queue"
#include "iostream"

using namespace std;

int main() {	// BFS
	int n, count = 0, numVisited = 0, dir[5] { -1, 0, 1, 0, -1};
	scanf("%d", &n);
	pair<int, int> ans[n];
	queue<array<int, 4>> q;
	set<pair<int, int>> avail;
	map<pair<int, int>, int> point2idx;
	for (int i = 0; i < n; i++) {
		pair<int, int> p;
		scanf("%d %d", &p.first, &p.second);
		point2idx[p] = i;
		for (int j = 0; j < 4; j++) {
			avail.insert({p.first + dir[j], p.second + dir[j + 1]});
		}
	}
	for (auto &[k, v] : point2idx) {
		avail.erase(k);
	}
	for (auto block : avail) {
		q.push({block.first, block.second, block.first, block.second});
	}
	while (!q.empty() && numVisited < n) {
		count++;
		for (int i = 0, size = (int) q.size(); i < size; i++) {
			auto [x, y, startX, startY] = q.front();
			q.pop();
			for (int j = 0; j < 4; j++) {
				int nextX = x + dir[j], nextY = y + dir[j + 1];
				pair<int, int> nextNode = {nextX, nextY};
				if (!point2idx.count(nextNode)) {
					continue;
				}
				numVisited++;
				ans[point2idx[nextNode]] = {startX, startY};
				q.push({nextX, nextY, startX, startY});
				point2idx.erase(nextNode);
			}
		}
	}
	for (int i = 0; i < n; i++) {
		printf("%d %d\n", ans[i].first, ans[i].second);
	}
	return 0;
}
