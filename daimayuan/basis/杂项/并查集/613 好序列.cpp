// http://oj.daimayuan.top/course/15/problem/613

#include "unordered_map"
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

const int length = 200001;
int nums[length], left[length], right[length];

bool dfs(int start, int end) {
	if (start >= end) {
		return true;
	}
	for (int i = start, j = end; i <= j; i++, j--) {
		if (left[i] < start && right[i] > end) {
			return dfs(start, i - 1) && dfs(i + 1, end);
		}
		if (left[j] < start && right[j] > end) {
			return dfs(start, j - 1) && dfs(j + 1, end);
		}
	}
	return false;
}

int main() {
	int T;
	read(T);
	while (T--) {
		int n;
		read(n);
		for (int i = 0; i < n; i++) {
			read(nums[i]);
		}
		std::unordered_map<int, int> memo;
		for (int i = 0, prev; i < n; i++) {
			int &num = nums[i];
			if (memo.count(num)) {
				prev = memo[num];
				left[i] = prev;
				right[prev] = i;
			} else {
				left[i] = -1;
			}
			memo[num] = i;
			right[i] = n;
		}
		puts(dfs(0, n - 1) ? "non-boring" : "boring");
	}
	return 0;
}