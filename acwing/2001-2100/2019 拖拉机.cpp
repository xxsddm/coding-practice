// https://www.acwing.com/problem/content/2021/

#include "queue"
#include "cstring"
#include "utility"
#include "iostream"

using namespace std;

int counter[1002][1002], dir[5] = {1, 0, -1, 0, 1};
bool container[1002][1002];

bool check(int row, int col) {
	return row >= 0 && row <= 1001 && col >= 0 && col <= 1001;
}

int main() {
	memset(counter, -1, sizeof(counter));
	memset(container, false, sizeof(container));
	int N, startR, startL;
	cin >> N >> startR >> startL;
	for (int i = 0; i < N; i++) {
		int r, c;
		cin >> r >> c;
		container[r][c] = true;
	}
	counter[startR][startL] = container[startR][startL] ? 1 : 0;
	deque<pair<int, int>> q;
	q.emplace_back(startR, startL);
	while (true) {
		auto &node = q.front();
		int row = node.first, col = node.second, num = counter[row][col];
		q.pop_front();
		// 则最先到达的移除数量最少
		if (row == 0 && col == 0) {
			cout << num;
			return 0;
		}
		for (int j = 0; j < 4; j++) {
			int nextRow = row + dir[j], nextCol = col + dir[j + 1];
			if (!check(nextRow, nextCol)) {
				continue;
			}
			int nextNum = num + (container[nextRow][nextCol] ? 1 : 0);
			if (counter[nextRow][nextCol] == -1 || counter[nextRow][nextCol] > nextNum) {
				counter[nextRow][nextCol] = nextNum;
				// 小的往前大的往后
				if (container[nextRow][nextCol]) {
					q.emplace_back(nextRow, nextCol);
				} else {
					q.emplace_front(nextRow, nextCol);
				}

			}
		}
	}
	return 0;
}
