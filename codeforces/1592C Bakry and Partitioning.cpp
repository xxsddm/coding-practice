// https://codeforces.com/problemset/problem/1592/C

#include "iostream"
#include "vector"

using namespace std;

int total = 0, counter = 0;

int dfs(int node, int prevNode, int source, int *value, vector<int> *next) {
    if (counter >= 2) {
        return 0;
    }
    int cur = value[node];
    for (auto &nextNode: next[node]) {
        if (nextNode != prevNode) {
            cur ^= dfs(nextNode, node, source, value, next);
            if (counter >= 2) {
                break;
            }
        }
    }
    if (cur == total && node != source) {
        counter++;
        return 0;   // 不影响连接该子树的树取total(否则会由于与其xor得到0)
    }
    return cur;
}

int main() {
    // n个节点,n-1条边正好生成MST
    // 移除一条边则移除一个子树
    int T;
    cin >> T;
    for (int t = 0; t < T; t++) {
        int n, k;
        cin >> n >> k;
        int value[n + 1];
        total = 0, counter = 0;
        for (int i = 1; i <= n; i++) {
            cin >> value[i];
            total ^= value[i];
        }
        bool skip = total == 0 || k <= 2;
        vector<int> next[n + 1];
        for (int i = 0; i < n - 1; i++) {
            int node1, node2;
            cin >> node1 >> node2;
            if (skip) {
                continue;
            }
            next[node1].push_back(node2);
            next[node2].push_back(node1);
        }
        if (total == 0) {
            cout << "YES" << endl;
            continue;
        } else if (k <= 2) {
            cout << "NO" << endl;
            continue;
        }
        dfs(1, -1, 1, value, next);
        cout << (counter >= 2 ? "YES" : "NO") << endl;
    }
    return 0;
}
