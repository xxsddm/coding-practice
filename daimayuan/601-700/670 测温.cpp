// http://oj.daimayuan.top/course/10/problem/670

#include "queue"
#include "iostream"

int main() {
	int n;
	scanf("%d", &n);
	int ans = 1;
	std::deque<std::pair<int, int>> dq;
	// first单调递增, 则second单调递减才可能取到最大值
	for (int i = 0; i < n; i++) {
		int lower, upper, start = i;
		scanf("%d %d", &lower, &upper);
		while (!dq.empty() && dq.front().second > upper) {
			dq.pop_front();
		}
		if (!dq.empty()) {
			ans = std::max(ans, i - dq.front().first + 1);
			while (!dq.empty() && dq.back().second <= lower) {
				start = dq.back().first;
				dq.pop_back();
			}
		}
		dq.emplace_back(start, lower);
	}
	printf("%d", ans);
	return 0;
}
