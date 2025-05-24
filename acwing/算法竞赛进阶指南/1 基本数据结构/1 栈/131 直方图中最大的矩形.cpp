// https://www.acwing.com/problem/content/description/133/

#include "stack"
#include "iostream"

using namespace std;

int main() {
	int n;
	while (cin >> n && n) {
		int lowerLeft[n], lowerRight[n];	// 保存左, 右首个较低元素索引
		long long nums[n], ans = 0;
		stack<int> container;
		for (int i = 0; i < n; i++) {
			scanf("%lld", &nums[i]);
		}
		for (int i = 0; i < n; i++) {
			long long height = nums[i];
			while (!container.empty() && height < nums[container.top()]) {
				lowerRight[container.top()] = i;
				container.pop();
			}
			container.push(i);
		}
		while (!container.empty()) {
			lowerRight[container.top()] = n;
			container.pop();
		}
		for (int i = n - 1; i >= 0; i--) {
			long long height = nums[i];
			while (!container.empty() && height < nums[container.top()]) {
				lowerLeft[container.top()] = i;
				container.pop();
			}
			container.push(i);
		}
		while (!container.empty()) {
			lowerLeft[container.top()] = -1;
			container.pop();
		}
		for (int i = 0; i < n; i++) {
			ans = max(ans, nums[i] * (lowerRight[i] - lowerLeft[i] - 1));
		}
		printf("%lld\n", ans);
	}
	return 0;
}
