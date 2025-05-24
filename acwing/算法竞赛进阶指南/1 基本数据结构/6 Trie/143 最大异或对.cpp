// https://www.acwing.com/problem/content/145/

#include "iostream"

using namespace std;

struct Node {
	Node *next[2];

	Node() {
		for (int i = 0; i < 2; i++) {
			next[i] = nullptr;
		}
	}
};

int main() {	// 从高位开始建Trie
	int N;
	Node root;
	scanf("%d", &N);
	int nums[N], ans = 0, maxnum = 0, count = 0;
	for (int i = 0; i < N; i++) {
		scanf("%d", &nums[i]);
		maxnum = max(maxnum, nums[i]);
	}
	for (int i = 0; i <= 30; i++) {
		if (maxnum < (1 << i)) {
			break;
		}
		count = i;
	}
	for (int &num : nums) {
		Node *node = &root;
		for (int temp = 1 << count; temp; temp >>= 1) {
			int idx = (num & temp) ? 1 : 0;
			if (node->next[idx] == nullptr) {
				node->next[idx] = new Node();
			}
			node = node->next[idx];
		}
		node = &root;
		int tempans = 0;
		for (int temp = 1 << count; temp; temp >>= 1) {
			int idx = (num & temp) ? 0 : 1;
			if (node->next[idx] == nullptr) {
				idx = 1 - idx;
			} else {
				tempans ^= temp;
			}
			node = node->next[idx];
		}
		ans = max(ans, tempans);
	}
	printf("%d", ans);
	return 0;
}
