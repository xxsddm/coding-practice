// https://www.acwing.com/problem/content/140/

#include "cstring"
#include "iostream"

using namespace std;

int main() {
	string S;
	int m, mod = 100007, base = 203;
	cin >> S;
	scanf("%d", &m);
	int length = (int) S.size(), cumsum[length + 1], power[length + 1];
	cumsum[0] = 0, power[0] = 1;
	for (int i = 0, pre = 0, mul = 1; i < length; i++) {
		int temp = S[i] - 'a';
		pre = (pre * base + temp * temp) % mod;
		mul = (mul * base) % mod;
		cumsum[i + 1] = pre;
		power[i + 1] = mul;

	}
	for (int i = 0; i < m; i++) {
		int l1, r1, l2, r2;
		scanf("%d %d %d %d", &l1, &r1, &l2, &r2);
		if (r1 - l1 != r2 - l2) {
			printf("No\n");
			continue;
		}
		if (l1 == l2) {
			printf("Yes\n");
			continue;
		}
		// 注意左侧为高位
		int key1 = (cumsum[r1] - ((long long) cumsum[l1 - 1] * power[r1 - l1 + 1]) % mod + mod) % mod;
		int key2 = (cumsum[r2] - ((long long) cumsum[l2 - 1] * power[r2 - l2 + 1]) % mod + mod) % mod;
		printf(key1 == key2 ? "Yes\n" : "No\n");
	}
	return 0;
}
