// http://oj.daimayuan.top/course/15/problem/781

#include "array"
#include "algorithm"
#include "iostream"

using namespace std;

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

int numstk[20];

template <typename T>
inline void write(T x) {
	int tempLen = 0;
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	while (x > 9) {
		numstk[tempLen++] = x % 10;
		x /= 10;
	}
	numstk[tempLen++] = x;
	for (int i = tempLen - 1; i >= 0; i--) {
		putchar(numstk[i] ^ 48);
	}
	putchar('\n');
}

int inf = 1 << 30, *minnum, *ans;
pair<int, int> *nums;
array<int, 4> *queries;

void change(int cur, int start, int end, int idx, int val) {
	if (start == end) {
		minnum[cur] = val;
		return;
	}
	int mid = (start + end) >> 1;
	int next1 = cur << 1, next2 = next1 ^ 1;
	if (idx <= mid) {
		change(next1, start, mid, idx, val);
	} else {
		change(next2, mid + 1, end, idx, val);
	}
	minnum[cur] = min(minnum[next1], minnum[next2]);
}

int query(int cur, int start, int end, int left, int right, int val) {
	if (left <= start && right >= end) {
		return minnum[cur];
	}
	if (minnum[cur] == inf) {
		return inf;
	}
	int mid = (start + end) >> 1;
	int next1 = cur << 1, next2 = next1 ^ 1;
	if (right <= mid) {
		return query(next1, start, mid, left, right, val);
	} else if (left > mid) {
		return query(next2, mid + 1, end, left, right, val);
	}
	return min(query(next1, start, mid, left, right, val),
	           query(next2, mid + 1, end, left, right, val));
}

int main() {
	int n, q;
	read(n), read(q);
	minnum = new int[n << 2], ans = new int[q];
	nums = new pair<int, int>[n];
	queries = new array<int, 4>[q];
	for (int i = 0; i < n; i++) {
		read(nums[i].first);
		nums[i].second = i + 1;
	}
	for (int i = 0; i < q; i++) {
		read(queries[i][1]), read(queries[i][2]), read(queries[i][0]);
		queries[i][3] = i;
	}
	sort(nums, nums + n);
	sort(queries, queries + q);
	for (int i = 1, limit = n << 2; i < limit; i++) {
		minnum[i] = inf;
	}
	for (int i = q - 1, j = n - 1; i >= 0; i--) {
		auto &[x, left, right, idx] = queries[i];
		while (j >= 0 && nums[j].first >= x) {
			change(1, 1, n, nums[j].second, nums[j].first);
			j--;
		}
		ans[idx] = query(1, 1, n, left, right, x);
		if (ans[idx] == inf) {
			ans[idx] = -1;
		}
	}
	for (int i = 0; i < q; i++) {
		write(ans[i]);
	}
	return 0;
}