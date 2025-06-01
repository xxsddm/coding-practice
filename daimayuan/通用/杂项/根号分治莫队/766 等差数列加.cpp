// http://oj.daimayuan.top/course/15/problem/766

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

int numstk[30];

template <typename T>
inline void write(T x) {
	int length = 0;
	while (x > 9) {
		numstk[length++] = x % 10;
		x /= 10;
	}
	numstk[length++] = x;
	for (int i = length - 1; i >= 0; i--) {
		putchar(numstk[i] ^ 48);
	}
	putchar('\n');
}

long long *nums, **memo;

int main() {	// 根号分治
	int n, q;
	read(n), read(q);
	nums = new long long[n + 1];
	memset(nums + 1, 0, sizeof(long long) * n);
	int left = 1, right = n;
	while (left <= right) {
		int mid = (left + right) >> 1;
		if (mid < n / mid) {
			left = mid + 1;
		} else if (mid > n / mid) {
			right = mid - 1;
		} else {
			left = mid + 1;
			break;
		}
	}
	int length = left;
	memo = new long long*[length];
	for (int i = 0; i < length; i++) {
		memo[i] = new long long[length];
		memset(memo[i], 0, sizeof(long long) * length);
	}
	for (int i = 0, op, x, y, d; i < q; i++) {
		read(op), read(x);
		if (op == 1) {
			read(y), read(d);
			if (x < length) {
				// 不超过根号n的记录操作
				memo[x][y] += d;
			} else {
				// 超过根号n的暴力处理
				for (int i = y; i <= n; i += x) {
					nums[i] += d;
				}
			}
		} else {
			long long ans = nums[x];
			// 枚举该位置更新步长及其模
			for (int i = 1; i < length; i++) {
				ans += memo[i][x % i];
			}
			write(ans);
		}
	}
	return 0;
}