// https://www.acwing.com/problem/content/1931/

#include "cstring"
#include "iostream"

using namespace std;

int N, M;
int dirs[5] = {1, 0, -1, 0, 1}, visited[1000][1000][4];
// int nextdir1[4] = {3, 2, 1, 0}, nextdir2[4] = {1, 0, 3, 2};	// 可找规律
char container[1000][1000];

int dfs(int row, int col, int dir) {
	if (row < 0 || row == N || col < 0 || col == M) {
		return 0;
	}
	if (!visited[row][col][dir]) {
		visited[row][col][dir] = -1;
		int nextDir = container[row][col] == '/' ? ((5 - dir) % 4) : (3 - dir);
		int nextRow = row + dirs[nextDir], nextCol = col + dirs[nextDir + 1];
		int temp = dfs(nextRow, nextCol, nextDir);
		visited[row][col][dir] = temp == -1 ? -1 : (temp + 1);
	}
	return visited[row][col][dir];
}

int main() {
	int ans = 0, temp;
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		scanf("%s", container[i]);
	}
	memset(visited, 0, N * M * 4 * sizeof(int));
	for (int i = 0; i < M; i++) {
		temp = dfs(0, i, 0);
		if (temp == -1) {
			cout << -1;
			return 0;
		}
		ans = max(ans, temp);
		temp = dfs(N - 1, i, 2);
		if (temp == -1) {
			cout << -1;
			return 0;
		}
		ans = max(ans, temp);
	}
	for (int i = 0; i < N; i++) {
		temp = dfs(i, 0, 3);
		if (temp == -1) {
			cout << -1;
			return 0;
		}
		ans = max(ans, temp);
		temp = dfs(i, M - 1, 1);
		if (temp == -1) {
			cout << -1;
			return 0;
		}
		ans = max(ans, temp);
	}
	printf("%d", ans);
	return 0;
}
