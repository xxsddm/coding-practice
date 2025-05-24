// https://www.luogu.com.cn/problem/P3808

#include "cstring"
#include "queue"
#include "iostream"

using namespace std;

class ACautomaton {
private:
	struct Node {
		int count = 0, length = 0;
		Node *fail, *next[26];
		Node() {
			for (int i = 0; i < 26; i++) {
				next[i] = nullptr;
			}
		}
	};

	Node *root = new Node(), *dummyhead = new Node();

public:
	ACautomaton() {
		root->fail = dummyhead;
		for (int i = 0; i < 26; i++) {
			dummyhead->next[i] = root;
		}
	}

	void add(char *word, int *minLength) {
		int length = strlen(word);
		Node *node = root;
		for (int i = 0; i < length; i++) {
			int idx = word[i] - 'a';
			if (node->next[idx] == nullptr) {
				node->next[idx] = new Node();
				node->next[idx]->length = node->length + 1;
			}
			node = node->next[idx];
		}
		node->count++;
		int temp = word[length - 1] - 'a';
		if (minLength[temp] == -1 || minLength[temp] > length) {
			minLength[temp] = length;
		}
	}

	void preprocess() {     // BFS(按照字符串长度遍历, 计算fail)
		queue<Node*> q;
		q.push(root);
		while (!q.empty()) {
			Node *node = q.front(), *prevFail = node->fail;
			q.pop();
			for (int i = 0; i < 26; i++) {
				if (node->next[i] == nullptr) {
					node->next[i] = prevFail->next[i];
					continue;
				}
				node->next[i]->fail = prevFail->next[i];
				q.push(node->next[i]);
			}
		}
	}

	int calculate(char *word, int *minLength) {
		int ans = 0, length = strlen(word);
		Node *node = root;
		for (int i = 0; i < length; i++) {
			node = node->next[word[i] - 'a'];
			int minLen = minLength[word[i] - 'a'];
			if (minLen != -1) {
				Node *temp = node;  // 考虑新的字符时移动到新的节点
				while (temp->length >= minLen) {    // 该节点对应字符串的最长公共后缀字符串也可匹配
					ans += temp->count;
					temp->count = 0;
					temp = temp->fail;
				}
			}
		}
		return ans;
	}
};

int main() {
	int n, minLength[26];	// 记录各字母结尾的最短字符串长度, 减少不必要的查找
	char container[1000001];
	memset(minLength, -1, sizeof(minLength));
	ACautomaton ac;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%s", container);
		ac.add(container, minLength);
	}
	scanf("%s", container);
	ac.preprocess();
	printf("%d", ac.calculate(container, minLength));
	return 0;
}