// http://oj.daimayuan.top/course/10/problem/467

#include "algorithm"
#include "iostream"

int mod = 1000000007, *fac, *facInv;

int quickPower(int num) {	// Fermat小定理, 计算num关于mod乘法逆元(num ^ (mod - 2))
	int ans = 1, temp = num, power = 1000000005;
	while (power) {
		if (power & 1) {
			ans = (long long) ans * temp % mod;
		}
		temp = (long long) temp * temp % mod;
		power >>= 1;
	}
	return ans;
}

int calculate(int x, int y) {
	if (x == 0 || y == 0) {
		return 1;
	} else if (x == 1 || y == 1) {
		return x + y;
	}
	return ((long long) fac[x + y] * facInv[x] % mod) * facInv[y] % mod;
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	std::pair<int, int> container[m];
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &container[i].first, &container[i].second);
	}
	fac = new int[2 * n - 1], facInv = new int[n];
	fac[0] = 1, facInv[0] = 1;
	for (int i = 1, limit = 2 * n - 1; i < limit; i++) {
		fac[i] = (long long) fac[i - 1] * i % mod;
	}
	for (int i = 1; i < n; i++) {
		facInv[i] = (long long) facInv[i - 1] * quickPower(i) % mod;
	}
	sort(container, container + m, [] (auto & p1, auto & p2) -> bool {
		return p1.first + p1.second < p2.first + p2.second;
	});
	int sum[m];
	for (int i = 0; i < m; i++) {
		sum[i] = container[i].first + container[i].second;
	}
	int ans = calculate(n - 1, n - 1), dp[m];
	for (int i = 0; i < m; i++) {
		int &x = container[i].first, &y = container[i].second, &z = sum[i];
		int temp = calculate(x - 1, y - 1);
		for (int j = 0; sum[j] < z; j++) {
			if (container[j].first > x || container[j].second > y) {
				continue;
			}
			temp -= ((long long) dp[j] * calculate(x - container[j].first, y - container[j].second)) % mod;
			if (temp < 0) {
				temp += mod;
			}
		}
		dp[i] = temp;
		if (temp) {
			ans -= ((long long) temp * calculate(n - x, n - y)) % mod;
			if (ans < 0) {
				ans += mod;
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}
