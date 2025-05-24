// https://www.acwing.com/problem/content/description/1740/

#include "algorithm"
#include "cstring"
#include "iostream"

using namespace std;

int main() {	// 含环问题(环路间无交叉)
	int N, ans = 0;
	scanf("%d", &N);
	int nums[N], next[N], indegree[N];
	bool visited[N];
	memset(indegree, 0, sizeof(indegree));
	memset(visited, false, sizeof(visited));
	for (int i = 0; i < N; i++) {
		scanf("%d", &nums[i]);
	}
	sort(nums, nums + N);
	for (int node = 0; node < N; node++) {
		int nextNode = node - 1;
		if (nextNode < 0 || node + 1 < N && nums[node + 1] - nums[node] < nums[node] - nums[nextNode]) {
			nextNode = node + 1;
		}
		if (nextNode == node - 1) {
			while (nextNode - 1 >= 0 && nums[nextNode - 1] == nums[nextNode]) {
				nextNode--;
			}
		}
		next[node] = nextNode;
		indegree[nextNode]++;
	}
	for (int start = 0; start < N; start++) {	// 链表连向环路(起点入度为0, 可能多个链表连向某环路)
		if (indegree[start] == 0) {
			ans++;
			int node = start;
			while (!visited[node]) {
				visited[node] = true;
				node = next[node];
			}
		}
	}
	for (int node = 0; node < N; node++) {	// 单纯的环路
		if (!visited[node]) {
			ans++;
			int temp = node;
			while (!visited[temp]) {
				visited[temp] = true;
				temp = next[temp];
			}
		}
	}
	printf("%d", ans);
	return 0;
}
