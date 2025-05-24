// https://www.acwing.com/problem/content/149/

#include "queue"
#include "cstring"
#include "iostream"

using namespace std;

int main() {
	int n, K, ans = 0;
	scanf("%d %d", &n, &K);
	int nums[n + 1], left[n + 1], right[n + 1];
	bool used[n];
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
	memset(used, false, sizeof(used));
	for (int i = 0; i < n; i++) {
		scanf("%d", &nums[i]);
	}
	for (int i = 0; i <= n; i++) {
		left[i] = i - 1;
		right[i] = i + 1;
	}
	for (int i = n - 1; i > 0; i--) {
		nums[i] -= nums[i - 1];
		pq.emplace(nums[i], i);
	}
	nums[0] = nums[n] = 1 << 30;
	while (K) {
		// 使用当前最短线段则相邻两段删除
		// 且修改当前线段位置后重新加入, 使可选择相邻两段
		pair<int, int> p = pq.top();
		pq.pop();
		int num = p.first, idx = p.second;
		if (used[idx]) {
			continue;
		}
		K--;
		ans += num;
		int l = left[idx], r = right[idx];
		if (l >= 0 && r <= n) {
			nums[idx] = nums[l] + nums[r] - num;
			pq.emplace(nums[idx], idx);
			// 移除l, r(类比链表删除节点)
			left[right[l]] = left[l], right[left[l]] = right[l], used[l] = true;
			left[right[r]] = left[r], right[left[r]] = right[r], used[r] = true;
		}
	}
	printf("%d", ans);
	return 0;
}
