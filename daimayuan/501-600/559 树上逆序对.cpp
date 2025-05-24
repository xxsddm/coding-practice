// http://oj.daimayuan.top/problem/559

#include "algorithm"
#include "iostream"

int n, *container;

void change(int idx) {
	while (idx <= n) {
		container[idx] += 1;
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
	scanf("%d", &n);
	int counter[n + 1];
	std::pair<int, int> nums[n + 1];
	container = new int[n + 1];
	for (int i = 1; i <= n; i++) {
		scanf("%d", &nums[i].first);
		nums[i].second = i;
		container[i] = 0;
		counter[i] = 0;
	}
	sort(nums + 1, nums + n + 1, [] (auto & p1, auto & p2) -> bool {
		if (p1.first != p2.first) {
			return p1.first < p2.first;
		}
		return p1.second < p2.second;
	});
	// 加入节点时查找相应范围内已有子节点数(均小于该节点值)
	for (int i = 1; i <= n; i++) {
		int &idx = nums[i].second;
		for (int k = 1; k < n; k++) {
			long long start = (long long) k * (idx - 1) + 2;
			if (start > n) {
				break;
			}
			counter[k] += query(std::min(k * idx + 1, n)) - query((int) start - 1);
		}
		change(idx);
	}
	for (int k = 1; k < n; k++) {
		printf("%d ", counter[k]);
	}
	return 0;
}
