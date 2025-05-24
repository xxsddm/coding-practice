// https://www.luogu.com.cn/problem/P3796

#include "queue"
#include "cstring"
#include "iostream"

using namespace std;

struct Node {
	int count = 0, idx = -1, length = 0;
	Node *fail, *next[26];
	Node() {
		for (int i = 0; i < 26; i++) {
			next[i] = nullptr;
		}
	}
};

Node *root, *dummyhead;

void add(char *word, int newIdx, int *minLength) {
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
	node->idx = newIdx;
	int temp = word[length - 1] - 'a';
	if (minLength[temp] == -1 || minLength[temp] > length) {
		minLength[temp] = length;
	}
}

void preprocess() {     // BFS(按照字符串长度遍历)
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

void calculate(string &word, int *counter, int *minLength) {
	int length = (int) word.size();
	Node *node = root;
	for (int i = 0; i < length; i++) {
		int idx = word[i] - 'a', minLen = minLength[idx];
		node = node->next[idx];
		if (minLen == -1) {
			continue;
		}
		Node *temp = node;	// 考虑新的字符时移动到新的节点
		while (temp->length >= minLen) {// 该节点对应字符串的最长公共后缀字符串也可匹配
			counter[temp->idx] += temp->count;
			temp = temp->fail;
		}
	}
}

int main() {
	int n;
	while (cin >> n && n) {
		int maxnum = -1, counter[n], minLength[26];	// 记录各字母结尾的最短字符串长度, 减少不必要的查找
		memset(counter, 0, sizeof(counter));
		memset(minLength, -1, sizeof(minLength));
		char words[n][71];
		root = new Node(), dummyhead = new Node();
		root->fail = dummyhead;
		for (int i = 0; i < 26; i++) {
			dummyhead->next[i] = root;
		}
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%s", words[i]);
			add(words[i], i, minLength);
		}
		string word;
		cin >> word;
		preprocess();
		calculate(word, counter, minLength);
		for (int &num : counter) {
			maxnum = max(maxnum, num);
		}
		printf("%d\n", maxnum);
		for (int i = 0; i < n; i++) {
			if (counter[i] == maxnum) {
				printf("%s\n", words[i]);
			}
		}
	}
	return 0;
}
