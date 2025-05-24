// https://www.acwing.com/problem/content/4077/

#include "iostream"
#include "cstring"
#include "vector"
#include "queue"

using namespace std;

int main() {    // BFS
    int numCity, numRoad;
    cin >> numCity >> numRoad;
    int container[numCity][numCity];
    vector<int> paths[numCity];
    memset(container, 0, sizeof(container));
    for (int i = 0; i < numRoad; i++) {
        int node1, node2;
        cin >> node1 >> node2;
        container[node1 - 1][node2 - 1] = 1;
        container[node2 - 1][node1 - 1] = 1;
    }
    // 若有铁路直达,container转换为公路
    int judge = 1 - container[0][numCity - 1], ans = 0;
    bool visited[numCity];
    memset(visited, false, sizeof(visited));
    queue<int> nodes;
    for (int i = 0; i < numCity - 1; i++) {
        for (int j = i + 1; j < numCity; j++) {
            if (container[i][j] == judge) {
                paths[i].push_back(j);
                paths[j].push_back(i);
            }
        }
    }
    nodes.push(0);
    visited[0] = true;
    while (!nodes.empty()) {
        ans++;
        int size = (int) nodes.size();
        for (int i = 0; i < size; i++) {
            int node = nodes.front();
            nodes.pop();
            for (int nextNode: paths[node]) {
                if (nextNode == numCity - 1) {
                    cout << ans;
                    return 0;
                }
                if (!visited[nextNode]) {
                    nodes.push(nextNode);
                    visited[nextNode] = true;
                }
            }
        }
    }
    cout << -1;
}
