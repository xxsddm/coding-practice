// https://www.luogu.com.cn/problem/P3376

#include "queue"
#include "cstring"
#include "iostream"

using namespace std;

class Dinic {
private:
	struct Edge {
		int to = 0, rest = 0;   // 记录边的指向点和残余流量
	};

	int idx = 0, numV = 0, start, end, *depth, *first;
	Edge *edges;
	vector<int> *adj;

	int bfs() { // BFS分层, 标记最短路径
		memset(depth, 0, sizeof(int) * numV);
		memset(first, 0, sizeof(int) * numV);	// first保存子节点访问起点, 减少dfs非残余路径访问(弧优化)
		queue<int> q;
		q.push(start);
		depth[start] = 1;
		while (!q.empty() && !depth[end]) {
			int node = q.front();
			q.pop();
			for (int &i : adj[node]) {
				Edge &edge = edges[i];
				int nextNode = edge.to;
				if (!depth[nextNode] && edge.rest) {
					depth[nextNode] = depth[node] + 1;
					q.push(nextNode);
				}
			}
		}
		return depth[end];
	}

	long long dfs(int node, int limit) {    // 根据最短路径查找增广路径
		if (node == end || limit == 0) {
			return limit;
		}
		long long flow = 0;
		for (int i = first[node], size = (int) adj[node].size(); i < size; i++, first[node]++) {
			int edgeIdx = adj[node][i];
			Edge &edge = edges[edgeIdx];
			int nextNode = edge.to;
			if (depth[nextNode] != depth[node] + 1) {
				continue;
			}
			int nextLimit = node == start ? edge.rest : min(limit, edge.rest), temp = dfs(nextNode, nextLimit);
			if (temp == 0) {
				continue;
			}
			flow += temp;
			if (limit != start) {
				limit -= temp;
			}
			edge.rest -= temp;
			edges[edgeIdx ^ 1].rest += temp;
			if (limit == 0) {
				break;
			}
		}
		return flow;
	}

public:
	Dinic(int V, int E, int s, int t) {
		numV = V, start = s, end = t, depth = new int[V], first = new int[V];
		edges = new Edge[2 * E];
		adj = new vector<int>[V];
	}

	void addEdge(int u, int v, int val) {
		Edge &edge1 = edges[idx], &edge2 = edges[idx + 1];
		edge1.to = v, edge1.rest = val;
		edge2.to = u;
		adj[u].push_back(idx++);    // 反向边索引为idx^1
		adj[v].push_back(idx++);
	}

	long long maxFlow() {
		long long ans = 0;
		while (bfs()) {
			ans += dfs(start, -1);
		}
		return ans;
	}
};

int main() {
	int n, m, s, t;
	scanf("%d %d %d %d", &n, &m, &s, &t);
	Dinic dinic(n, m, s - 1, t - 1);
	for (int i = 0; i < m; i++) {
		int u, v, val;
		scanf("%d %d %d", &u, &v, &val);
		dinic.addEdge(u - 1, v - 1, val);
	}
	printf("%lld", dinic.maxFlow());
	return 0;
}