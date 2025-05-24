// https://www.acwing.com/problem/content/168/

#include "iostream"

using namespace std;

int length = 0, restRow[9], restCol[9], restSquare[9], counter[1 << 9], status2num[1 << 9], idxs[81];
char container[82];

int lowbit(int &x) {
	return x & -x;
}

bool backtrack(int count) {
	if (count == 0) {
		return true;
	}
	int idx = -1, minnum = 10;
	for (int i = 0; i < length; i++) {	// 每次选择剩余备选方案最少的位置
		int &nextIdx = idxs[i];
		if (container[nextIdx] != '.') {
			continue;
		}
		int row = nextIdx / 9, col = nextIdx % 9, square = row / 3 * 3 + col / 3;
		int temp = counter[restRow[row] & restCol[col] & restSquare[square]];
		if (temp < minnum) {
			minnum = temp;
			idx = nextIdx;
		}
	}
	int row = idx / 9, col = idx % 9, square = row / 3 * 3 + col / 3;
	int status = restRow[row] & restCol[col] & restSquare[square];
	while (status) {
		int temp = lowbit(status), num = status2num[temp];
		status ^= temp;
		restRow[row] ^= temp;
		restCol[col] ^= temp;
		restSquare[square] ^= temp;
		container[idx] = num + '0';
		if (backtrack(count - 1)) {
			return true;
		}
		restRow[row] ^= temp;
		restCol[col] ^= temp;
		restSquare[square] ^= temp;
		container[idx] = '.';
	}
	return false;
}

int main() {
	counter[0] = 0;
	for (int i = 1 << 8, j = 9; i; i >>= 1, j--) {	// 记录lowbit相应数字
		status2num[i] = j;
	}
	for (int i = (1 << 9) - 1; i; i--) {	// 记录每个状态的备选方案数
		for (int j = i; j; j ^= lowbit(j)) {
			counter[i]++;
		}
	}
	while (scanf("%s", container) && container[0] != 'e') {
		length = 0;
		int count = 0;
		for (int i = 0, temp = (1 << 9) - 1; i < 9; i++) {
			restRow[i] = temp;
			restCol[i] = temp;
			restSquare[i] = temp;
		}
		for (int i = 0; i < 81; i++) {
			if (container[i] != '.') {
				int row = i / 9, col = i % 9, square = row / 3 * 3 + col / 3;
				int temp = 1 << (container[i] - '1');
				restRow[row] ^= temp;
				restCol[col] ^= temp;
				restSquare[square] ^= temp;
			} else {
				count++;
				idxs[length++] = i;;
			}
		}
		backtrack(count);
		printf("%s\n", container);
	}
	return 0;
}
