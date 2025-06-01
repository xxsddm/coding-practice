#include <iostream>
#include <vector>
#include <queue>

using namespace std;

using ll = long long;

struct Edge {
    int dst;
    ll rest;
    ll cost;

    Edge(int dst, ll rest, ll cost): dst(dst), rest(rest), cost(cost){}
};

class MinCostFlow {
public:
    ll INF = 0x7fffffffffffffff;
    int source, target, nNode;
    vector<vector<int>> adj;
    vector<Edge> edgeList;
    vector<ll> dist;
    vector<int> first;
    vector<bool> visited;
    ll maxFlow = 0, minCost = 0;

    /**
     * @param source 源点索引
     * @param target 终点索引
     * @param nNode 点的数量(所有点按索引唯一区分)
     */
    MinCostFlow(int source, int target, int nNode): source(source), target(target), nNode(nNode) {
        adj.resize(nNode);
        dist.resize(nNode);
        first.resize(nNode);
        visited.resize(nNode, false);
    }

    void addEdge(int src, int dst, ll rest, ll cost) {
        int idx1 = (int) edgeList.size();
        int idx2 = idx1 ^ 1;
        adj[src].push_back(idx1);
        adj[dst].push_back(idx2);
        edgeList.emplace_back(dst, rest, cost);
        edgeList.emplace_back(src, 0, - cost);
    }

    bool spfa() {
        for (int i = 0; i < nNode; ++i) {
            first[i] = 0;
            dist[i] = INF;
        }
        queue<int> q;
        q.push(source);
        visited[source] = true;
        dist[source] = 0;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            visited[node] = false;
            for (int edgeIdx : adj[node]) {
                Edge& edge = edgeList[edgeIdx];
                int nextNode = edge.dst;
                ll nextCost = dist[node] + edge.cost;
                if (edge.rest == 0 || nextCost >= dist[nextNode]) {
                    continue;
                }
                dist[nextNode] = nextCost;
                if (!visited[nextNode]) {
                    q.push(nextNode);
                    visited[nextNode] = true;
                }
            }
        }
        return dist[target] != INF;
    }

    ll dfs(int node, ll limit) {
        if (node == target || limit == 0) {
            return limit;
        }
        ll ans = 0;
        visited[node] = true;
        for (int &i = first[node], size = (int) adj[node].size(); i < size; ++i) {
            int edgeIdx = adj[node][i];
            Edge &edge = edgeList[edgeIdx];
            int nextNode = edge.dst;
            if (visited[nextNode] or edge.rest == 0 or dist[nextNode] != dist[node] + edge.cost) {
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
            minCost += edge.cost * temp;
            if (limit == 0) {
                break;
            }
        }
        visited[node] = false;
        return ans;
    }


    void calculate(ll flow) {
        while (spfa() and flow > 0) {
            ll temp = dfs(source, flow);
            maxFlow += temp;
            flow -= temp;
        }
    }
};