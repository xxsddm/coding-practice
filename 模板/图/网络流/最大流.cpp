#include <iostream>
#include <vector>
#include <queue>

using namespace std;

using ll = long long;

struct Edge {
    int dst;
    ll rest;

    Edge(int dst, ll rest): dst(dst), rest(rest){}
};

class MaxFlow {
public:
    ll MAX_LL = 0x7fffffffffffffff;
    int MAX_INT = 0x7fffffff;
    int source, target, nNode;
    vector<vector<int>> adj;
    vector<Edge> edgeList;
    vector<int> first, dist;
    ll maxFlow = 0;

    /**
     * @param source 源点索引
     * @param target 终点索引
     * @param nNode 点的数量(所有点按索引唯一区分)
     */
    MaxFlow(int source, int target, int nNode): source(source), target(target), nNode(nNode) {
        adj.resize(nNode);
        dist.resize(nNode);
        first.resize(nNode);
    }

    void addEdge(int src, int dst, ll rest) {
        int idx1 = (int) edgeList.size();
        int idx2 = idx1 ^ 1;
        adj[src].push_back(idx1);
        adj[dst].push_back(idx2);
        edgeList.emplace_back(dst, rest);
        edgeList.emplace_back(src, 0);
    }

    bool bfs() {
        for (int i = 0; i < nNode; ++i) {
            first[i] = 0;
            dist[i] = MAX_INT;
        }
        queue<int> q;
        q.push(source);
        dist[source] = 0;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            for (int edgeIdx : adj[node]) {
                Edge& edge = edgeList[edgeIdx];
                int nextNode = edge.dst;
                int nextDist = dist[node] + 1;
                if (edge.rest == 0 || nextDist >= dist[nextNode]) {
                    continue;
                }
                dist[nextNode] = nextDist;
                q.push(nextNode);
            }
        }
        return dist[target] != MAX_INT;
    }

    ll dfs(int node, ll limit) {
        if (node == target || limit == 0) {
            return limit;
        }
        ll ans = 0;
        for (int &i = first[node], size = (int) adj[node].size(); i < size; ++i) {
            int edgeIdx = adj[node][i];
            Edge &edge = edgeList[edgeIdx];
            int nextNode = edge.dst;
            if (edge.rest == 0 or dist[nextNode] != dist[node] + 1) {
                continue;
            }
            ll temp = dfs(nextNode, min(edge.rest, limit));
            if (temp == 0) {
                continue;
            }
            Edge &reverseEdge = edgeList[edgeIdx ^ 1];
            edge.rest -= temp;
            reverseEdge.rest += temp;
            limit -= temp;
            ans += temp;
            if (limit == 0) {
                break;
            }
        }
        return ans;
    }


    void calculate(ll flow) {
        while (bfs() and flow > 0) {
            ll temp = dfs(source, flow);
            maxFlow += temp;
            flow -= temp;
        }
    }
};

int main() {
    int n, m, s, t;
    scanf("%d %d %d %d", &n, &m, &s, &t);
    MaxFlow calculator = MaxFlow(s, t, n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        calculator.addEdge(u, v, w);
    }
    calculator.calculate((long long) 1 << 50);
    printf("%lld", calculator.maxFlow);
    return 0;
}