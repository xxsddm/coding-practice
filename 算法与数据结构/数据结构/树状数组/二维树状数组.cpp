// http://oj.daimayuan.top/course/15/problem/637

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

int n, m, nums[501][501];
long long container[501][501];

void change(int row, int col, long long delta) {
	for (int x = row; x <= n; x += x & -x) {
		for (int y = col; y <= m; y += y & -y) {
			container[x][y] += delta;
		}
	}
}

long long query(int row, int col) {
	long long ans = 0;
	for (int x = row; x; x ^= x & -x) {
		for (int y = col; y; y ^= y & -y) {
			ans += container[x][y];
		}
	}
	return ans;
}

int main() {
	int q;
	read(n), read(m), read(q);
	for (int i = 1, num; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			read(num);
			change(i, j, num - nums[i][j]);
			nums[i][j] = num;
		}
	}
	for (int i = 0, op, x, y, d; i < q; i++) {
		read(op), read(x), read(y);
		if (op == 1) {
			read(d);
			change(x, y, d - nums[x][y]);
			nums[x][y] = d;
		} else if (op == 2) {
			write(query(x, y));
		}
	}
	return 0;
}
