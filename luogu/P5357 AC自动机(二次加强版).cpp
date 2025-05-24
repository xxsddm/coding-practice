// https://www.luogu.com.cn/problem/P5357

#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

const int LEN = 2000001, TOTAL = 26, BASE = 'a';

struct Node {
    int count = 0, indegree = 0;
    std::vector<int> container;
    Node *fail = nullptr, **next;
    Node() {
        next = (Node **)malloc(sizeof(Node *) * TOTAL);
        memset(next, 0, sizeof(Node *) * TOTAL);
    }
} *root = new Node(), *root_d = new Node();

char word[LEN];
int *counter;
std::vector<Node *> container;

void add(int idx) {
    Node *node = root;
    for (int i = 0, j, length = (int)strlen(word); i < length; i++) {
        j = word[i] - BASE;
        if (node->next[j] == nullptr) {
            node->next[j] = new Node();
            container.push_back(node->next[j]);
        }
        node = node->next[j];
    }
    node->container.push_back(idx);
}

void bfs() {  // 按照字符串长度遍历, 计算fail, 则fail相应长度小于当前节点
    root->fail = root_d;
    for (int i = 0; i < TOTAL; i++) {
        root_d->next[i] = root;
    }
    std::queue<Node *> q;
    q.push(root);
    while (!q.empty()) {
        Node *node = q.front(), *curFail = node->fail;
        q.pop();
        for (int i = 0; i < TOTAL; i++) {  // 计算当前节点相应字符串的最长公共后缀字符串相应节点
            if (node->next[i] == nullptr) {
                node->next[i] = curFail->next[i];
            } else {
                node->next[i]->fail = curFail->next[i];
                q.push(node->next[i]);
            }
        }
    }
}

void count() {  // BFS(利用拓扑关系计算各字符串出现次数)
    Node *temp = root;
    for (int i = 0, j, length = (int)strlen(word); i < length; i++) {
        j = word[i] - BASE;
        temp = temp->next[j];
        temp->count++;
    }
    for (auto &node : container) {
        node->fail->indegree++;
    }
    std::queue<Node *> q;
    for (auto &node : container) {
        if (node->indegree == 0) {
            q.push(node);
        }
    }
    while (!q.empty()) {
        Node *node = q.front();
        q.pop();
        for (int &idx : node->container) {
            counter[idx] = node->count;
        }
        node->fail->count += node->count;
        if (--node->fail->indegree == 0) {
            q.push(node->fail);
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    counter = new int[T];
    for (int t = 0; t < T; t++) {
        scanf("%s", word);
        add(t);
    }
    scanf("%s", word);
    bfs();
    count();
    for (int t = 0; t < T; t++) {
        printf("%d\n", counter[t]);
    }
    return 0;
}
