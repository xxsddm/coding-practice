// http://oj.daimayuan.top/course/10/problem/380

#include "queue"
#include "cstring"
#include "iostream"

using namespace std;

int n, inf = 0x7fffffff, *bike, **dist;
bool *visited;

void dijkstra(int idx, vector<pair<int, int>> *next) {
	int count = 0, *d = dist[idx], start = bike[idx];
	for (int i = 1; i <= n; i++) {
		d[i] = inf;
	}
	memset(visited, false, sizeof(bool) * (n + 1));
	d[start] = 0;
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
	pq.emplace(d[start], start);
	while (!pq.empty() && count < n) {
		int node = pq.top().second;
		pq.pop();
		if (visited[node]) {
			continue;
		}
		visited[node] = true;
		count++;
		for (pair<int, int> &p : next[node]) {
			auto &[nextNode, weight] = p;
			if (visited[nextNode]) {
				continue;
			}
			if (d[nextNode] > d[node] + weight) {
				d[nextNode] = d[node] + weight;
				pq.emplace(d[nextNode], nextNode);
			}
		}
	}
}

int main() {
	int vWalk, vBike, m, k;
	scanf("%d %d", &vWalk, &vBike);
	scanf("%d %d", &n, &m);
	visited = new bool[n + 1];
	vector<pair<int, int>> next[n + 1];
	for (int i = 0; i < m; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		next[u].emplace_back(v, w);
		next[v].emplace_back(u, w);
	}
	scanf("%d", &k);
	int prob[k];
	bike = new int[k + 1];
	bike[k] = 1;
	for (int i = 0; i < k; i++) {
		scanf("%d %d", &bike[i], &prob[i]);
	}
	dist = new int*[k + 1];
	for (int i = 0; i <= k; i++) {
		dist[i] = new int[n + 1];
	}
	dijkstra(k, next);
	if (dist[k][n] == inf) {
		printf("-1");
		return 0;
	}
	int num2idx[(1 << (k - 1)) + 1];
	double ans = 1.0 * dist[k][n] / vWalk, dp[1 << k][k];	// 已访问自行车状态, 当前使用的自行车 -> 该点到终点期望时间
	for (int i = 0, j = 1; i < k; i++, j <<= 1) {
		dijkstra(i, next);
		num2idx[j] = i;
	}
	// 枚举使用自行车的点, 若未开启则考虑移动到下一有自行车且未访问的点
	for (int status = (1 << k) - 1; status >= 0; status--) {
		int used = status, unused = ((1 << k) - 1) ^ status;
		while (used) {
			int temp1 = used & -used, idx = num2idx[temp1];
			used ^= temp1;
			double tGood = 1.0 * dist[idx][n] / vBike, tBad = 1.0 * dist[idx][n] / vWalk;
			int back = unused;
			while (back) {
				int temp2 = back & -back, nextIdx = num2idx[temp2], nextNode = bike[nextIdx];
				back ^= temp2;
				tBad = min(tBad, 1.0 * dist[idx][nextNode] / vWalk + dp[status ^ temp2][nextIdx]);
			}
			double probBad = 0.01 * prob[idx];
			dp[status][idx] = (1 - probBad) * tGood + probBad * tBad;
		}
	}
	// 则若该自行车为第一个尝试的点, 可行的最短期望时间
	for (int i = 0, j = 1; i < k; i++, j <<= 1) {
		ans = min(ans, 1.0 * dist[k][bike[i]] / vWalk + dp[j][i]);
	}
	printf("%lf", ans);
	return 0;
}
