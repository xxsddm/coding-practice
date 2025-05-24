// https://www.acwing.com/problem/content/description/138/

#include "stack"
#include "algorithm"
#include "iostream"

using namespace std;

int main() {
	int n, maxnum = 0x7fffffff, minnum = - maxnum;
	scanf("%d", &n);
	pair<int, int> nums[n], left[n], right[n], ans[n];	// 左右单调栈
	stack<pair<int, int>> container;
	for (int i = 0; i < n; i++) {
		scanf("%d", &nums[i].first);
		nums[i].second = i;
		left[i].first = minnum;
		right[i].first = maxnum;
	}
	sort(nums, nums + n);	// 对原数组排序后, 排序后左右两侧最近元素差值即为其原是索引对应答案
	for (int i = n - 1; i >= 0; i--) {	// 左侧最近(大)元素
		int num = nums[i].first, idx = nums[i].second;
		while (!container.empty() && idx < container.top().second) {
			int tempidx = container.top().second;
			container.pop();
			left[tempidx].first = num;
			left[tempidx].second = idx;
		}
		container.push(nums[i]);
	}
	container = stack<pair<int, int>> ();
	for (int i = 0; i < n; i++) {	// 右侧最近(小)元素
		int num = nums[i].first, idx = nums[i].second;
		while (!container.empty() && idx < container.top().second) {
			int tempidx = container.top().second;
			container.pop();
			right[tempidx].first = num;
			right[tempidx].second = idx;
		}
		container.push(nums[i]);
	}
	for (int i = 0; i < n; i++) {
		int num = nums[i].first, idx = nums[i].second;
		if (idx == 0) {
			continue;
		}
		ans[idx].first = maxnum;
		if (left[idx].first != minnum) {
			ans[idx].first = num - left[idx].first;
			ans[idx].second = left[idx].second + 1;
		}
		if (right[idx].first != maxnum && right[idx].first - num < ans[idx].first) {
			ans[idx].first = right[idx].first - num;
			ans[idx].second = right[idx].second + 1;
		}
	}
	for (int i = 1; i < n; i++) {
		printf("%d %d\n", ans[i].first, ans[i].second);
	}
	return 0;
}
