// https://www.luogu.com.cn/problem/P6054

#include "queue"
#include "cstring"
#include "iostream"

#define inf 1e10
#define eps 1e-5

using namespace std;

class Dinic {
private:
	struct Edge {
		int to = 0;
		double rest = 0;    // 记录边的指向点和残余流量
		Edge(int to, double rest): to(to), rest(rest) {}
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
				if (depth[nextNode] == 0 && edge.rest > eps) {
					depth[nextNode] = depth[node] + 1;
					q.push(nextNode);
				}
			}
		}
		return depth[end];
	}

	double dfs(int node, double limit) {    // 根据最短路径查找增广路径
		if (node == end || limit < eps) {
			return limit;
		}
		double flow = 0;
		for (int i = first[node], size = (int) adj[node].size(); i < size; i++, first[node]++) {
			int edgeIdx = adj[node][i];
			Edge &edge = edges[edgeIdx];
			int nextNode = edge.to;
			if (depth[nextNode] != depth[node] + 1) {
				continue;
			}
			double nextLimit = min(limit, edge.rest), temp = dfs(nextNode, nextLimit);
			if (temp < eps) {
				continue;
			}
			flow += temp;
			limit -= temp;
			edge.rest -= temp;
			edges[edgeIdx ^ 1].rest += temp;
			if (limit < eps || flow > inf) {
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

	void addEdge(int u, int v, double val) {
		edges.emplace_back(v, val);
		edges.emplace_back(u, 0);
		adj[u].push_back(idx++);    // 反向边索引为idx^1
		adj[v].push_back(idx++);
	}

	double maxFlow() {
		double ans = 0;
		while (bfs()) {
			ans += dfs(start, inf);
			if (ans > inf) {
				return -1;
			}
		}
		return ans;
	}
};

int n, m, p, y;

int getNode(int id, int test) {
	return id * (m + 1) + test;
}

int main() {	// 最小割问题, 建图
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d %d %d", &n, &m, &p, &y);
		int s = n * (m + 1), t = s + 1;
		double c[p];
		Dinic dinic(t + 1, s, t);
		for (int i = 0; i < p; i++) {
			scanf("%lf", &c[i]);
		}
		for (int test = 0; test < m; test++) {
			for (int id = 0; id < n; id++) {
				double cumsum = 0, prob = 1.0;
				for (int question = 0; question < p; question++) {
					double temp;
					scanf("%lf", &temp);
					prob *= temp;
					cumsum += c[question] * prob;
				}
				dinic.addEdge(getNode(id, test), getNode(id, test + 1), cumsum);
				// 至关重要的有向边, 不理解
				// 每个参与者的相应试卷节点向前连接无穷大的边
				dinic.addEdge(getNode(id, test + 1), getNode(id, test), inf);
			}
		}
		for (int i = 0; i < y; i++) {
			int a, b, k;
			scanf("%d %d %d", &a, &b, &k);
			a--, b--;
			for (int test = max(-k, 0); test + k <= m && test <= m; test++) {
				dinic.addEdge(getNode(b, test), getNode(a, test + k), inf);
			}
		}
		for (int id = 0; id < n; id++) {
			dinic.addEdge(s, getNode(id, 0), inf);
			dinic.addEdge(getNode(id, m), t, inf);
		}
		double ans = dinic.maxFlow();
		if (ans < 0) {
			printf("%d\n", -1);
		} else {
			printf("%.4lf\n", ans);
		}
	}
	return 0;
}
