// http://oj.daimayuan.top/course/11/problem/498

#include "cstring"
#include "iostream"

int mod = 1000000007, length = 1, counter[10][200001][10];

int main() {
	int t;
	scanf("%d", &t);
	for (int i = 0; i < 10; i++) {
		memset(counter[i][0], 0, sizeof(int) * 10);
		counter[i][0][i] = 1;
	}
	while (t--) {
		int n, m;
		scanf("%d %d", &n, &m);
		while (length <= m) {
			for (int i = 0; i < 10; i++) {
				counter[i][length][0] = counter[i][length - 1][9];
				counter[i][length][1] = (counter[i][length - 1][0] + counter[i][length - 1][9]) % mod;
				for (int j = 2; j < 10; j++) {
					counter[i][length][j] = counter[i][length - 1][j - 1];
				}
			}
			length++;
		}
		int ans = 0;
		while (n) {
			int temp = n % 10;
			n /= 10;
			for (int i = 0; i < 10; i++) {
				ans = (ans + counter[temp][m][i]) % mod;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
