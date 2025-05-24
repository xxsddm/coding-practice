// https://www.acwing.com/problem/content/113/

#include "queue"
#include "algorithm"
#include "iostream"

using namespace std;

struct Node {
	int left, right, idx;
	bool operator < (Node &other) {
		return left < other.left;
	}
};

int main() {
	int N;
	scanf("%d", &N);
	int ans[N];
	Node container[N];
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &container[i].left, &container[i].right);
		container[i].idx = i;
	}
	sort(container, container + N);
	// 优先使用上轮结束时间最小的栏位, 和起始时间最小的节点
	for (int i = 0; i < N; i++) {
		int left = container[i].left, right = container[i].right, idx = container[i].idx, temp;
		if (!pq.empty() && left > pq.top().first) {
			temp = pq.top().second;
			pq.pop();
		} else {
			temp = (int) pq.size() + 1;
		}
		pq.emplace(right, temp);
		ans[idx] = temp;
	}
	printf("%d\n", (int) pq.size());
	for (int &idx : ans) {
		printf("%d\n", idx);
	}
	return 0;
}
