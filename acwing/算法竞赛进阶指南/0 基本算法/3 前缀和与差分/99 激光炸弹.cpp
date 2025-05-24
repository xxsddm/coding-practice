// https://www.acwing.com/problem/content/description/101/

#include "cstring"
#include "iostream"

using namespace std;

int N, R, rowStart = 5001, rowEnd = 1, colStart = 5001, colEnd = 1, counter[5002][5002];

int main() {
	int ans = 0;
	memset(counter, 0, sizeof(counter));
	scanf("%d %d", &N, &R);
	for (int i = 0; i < N; i++) {	// 留出0
		int X, Y, W;
		scanf("%d %d %d", &X, &Y, &W);
		counter[X + 1][Y + 1] += W;
		rowStart = min(rowStart, X + 1);
		rowEnd = max(rowEnd, X + 1);
		colStart = min(colStart, Y + 1);
		colEnd = max(colEnd, Y + 1);
	}
	// 1~row, 1~col累和
	for (int row = rowStart; row <= rowEnd; row++) {
		for (int col = colStart; col <= colEnd; col++) {
			counter[row][col] += counter[row - 1][col] + counter[row][col - 1] - counter[row - 1][col - 1];
		}
	}
	// 枚举窗口行终点, 列终点
	for (int row = min(rowStart + R - 1, rowEnd); row <= rowEnd; row++) {
		for (int col = min(colStart + R - 1, colEnd); col <= colEnd; col++) {
			// 计算窗口行起点, 列起点
			int r = max(rowStart, row - R + 1), c = max(colStart, col - R + 1);
			ans = max(ans, counter[row][col] - counter[row][c - 1] - counter[r - 1][col] + counter[r - 1][c - 1]);
		}
	}
	printf("%d", ans);
	return 0;
}
