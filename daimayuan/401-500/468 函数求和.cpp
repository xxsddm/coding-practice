// http://oj.daimayuan.top/course/10/problem/468

#include "iostream"

using namespace std;

int main() {
	int n, k;
	scanf("%d %d", &n, &k);
	long long mod = 998244353, add = 1LL << (k - 1), ans = 0, used = 0;
	for (int i = 1; i <= n; i++) {
		long long num;
		scanf("%lld", &num);
		long long next = num | used, diff = next ^ used;
		while (diff) {
			long long temp = diff & -diff;
			diff ^= temp;
			ans = (ans + add * i) % mod;
			add >>= 1;
		}
		used = next;
	}
	printf("%lld", ans);
	return 0;
}
