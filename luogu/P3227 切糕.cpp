// https://www.luogu.com.cn/problem/P3227

#include "queue"
#include "cstring"
#include "iostream"

#define inf 0x7fffffff

using namespace std;

class Dinic {
private:
	struct Edge {
		int to = 0, rest = 0;   // 记录边的指向点和残余流量
		Edge(int to, int rest): to(to), rest(rest) {}
	};

	int idx = 0, numV = 0, start, end, *depth, *first;
	vector<Edge> edges;
	vector<int> *adj;

	int bfs() { // BFS分层, 标记最短路径
		memset(depth, 0, sizeof(int) * numV);
		memset(first, 0, sizeof(int) * numV);	// first保存子节点访问起点, 减少dfs非残余路径访问
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

	int dfs(int node, int limit) {  // 根据最短路径查找增广路径
		if (node == end || limit == 0) {
			return limit;
		}
		int flow = 0;
		for (int i = first[node], size = (int) adj[node].size(); i < size; i++, first[node]++) {
			int edgeIdx = adj[node][i];
			Edge &edge = edges[edgeIdx];
			int nextNode = edge.to;
			if (depth[nextNode] != depth[node] + 1) {
				continue;
			}
			int nextLimit = min(limit, edge.rest), temp = dfs(nextNode, nextLimit);
			if (temp == 0) {
				continue;
			}
			flow += temp;
			limit -= temp;
			edge.rest -= temp;
			edges[edgeIdx ^ 1].rest += temp;
			if (limit == 0) {
				break;
			}
		}
		return flow;
	}

public:
	Dinic(int V, int s, int t) {
		numV = V, start = s, end = t, depth = new int[V], first = new int[V];
		adj = new vector<int>[V];
	}

	void addEdge(int u, int v, int val) {
		edges.emplace_back(v, val);
		edges.emplace_back(u, 0);
		adj[u].push_back(idx++);    // 反向边索引为idx^1
		adj[v].push_back(idx++);
	}

	int maxFlow() {
		int ans = 0;
		while (bfs()) {
			ans += dfs(start, inf);
		}
		return ans;
	}
};

int P, Q, R;

int getNode(int x, int y, int z) {
	return z * P * Q + x * Q + y;
}

int main() {	// 建图, 最小割
	int D, dirs[] = {1, 0, -1, 0, 1};
	scanf("%d %d %d", &P, &Q, &R);
	scanf("%d", &D);
	int s = P * Q * (R + 1), t = s + 1;
	Dinic dinic(t + 1, s, t);
	for (int z = 0; z < R; z++) {
		for (int x = 0; x < P; x++) {
			for (int y = 0; y < Q; y++) {
				int val;
				scanf("%d", &val);
				dinic.addEdge(getNode(x, y, z), getNode(x, y, z + 1), val);
			}
		}
	}
	for (int x = 0; x < P; x++) {
		for (int y = 0; y < Q; y++) {
			dinic.addEdge(s, getNode(x, y, 0), inf);
			dinic.addEdge(getNode(x, y, R), t, inf);
		}
	}
	for (int x = 0; x < P; x++) {
		for (int y = 0; y < Q; y++) {
			for (int i = 0; i < 4; i++) {
				int nextX = x + dirs[i], nextY = y + dirs[i + 1];
				if (nextX >= 0 && nextY >= 0 && nextX < P && nextY < Q) {
					for (int z = D; z < R; z++) {
						// 画图可知必须由z较大点指向较小点
						// 此时切割不可过该有向边否则最大流为无穷大
						dinic.addEdge(getNode(x, y, z), getNode(nextX, nextY, z - D), inf);
					}
				}
			}
		}
	}
	printf("%d", dinic.maxFlow());
	return 0;
}
