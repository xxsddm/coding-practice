// https://www.acwing.com/problem/content/92/

#include "iostream"

using namespace std;

int main() {
	long long a, b, p, ans = 0;
	scanf("%lld %lld %lld", &a, &b, &p);
	a %= p, b %= p;
	while (b) {
		if (b & 1) {
			ans += a;
			ans %= p;
		}
		a <<= 1;
		a %= p;
		b >>= 1;
	}
	printf("%lld", ans);
	return 0;
}
