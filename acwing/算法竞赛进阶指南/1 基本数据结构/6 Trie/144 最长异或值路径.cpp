// https://www.acwing.com/problem/content/146/

#include "vector"
#include "iostream"

using namespace std;

struct Node {
	Node *next[2];
	Node() {
		next[0] = nullptr;
		next[1] = nullptr;
	}
} root;

int count = 30;

void dfs(int node, int prevNode, int *nums, vector<pair<int, int>> *next) {
	for (auto & p : next[node]) {
		if (p.first == prevNode) {
			continue;
		}
		int nextNode = p.first, nextVal = nums[node] ^ p.second;
		nums[nextNode] = nextVal;
		dfs(nextNode, node, nums, next);
	}
}

void add(int &num) {
	Node *node = &root;
	for (int temp = 1 << count; temp; temp >>= 1) {
		int idx = (temp & num) ? 1 : 0;
		if (node->next[idx] == nullptr) {
			node->next[idx] = new Node();
		}
		node = node->next[idx];
	}
}

int main() {
	int n;
	scanf("%d", &n);
	int nums[n], maxnum = 0, ans = 0;
	vector<pair<int, int>> next[n];
	for (int i = 0; i < n; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		next[u].emplace_back(v, w);
		next[v].emplace_back(u, w);
	}
	nums[0] = 0;	// 选0为树的根节点(不一定属于最优路径)
	dfs(0, -1, nums, next);
	for (int &num : nums) {
		maxnum = max(maxnum, num);
	}
	for (int i = 1, temp = 2; i <= 30; i++, temp <<= 1) {
		if (temp > maxnum) {
			count = i - 1;
			break;
		}
	}
	add(nums[0]);
	for (int i = 1; i < n; i++) {
		int tempans = 0, &num = nums[i];
		Node *node = &root;
		for (int temp = 1 << count; temp; temp >>= 1) {
			int idx = (temp & num) ? 0 : 1;	// 优先使高位异或值为1
			if (node->next[idx] == nullptr) {
				idx = 1 - idx;
			} else {
				tempans ^= temp;
			}
			node = node->next[idx];
		}
		ans = max(ans, tempans);
		add(nums[i]);
	}
	printf("%d", ans);
	return 0;
}
