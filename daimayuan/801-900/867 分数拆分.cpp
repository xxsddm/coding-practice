// http://oj.daimayuan.top/course/11/problem/867

#include "iostream"

int main() {
	int k;
	scanf("%d", &k);
	int ans = 0;
	for (int i = k + 1, limit = k << 1; i <= limit; i++) {
		if ((long long) i * k % (i - k) == 0) {
			ans++;
		}
	}
	printf("%d", ans);
	return 0;
}
