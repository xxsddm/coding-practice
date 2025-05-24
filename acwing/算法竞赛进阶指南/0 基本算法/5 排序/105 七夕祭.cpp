// https://www.acwing.com/problem/content/107/

#include "algorithm"
#include "cstring"
#include "iostream"

using namespace std;

int N, M, T;

long long count(int length, int *counter) {	// 可找到不交换的点断开环
	int mean = T / length;
	long long ans = 0;
	for (int i = 0; i < length; i++) {
		counter[i] -= mean;
	}
	for (int i = 1; i < length; i++) {
		counter[i] += counter[i - 1];
	}
	sort(counter, counter + length);
	int mid = counter[length >> 1]; // 利用中位数性质
	for (int i = 0; i < length; i++) {
		ans += abs(counter[i] - mid);
	}
	return ans;
}

int main() {	// P34
	scanf("%d %d %d", &N, &M, &T);
	int counterRow[N], counterCol[M];
	long long ans = 0;
	memset(counterRow, 0, sizeof(counterRow));
	memset(counterCol, 0, sizeof(counterCol));
	for (int i = 0; i < T; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		counterRow[x - 1]++;
		counterCol[y - 1]++;
	}
	if (T % N == 0 && T % M == 0) {
		ans += count(N, counterRow);
		ans += count(M, counterCol);
		printf("both %lld", ans);
	} else if (T % N == 0) {
		ans += count(N, counterRow);
		printf("row %lld", ans);
	} else if (T % M == 0) {
		ans += count(M, counterCol);
		printf("column %lld", ans);
	} else {
		cout << "impossible";
	}
	return 0;
}
