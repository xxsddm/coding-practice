// http://oj.daimayuan.top/course/15/problem/769

#include "array"
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

int *nums, *ans, counter1[100001], *counter2;
std::array<int, 4> *query;

inline void add(int idx) {
	int temp = counter1[nums[idx]];
	counter1[nums[idx]]++;
	counter2[temp]--;
	counter2[temp + 1]++;
}

inline void remove(int idx) {
	int temp = counter1[nums[idx]];
	counter1[nums[idx]]--;
	counter2[temp]--;
	counter2[temp - 1]++;
}

int main() {
	int n, m;
	read(n);
	nums = new int[n + 1], counter2 = new int[n + 1];
	for (int i = 1; i <= n; i++) {
		read(nums[i]);
		counter2[i] = 0;
	}
	read(m);
	query = new std::array<int, 4>[m];
	ans = new int[m];
	for (int i = 0; i < m; i++) {
		read(query[i][0]), read(query[i][1]), read(query[i][2]);
		query[i][3] = i;
	}
	int block = n;
	for (int left = 1, mid; left <= block;) {
		mid = (left + block) >> 1;
		if (mid < n / mid) {
			left = mid + 1;
		} else if (mid > n / mid) {
			block = mid - 1;
		} else {
			block = mid;
			break;
		}
	}
	// 奇偶区间右边界交替排序方式
	sort(query, query + m, [&] (auto & p1, auto & p2) -> bool {
		if (p1[0] / block != p2[0] / block) {
			return p1[0] < p2[0];
		}
		int idx = p1[0] / block;
		if (idx & 1) {
			return p1[1] > p2[1];
		}
		return p1[1] < p2[1];
	});
	for (int i = 0, start = 1, end = 0; i < m; i++) {
		int &left = query[i][0], &right = query[i][1];
		while (end < right) {
			add(++end);
		}
		while (start < left) {
			remove(start++);
		}
		while (start > left) {
			add(--start);
		}
		while (end > right) {
			remove(end--);
		}
		ans[query[i][3]] = counter2[query[i][2]];
	}
	for (int i = 0; i < m; i++) {
		write(ans[i]);
	}
	return 0;
}