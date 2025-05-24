// https://www.acwing.com/problem/content/117/

#include "cstring"
#include "queue"
#include "iostream"

using namespace std;

struct Node {
	int val, idx, prev = -1, size = 1;

	bool operator < (const Node& other) const {
		return val * other.size < other.val * size;
	}
};

int main() {
	int n, R, ans = 0, count = 1;
	scanf("%d %d", &n, &R);
	Node nodes[n];
	bool visited[n];
	priority_queue<Node> container;
	memset(visited, false, sizeof(visited));
	visited[--R] = true;
	for (int i = 0; i < n; i++) {
		nodes[i].idx = i;
		scanf("%d", &nodes[i].val);
		ans += nodes[i].val;	// 各节点开始时加一次, 后续则只需再考虑前驱节点包含节点数量
	}
	for (int i = 1; i < n; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		nodes[b - 1].prev = a - 1;
	}
	for (int i = 0; i < n; i++) {
		if (i != R) {
			container.push(nodes[i]);
		}
	}
	while (count < n) {
		Node node = container.top();
		container.pop();
		if (nodes[node.idx].size != node.size) {
			continue;
		}
		visited[node.idx] = true;
		count++;
		// 更新节点的父节点(怠惰更新)
		int prevIdx = nodes[node.idx].prev;
		while (prevIdx != R && visited[prevIdx]) {
			prevIdx = nodes[prevIdx].prev;
		}
		Node & prevNode = nodes[prevIdx];
		ans += node.val * prevNode.size;
		// 与前驱节点向前合并(子节点的父节点改为前驱节点, 后续再更新)
		prevNode.val += node.val;
		prevNode.size += node.size;
		if (!visited[prevIdx]) {
			container.push(prevNode);
		}
	}
	printf("%d", ans);
	return 0;
}