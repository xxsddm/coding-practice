// http://oj.daimayuan.top/course/10/problem/501

#include "iostream"

using namespace std;

int main() {
	int n;
	scanf("%d", &n);
	int nums[n], counter[n], ans = 1;
	for (int i = 0; i < n; i++) {
		scanf("%d", &nums[i]);
	}
	counter[0] = 1;
	for (int i = 1; i < n; i++) {
		counter[i] = min(counter[i - 1] + 1, nums[i]);
	}
	counter[n - 1] = 1;
	for (int i = n - 2; i >= 0; i--) {
		// counter[i] = min(counter[i], min(counter[i + 1] + 1, nums[i]));
		counter[i] = min(counter[i], counter[i + 1] + 1);
		ans = max(ans, counter[i]);
	}
	printf("%d", ans);
	return 0;
}
