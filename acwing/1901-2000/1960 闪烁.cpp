// https://www.acwing.com/problem/content/description/1962/

#include "cstring"
#include "iostream"

using namespace std;

int N;

int change(int status) {
	return ((status & 1) << (N - 1)) ^ (status >> 1) ^ status;
}

void output(int status) {
	for (int temp = 1 << (N - 1); temp; temp >>= 1) {
		if (status & temp) {
			cout << 1 << endl;
		} else {
			cout << 0 << endl;
		}
	}
}

int main() {	// 自动找规律
	long long B;
	scanf("%d %lld", &N, &B);
	// 记录上一个该状态的位置
	int T = -1, status = 0, prev[1 << N];
	memset(prev, -1, sizeof(prev));
	for (int i = 0, temp = 1 << (N - 1); i < N; i++, temp >>= 1) {
		int j;
		cin >> j;
		if (j) {
			status ^= temp;
		}
	}
	prev[status] = 0;
	for (int i = 1; i <= B; i++) {
		status = change(status);
		if (prev[status] == -1) {
			prev[status] = i;
		} else {
			T = i - prev[status];
			break;
		}
	}
	if (T == -1) {
		output(status);
		return 0;
	}
	for (int i = 1, limit = (int) ((B - prev[status]) % T); i <= limit; i++) {
		status = change(status);
	}
	output(status);
	return 0;
}
