// https://www.acwing.com/problem/content/97/

#include "iostream"

using namespace std;

int ans = 7, dir[5] = {1, 0, -1, 0, 1};
string lights;

bool check(int r, int c) {
	return r >= 0 && r < 5
	       && c >= 0 && c < 5;
}

int getIdx(int r, int c) {
	return 5 * r + c;
}

void change(int row, int col) {
	int temp = getIdx(row, col);
	lights[temp] = '0' + '1' - lights[temp];
	for (int i = 0; i < 4; i++) {
		int nextRow = row + dir[i], nextCol = col + dir[i + 1];
		if (!check(nextRow, nextCol)) {
			continue;
		}
		int idx = getIdx(nextRow, nextCol);
		lights[idx] = '0' + '1' - lights[idx];
	}
}

void dfs(int row, int count) {
	if (row == 4) {
		for (int idx = getIdx(4, 0); idx < 25; idx++) {
			if (lights[idx] == '0') {
				return;
			}
		}
		ans = count;
		return;
	}
	for (int col = 0, idx = getIdx(row, 0); col < 5; col++, idx++) {
		if (lights[idx] == '0') {
			if (++count >= ans) {
				return;
			}
			change(row + 1, col);
		}
	}
	dfs(row + 1, count);
}

int main() {
	int n;
	cin >> n;
	while (n--) {
		ans = 7;
		lights.clear();
		for (int i = 0; i < 5; i++) {
			string temp;
			cin >> temp;
			lights += temp;
		}
		string back = lights;
		// 枚举第一层是否修改的状态, 然后对1~4层关闭项的下一层进行修改, 若到达最后一层仍有关闭项, 则方案不可行
		for (int status = 0, limit = (1 << 5) - 1; status <= limit; status++) {
			lights = back;
			int count = 0;
			for (int i = 0, j = 1; i < 5; i++, j <<= 1) {
				if (status & j) {
					change(0, i);
					count++;
				}
			}
			dfs(0, count);
		}
		cout << (ans == 7 ? -1 : ans) << endl;
	}
	return 0;
}
