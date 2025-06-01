// http://oj.daimayuan.top/course/15/problem/686

#include "array"
#include "algorithm"
#include "unordered_map"

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

int length2;
int *nums2, *ans, *tree;
std::pair<int, int> *nums;
std::array<int, 4> *container;

void change(int idx) {
	while (idx <= length2) {
		tree[idx]++;
		idx += idx & -idx;
	}
}

int query(int idx) {
	int cumsum = 0;
	while (idx) {
		cumsum += tree[idx];
		idx ^= idx & -idx;
	}
	return cumsum;
}

int main() {
	int n, q;
	read(n), read(q);
	nums2 = new int[n + 1];
	ans = new int[q];
	nums = new std::pair<int, int>[n + 1];
	container = new std::array<int, 4>[q << 2];
	for (int i = 1; i <= n; i++) {
		read(nums[i].first), read(nums[i].second);
		nums2[i] = nums[i].second;
	}
	for (int i = 0, idx = 0, x1, x2, y1, y2; i < q; i++) {
		read(x1), read(x2), read(y1), read(y2);
		container[idx++] = {x1 - 1, y1 - 1, i, 1};
		container[idx++] = {x1 - 1, y2, i, -1};
		container[idx++] = {x2, y1 - 1, i, -1};
		container[idx++] = {x2, y2, i, 1};
		ans[i] = 0;
	}
	std::sort(nums2, nums2 + n + 1);
	length2 = std::unique(nums2 + 1, nums2 + n + 1) - nums2 - 1;
	tree = new int[length2 + 1];
	std::unordered_map<int, int> y2idx;
	for (int i = 1; i <= length2; i++) {
		y2idx[nums2[i]] = i;
		tree[i] = 0;
	}
	std::sort(nums + 1, nums + n + 1);
	std::sort(container, container + (q << 2), [&] (auto & p1, auto & p2) -> bool {
		if (p1[0] != p2[0]) {
			return p1[0] < p2[0];
		}
		return p1[1] < p2[1];
	});
	for (int i = 0, idx = 1, prev = 0, limit = q << 2; i < limit; i++) {
		int &upper = container[i][0];
		while (idx <= n && nums[idx].first <= upper) {
			change(y2idx[nums[idx].second]);
			idx++;
		}
		int loc = (i && container[i][1] == container[i - 1][1]) ? prev :
		          (std::upper_bound(nums2 + 1, nums2 + length2 + 1, container[i][1]) - nums2 - 1);
		ans[container[i][2]] += container[i][3] * query(loc);
		prev = loc;
	}
	for (int i = 0; i < q; i++) {
		write(ans[i]);
	}
	return 0;
}
