// https://www.acwing.com/problem/content/2007/

#include "cstring"
#include "iostream"

using namespace std;

int N, ans = 0, dir[5] = {1, 0, -1, 0, 1}, counter[5][5];
string target;

bool check(int row, int col) {
	return row >= 0 && row < N && col >= 0 && col < N;
}

int getIdx(int row, int col) {
	return row * N + col;
}

void backtrack(int left, int right, int row, int col, int visited) {
	if (left == right) {
		ans = left + right;
		counter[row][col] = ans;
		return;
	}
	for (int i = 0; i < 4; i++) {
		int nextRow = row + dir[i], nextCol = col + dir[i + 1];
		// 剔除已访问节点
		if (!check(nextRow, nextCol) || visited & (1 << (nextRow * N + nextCol))) {
			continue;
		}
		char temp = target[getIdx(nextRow, nextCol)];
		// 剔除不对称情况
		if (right && temp == '(') {
			continue;
		}
		int nextLeft = left + (temp == '(' ? 1 : 0), nextRight = right + (temp == ')' ? 1 : 0);
		// 剔除必然更短情况
		if (nextRight && (nextLeft << 1) <= max(ans, counter[nextRow][nextCol])) {
			continue;
		}
		backtrack(nextLeft, nextRight, nextRow, nextCol, visited ^ (1 << (nextRow * N + nextCol)));
	}
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		string temp;
		cin >> temp;
		target += temp;
	}
	memset(counter, 0, sizeof(counter));
	if (target[0] == ')') {
		cout << 0;
		return 0;
	}
	backtrack(1, 0, 0, 0, 1);
	cout << ans;
	return 0;
}
