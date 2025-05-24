// http://oj.daimayuan.top/course/11/problem/855

#include "cstring"
#include "iostream"

template <typename T>
inline void read(T &x) {
	x = 0;
	char c = getchar();
	while (c < 48 || c > 57) {
		c = getchar();
	}
	while (c >= 48 && c <= 57) {
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = getchar();
	}
}

int main() {
	int n, length = 60, mod = 1e9 + 7;
	read(n);
	int limit = 0, counter[length];
	memset(counter, 0, sizeof(counter));
	for (int i = 0; i < n; i++) {
		long long num;
		read(num);
		int j = 0;
		while (num) {
			if (num & 1) {
				counter[j]++;	// 记录各位置取1次数
			}
			num >>= 1;
			j++;
		}
		if (j > limit) {
			limit = j;
		}
	}
	int ans = 0;
	for (int i = 0, temp = 1; i < limit; i++) {
		if (counter[i] && counter[i] != n) {
			ans = ans + (temp * ((long long) counter[i] * (n - counter[i]) % mod)) % mod;
			if (ans >= mod) {
				ans -= mod;
			}
		}
		temp <<= 1;
		if (temp >= mod) {
			temp -= mod;
		}
	}
	printf("%d", ans);
	return 0;
}
