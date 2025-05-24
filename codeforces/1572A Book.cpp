// https://codeforces.com/problemset/problem/1572/A

#include "iostream"
#include "vector"
#include "cstring"
#include "queue"
#include "algorithm"

using namespace std;

int n, ans;

bool dfs(int node, int *status, vector<int> *adj) { // 检查环路
    status[node] = 1;
    for (int &nextNode: adj[node]) {
        if (status[nextNode] == 1 || status[nextNode] == 0 && !dfs(nextNode, status, adj)) {
            return false;
        }
    }
    status[node] = 2;
    return true;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        ans = 0;
        int status[n + 1], indegree[n + 1];
        vector<int> adj[n + 1];
        priority_queue<int, vector<int>, greater<>> container;
        memset(status, 0, sizeof(status));
        memset(indegree, 0, sizeof(indegree));
        for (int i = 1; i <= n; i++) {
            int numPrev;
            cin >> numPrev;
            indegree[i] = numPrev;
            for (int j = 0; j < numPrev; j++) {
                int nextNode;
                cin >> nextNode;
                adj[nextNode].push_back(i);
            }
            if (numPrev == 0) {
                container.push(i);
            }
        }
        if (container.empty()) {
            cout << -1 << endl;
            continue;
        }
        for (int i = 1; i <= n; i++) {
            if (status[i] == 0 && !dfs(i, status, adj)) {
                ans = -1;
                break;
            }
        }
        if (ans == -1) {
            cout << ans << endl;
            continue;
        }
        while (!container.empty()) {
            ans++;
            deque<int> q;
            while (!container.empty()) {
                int node = container.top();
                container.pop();
                for (int &nextNode: adj[node]) {
                    if (--indegree[nextNode] == 0) {
                        if (nextNode > node) {  // 较大节点本轮遍历
                            container.push(nextNode);
                        } else {                // 较小节点下轮遍历
                            q.push_front(nextNode);
                        }
                    }
                }
            }
            for (int &nextNode: q) {
                container.push(nextNode);
            }
        }
        cout << ans << endl;
    }
}
