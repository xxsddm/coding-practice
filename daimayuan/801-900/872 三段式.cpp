// http://oj.daimayuan.top/course/11/problem/872

#include "iostream"

template <typename T>
inline void read(T &x) {
	x = 0;
	bool neg = false;
	char c = getchar();
	while (c < 48 || c > 57) {
		if (c == '-') {
			neg = true;
		}
		c = getchar();
	}
	while (c >= 48 && c <= 57) {
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = getchar();
	}
	if (neg) {
		x = -x;
	}
}

int *nums;

int main() {
	int n;
	read(n);
	nums = new int[n];
	long long total = 0;
	for (int i = 0; i < n; i++) {
		read(nums[i]);
		total += nums[i];
	}
	if (total % 3) {
		printf("0");
		return 0;
	}
	long long ans = 0, cumsum = 0;
	long long first = total / 3, second = first << 1;
	for (int i = 0, count = 0, limit = n - 1; i < limit; i++) {
		cumsum += nums[i];
		if (cumsum == second) {
			ans += count;
		}
		if (cumsum == first) {
			count++;
		}
	}
	printf("%lld", ans);
	return 0;
}
