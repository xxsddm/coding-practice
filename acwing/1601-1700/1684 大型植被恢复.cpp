// https://www.acwing.com/problem/content/1686/

#include "cstring"
#include "vector"
#include "iostream"

using namespace std;

int main() {
	int N, M;
	scanf("%d %d", &N, &M);
	int ans[N];
	memset(ans, 0, sizeof(ans));
	vector<int> next[N];
	for (int i = 0; i < M; i++) {
		int node1, node2;
		scanf("%d %d", &node1, &node2);
		node1--, node2--;
		next[node1].push_back(node2);
		next[node2].push_back(node1);
	}
	for (int node = 0; node < N; node++) {
		// 检查之前已确认取值的相连节点, 选择最小的可行值
		int used = 0;
		for (int &nextNode : next[node]) {
			used |= 1 << ans[nextNode];
		}
		for (int num = 1, temp = 2; num <= 4; num++, temp <<= 1) {
			if (!(used & temp)) {
				ans[node] = num;
				break;
			}
		}
		printf("%d", ans[node]);
	}
	return 0;
}
