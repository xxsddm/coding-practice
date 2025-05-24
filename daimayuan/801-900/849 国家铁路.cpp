// http://oj.daimayuan.top/course/11/problem/849

#include "iostream"

int H, W, C, **nums;
long long *container;

inline void read(int &x) {
	x = 0;
	char c = getchar();
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + (c - '0');
		c = getchar();
	}
}

long long query(int idx) {
	long long ans = 1LL << 62;
	while (idx) {
		ans = std::min(ans, container[idx]);
		idx ^= idx & -idx;
	}
	return ans;
}

void change(int idx, long long num) {
	while (idx <= W) {
		if (container[idx] <= num) {
			break;
		}
		container[idx] = num;
		idx += idx & -idx;
	}
}

int main() {	// 树状数组维护前缀最小值
	read(H), read(W), read(C);
	nums = new int*[H];
	container = new long long[W + 1];
	for (int i = 0; i < H; i++) {
		nums[i] = new int[W];
		for (int j = 0; j < W; j++) {
			read(nums[i][j]);
		}
	}
	long long ans = 1LL << 62;
	for (int i = 1; i <= W; i++) {
		container[i] = ans;
	}
	// 左上右下情况
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			ans = std::min(ans, nums[i][j] + (long long) C * (i + j) + query(j + 1));
			change(j + 1, nums[i][j] - (long long) C * (i + j));
		}
	}
	for (int i = 1; i <= W; i++) {
		container[i] = 1e18;
	}
	// 左下右上情况
	for (int i = H - 1; i >= 0; i--) {
		for (int j = 0; j < W; j++) {
			ans = std::min(ans, nums[i][j] + (long long) C * (j - i) + query(j));
			change(j + 1, nums[i][j] - (long long) C * (j - i));
		}
	}
	printf("%lld", ans);
	return 0;
}
