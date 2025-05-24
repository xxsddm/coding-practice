// https://www.acwing.com/problem/content/4199/

#include "iostream"
#include "cstring"
#include "vector"
#include "queue"
#include "stack"

using namespace std;

struct edge {
    int to, weight;
    edge(int v, int w): to(v), weight(w) {}
    bool operator > (edge &other) const {
        return weight > other.weight;
    }
};

int main() {    // dijkstra
    int n, m;
    cin >> n >> m;
    int prev[n + 1], dist[n + 1];
    bool visited[n + 1];
    vector<edge> next[n + 1];
    memset(prev, -1, sizeof(prev));
    memset(dist, -1, sizeof(dist));
    memset(visited, false, sizeof(visited));
    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        next[a].emplace_back(b, w);
        next[b].emplace_back(a, w);
    }
    priority_queue<edge, vector<edge>, greater<>> pq;
    pq.push({1, 0});
    while (!pq.empty()) {
        int node = pq.top().to;
        pq.pop();
        if (visited[node]) {
            continue;
        }
        visited[node] = true;
        if (node == n) {
            break;
        }
        for (edge &nextEdge: next[node]) {
            if (visited[nextEdge.to]) {
                continue;
            }
            int nextNode = nextEdge.to, nextWeight = nextEdge.weight;
            if (dist[nextNode] == -1 || dist[nextNode] > dist[node] + nextWeight) {
                prev[nextNode] = node;
                dist[nextNode] = dist[node] + nextWeight;
                pq.push({nextNode, dist[nextNode]});
            }
        }
    }
    if (dist[n] == -1) {
        cout << -1;
        return 0;
    }
    stack<int> container;
    for (int node = n; node != -1; node = prev[node]) {
        container.push(node);
    }
    while (!container.empty()) {
        cout << container.top() << " ";
        container.pop();
    }
}
