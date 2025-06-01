// http://oj.daimayuan.top/course/15/problem/689

#include "array"
#include "cstring"
#include "algorithm"
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

int n, *nums, *ans, *minlast;
std::array<int, 3> *queries;

void change(int cur, int start, int end, int idx, int num) {
	if (start == end) {
		minlast[cur] = num;
		return;
	}
	int mid = (start + end) >> 1;
	int next1 = cur << 1, next2 = next1 ^ 1;
	if (idx <= mid) {
		change(next1, start, mid, idx, num);
	} else {
		change(next2, mid + 1, end, idx, num);
	}
	minlast[cur] = std::min(minlast[next1], minlast[next2]);
}

int query(int limit) {
	int cur = 1, start = 0;
	for (int end = n; start < end;) {
		int mid = (start + end) >> 1;
		int next1 = cur << 1, next2 = next1 ^ 1;
		if (minlast[next1] <= limit) {
			cur = next1;
			end = mid;
		} else {
			cur = next2;
			start = mid + 1;
		}
	}
	return start;
}

int main() {
	int q;
	read(n), read(q);
	nums = new int[n + 1], minlast = new int[n << 2];
	ans = new int[q];
	queries = new std::array<int, 3>[q];
	memset(minlast, 0, sizeof(int) * (n << 2));
	for (int i = 1; i <= n; i++) {
		read(nums[i]);
	}
	for (int i = 0; i < q; i++) {
		read(queries[i][0]), read(queries[i][1]);
		queries[i][2] = i;
	}
	sort(queries, queries + q, [&] (auto & p1, auto & p2) -> bool {
		return p1[1] < p2[1];
	});
	// 维护[0, n]元素最后出现位置, 扫描到right时查询 最后出现位置 < left 的[0, n]中最小值
	// 即线段树二分
	for (int i = 0, j = 0; i < q; i++) {
		int &right = queries[i][1];
		while (j < right) {
			if (nums[++j] <= n) {
				change(1, 0, n, nums[j], j);
			}
		}
		ans[queries[i][2]] = query(queries[i][0] - 1);
	}
	for (int i = 0; i < q; i++) {
		write(ans[i]);
	}
	return 0;
}
