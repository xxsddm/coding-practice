// http://oj.daimayuan.top/course/10/problem/611

#include "iostream"

int idx1 = 2, idx2 = 2, fac[1000030], facInv[1000030];
long long mod = 1e9 + 7;

int quickPower(int num, int power) {
	if (num == 1) {
		return 1;
	}
	long long ans = 1, temp = num;
	while (power) {
		if (power & 1) {
			ans = ans * temp % mod;
		}
		temp = temp * temp % mod;
		power >>= 1;
	}
	return (int) ans;
}

int calculate(int x, int y) {
	if (x == 0 || y == 0) {
		return 1;
	}
	if (x == 1 || y == 1) {
		return x + y;
	}
	return ((long long) fac[x + y] * facInv[x] % mod) * facInv[y] % mod;
}

int main() {
	int t;
	scanf("%d", &t);
	fac[0] = fac[1] = 1;
	facInv[0] = facInv[1] = 1;
	while (t--) {
		int x, y;
		scanf("%d %d", &x, &y);
		int ans = quickPower(2, y - 1);
		for (int i = 2; i <= x / i; i++) {
			if (x % i == 0) {
				int count = 0;
				while (x % i == 0) {
					x /= i;
					count++;
				}
				// count个质因数放入y个数中
				// 隔板法, y-1个隔板, count个元素
				// 随机排列, 产生y个间隔, 每个间隔内元素数量为相应分配数量
				int limit = y - 1 + count;
				while (idx1 <= limit) {
					fac[idx1] = (long long) fac[idx1 - 1] * idx1 % mod;
					idx1++;
				}
				limit = std::max(y - 1, count);
				while (idx2 <= limit) {
					facInv[idx2] = (long long) facInv[idx2 - 1] * quickPower(idx2, mod - 2) % mod;
					idx2++;
				}
				ans = (long long) ans * calculate(y - 1, count) % mod;
			}
		}
		if (x > 1) {
			ans = (long long) ans * y % mod;
		}
		printf("%d\n", ans);
	}
	return 0;
}
