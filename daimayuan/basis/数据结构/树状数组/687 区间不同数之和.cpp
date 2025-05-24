// http://oj.daimayuan.top/course/15/problem/687

#include "array"
#include "cstring"
#include "algorithm"

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

int n, *prev;
long long *nums, *ans;
std::array<int, 3> *container, *queries;

void change(int idx, long long delta) {
	while (idx <= n) {
		nums[idx] += delta;
		idx += idx & -idx;
	}
}

long long query(int idx) {
	long long ans = 0;
	while (idx) {
		ans += nums[idx];
		idx ^= idx & -idx;
	}
	return ans;
}

int main() {	// prev[i] < left, left <= i <= right
	int q;
	read(n), read(q);
	prev = new int[n + 1];
	nums = new long long[n + 1];
	ans = new long long[n + 1];
	container = new std::array<int, 3>[n + 1];
	queries = new std::array<int, 3>[q];
	memset(prev + 1, 0, sizeof(int) * n);
	for (int i = 1, num; i <= n; i++) {
		read(num);
		container[i][0] = prev[num];
		container[i][1] = i;
		container[i][2] = num;
		prev[num] = i;
		nums[i] = 0;
	}
	for (int i = 0; i < q; i++) {
		read(queries[i][0]), read(queries[i][1]);
		queries[i][2] = i;
	}
	std::sort(container + 1, container + n + 1);
	std::sort(queries, queries + q);
	for (int i = 0, j = 1; i < q; i++) {
		int &left = queries[i][0], &right = queries[i][1];
		while (j <= n && container[j][0] < left) {
			change(container[j][1], container[j][2]);
			j++;
		}
		ans[queries[i][2]] = query(right) - query(left - 1);
	}
	for (int i = 0; i < q; i++) {
		write(ans[i]);
	}
	return 0;
}
