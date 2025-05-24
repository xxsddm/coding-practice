// https://www.luogu.com.cn/problem/P1629

#define inf 0x7fffffff

#include "iostream"
#include "vector"
#include "queue"
#include "cstring"

using namespace std;

struct edge{
    int to, weight;
    edge(int v, int w): to(v), weight(w) {}
    bool operator < (const edge &other) const {return weight > other.weight;}
};

void dijkstra(int &ans, vector<edge> *container, int numNode) {
    int distance[numNode + 1];
    bool visited[numNode + 1];
    priority_queue<edge> pq;
    for (int i = 1; i <= numNode; i++) {
        distance[i] = 0x7fffffff;
    }
    memset(visited, false, sizeof(visited));
    distance[1] = 0;
    pq.push({1, 0});
    while (!pq.empty()) {
        edge ed = pq.top();
        pq.pop();
        int node = ed.to;
        if (visited[node]) {
            continue;
        }
        visited[node] = true;
        ans += distance[node];
        for (edge &nextEdge: container[node]) {
            int nextNode = nextEdge.to, nextWeight = nextEdge.weight;
            if (visited[nextNode]) {
                continue;
            }
            if (distance[nextNode] > distance[node] + nextWeight) {
                distance[nextNode] = distance[node] + nextWeight;
                pq.push({nextNode, distance[nextNode]});
            }
        }
    }
}

int dist[1001][1001];

int main() {    // Dijkstra
    int numNode, numRoad;
    scanf("%d %d", &numNode, &numRoad);
    int ans = 0;
    for (int i = 1; i <= numNode; i++) {
        for (int j = 1; j <= numNode; j++) {
            dist[i][j] = inf;
        }
    }
    // 反转邻接表依然以1为源点
    vector<edge> container[numNode + 1], reverseContainer[numNode + 1];
    for (int i = 0; i < numRoad; i++) {
        int node1, node2, weight;
        scanf("%d %d %d", &node1, &node2, &weight);
        dist[node1][node2] = min(dist[node1][node2], weight);
    }
    for (int i = 1; i <= numNode; i++) {
        for (int j = 1; j <= numNode; j++) {
            if (dist[i][j] != inf) {
                container[i].emplace_back(j, dist[i][j]);
                reverseContainer[j].emplace_back(i, dist[i][j]);
            }
        }
    }
    dijkstra(ans, container, numNode);
    dijkstra(ans, reverseContainer, numNode);
    cout << ans;
    return 0;
}
