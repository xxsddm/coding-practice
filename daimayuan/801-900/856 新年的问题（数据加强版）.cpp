// http://oj.daimayuan.top/course/10/problem/856

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

int **nums, *container;

int main() {	// 即各行第二大值的最大值, 与各列最大值的最小值, 其中较小值
	int n, m;
	read(n), read(m);
	int ans = 0;
	nums = new int*[n];
	container = new int[m];
	for (int i = 0; i < n; i++) {
		nums[i] = new int[m];
		int first = 0, second = 0;
		for (int j = 0; j < m; j++) {
			read(nums[i][j]);
			if (first < nums[i][j]) {
				second = first;
				first = nums[i][j];
			} else if (second < nums[i][j]) {
				second = nums[i][j];
			}
		}
		ans = std::max(ans, second);
	}
	for (int i = 0; i < m; i++) {
		container[i] = nums[0][i];
	}
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < m; j++) {
			container[j] = std::max(container[j], nums[i][j]);
		}
	}
	for (int i = 0; i < m; i++) {
		ans = std::min(ans, container[i]);
	}
	printf("%d", ans);
	return 0;
}