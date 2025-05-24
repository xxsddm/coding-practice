// https://www.acwing.com/problem/content/91/

#include "iostream"

using namespace std;

int multiply(int num1, int num2, int mod) {
	return (int) (((long long) num1 * num2) % mod);
}

int main() {
	int a, b, p, ans = 1;
	scanf("%d %d %d", &a, &b, &p);
	if (a == 0) {
		printf("%d", 0);
		return 0;
	}
	if (b == 0) {
		printf("%d", 1 % p);
		return 0;
	}
	while (b) {
		if (b & 1) {
			ans = multiply(ans, a, p);
		}
		a = multiply(a, a, p);
		b >>= 1;
	}
	printf("%d", ans);
	return 0;
}
