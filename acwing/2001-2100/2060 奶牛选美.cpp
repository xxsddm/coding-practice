// https://www.acwing.com/problem/content/2062/

#include "queue"
#include "cstring"
#include "iostream"

using namespace std;

int N, M, inf;
int dir[5] = { -1, 0, 1, 0, -1};
string target;

int loc2idx(int row, int col) {
	return row * M + col;
}

bool check(int row, int col) {
	return row >= 0 && row < N
	       && col >= 0 && col < M;
}

void dfs(int row, int col) {
	for (int i = 0; i < 4; i++) {
		int nextRow = row + dir[i], nextCol = col + dir[i + 1];
		if (!check(nextRow, nextCol)) {
			continue;
		}
		int idx = loc2idx(nextRow, nextCol);
		if (target[idx] == 'X') {
			target[idx] = 'Y';
			dfs(nextRow, nextCol);
		}
	}
}

int bfs(int r, int c) {
	int ans = 0;
	queue<pair<int, int>> container;
	bool visited[N][M];
	memset(visited, false, sizeof(visited));
	visited[r][c] = true;
	container.emplace(r, c);
	while (!container.empty()) {
		ans++;
		for (int i = 0, size = (int) container.size(); i < size; i++) {
			auto &temp = container.front();
			int row = temp.first, col = temp.second;
			bool skip = false;
			deque<pair<int, int>> subcontainer;
			container.pop();
			for (int j = 0; j < 4; j++) {
				int nextRow = row + dir[j], nextCol = col + dir[j + 1];
				if (!check(nextRow, nextCol) || visited[nextRow][nextCol]) {
					continue;
				}
				visited[nextRow][nextCol] = true;
				int idx = loc2idx(nextRow, nextCol);
				if (target[idx] == 'Y') {
					if (ans > 1) {	// Y区域边缘的点不重复考虑
						skip = true;
						break;
					}
					continue;
				}
				if (target[idx] == 'X') {
					return ans;
				}
				subcontainer.emplace_back(nextRow, nextCol);
			}
			if (!skip) {
				for (auto &p : subcontainer) {
					container.push(p);
				}
			}
		}
	}
	return inf;
}

int main() {
	scanf("%d %d", &N, &M);
	inf = N * M;
	for (int i = 0; i < N; i++) {
		string temp;
		cin >> temp;
		target += temp;
	}
	for (int i = 0, length = (int) target.size(); i < length; i++) {
		int row = i / M, col = i % M;
		if (target[loc2idx(row, col)] == 'X') {
			target[loc2idx(row, col)] = 'Y';
			dfs(row, col);	// 修改元素为Y
			break;
		}
	}
	int ans = inf;
	for (int row = 0; row < N; row++) {
		for (int col = 0; col < M; col++) {
			if (target[loc2idx(row, col)] == 'Y') {
				for (int i = 0; i < 4; i++) {
					int r = row + dir[i], c = col + dir[i + 1];
					if (check(r, c) && target[loc2idx(r, c)] == '.') {
						ans = min(ans, bfs(r, c));
					}
				}
			}
		}
	}
	printf("%d", ans);
	return 0;
}
