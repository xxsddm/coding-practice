// https://www.acwing.com/problem/content/144/

#include "iostream"

using namespace std;

struct Node {
	int num = 0;
	Node *next[26];

	Node() {
		for (int i = 0; i < 26; i++) {
			next[i] = nullptr;
		}
	}
};

int main() {
	int N, M;
	Node root;
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		string word;
		cin >> word;
		Node *node = &root;
		for (char &letter : word) {
			int idx = letter - 'a';
			if (node->next[idx] == nullptr) {
				node->next[idx] = new Node();
			}
			node = node->next[idx];
		}
		node->num++;
	}
	for (int i = 0; i < M; i++) {
		int ans = 0;
		string word;
		cin >> word;
		Node *node = &root;
		for (char &letter : word) {
			int idx = letter - 'a';
			if (node->next[idx] == nullptr) {
				break;
			}
			node = node->next[idx];
			ans += node->num;
		}
		printf("%d\n", ans);
	}
	return 0;
}
