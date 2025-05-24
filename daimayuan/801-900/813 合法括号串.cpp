// http://oj.daimayuan.top/course/10/problem/813

#include "algorithm"
#include "array"
#include "stack"
#include "cstring"
#include "iostream"

int n, *container;
char *word;
std::array<int, 3> *nums;

void change(int idx, int delta) {
	while (idx <= n) {
		container[idx] += delta;
		idx += idx & -idx;
	}
}

int query(int idx) {
	int ans = 0;
	while (idx) {
		ans += container[idx];
		idx ^= idx & -idx;
	}
	return ans;
}

int main() {
	int m;
	scanf("%d %d", &n, &m);
	container = new int[n + 1];
	word = new char[n + 3];
	nums = new std::array<int, 3>[m];
	memset(container, 0, sizeof(int) * (n + 1));
	int ans[m];
	scanf("%s", word + 1);
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &nums[i][0], &nums[i][1]);
		nums[i][2] = i;
	}
	// 离线, 二维计数
	sort(nums, nums + m, [&] (auto & p1, auto & p2) -> bool {
		return p1[1] < p2[1];
	});
	std::stack<int> stk;
	for (int i = 0, j = 1, total = 0; i < m; i++) {
		auto &[start, end, idx] = nums[i];
		while (j <= end) {
			if (word[j] == '(') {
				stk.push(j);
			} else if (!stk.empty()) {
				change(stk.top(), 1);
				stk.pop();
				total++;
			}
			j++;
		}
		ans[idx] = (total - query(start - 1)) << 1;
	}
	for (int i = 0; i < m; i++) {
		printf("%d\n", ans[i]);
	}
	return 0;
}
