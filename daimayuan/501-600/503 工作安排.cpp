// http://oj.daimayuan.top/course/10/problem/503

#include "queue"
#include "algorithm"
#include "iostream"

using namespace std;

int main() {
	int N, length = 0;
	scanf("%d", &N);
	pair<int, int> nums[N];
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &nums[length].first, &nums[length].second);
		if (nums[length].first) {
			length++;
		}
	}
	sort(nums, nums + length);
	priority_queue<int, vector<int>, greater<>> pq;
	long long ans = 0;
	for (int i = 0; i < length; i++) {
		int &d = nums[i].first, &p = nums[i].second;
		if (d > (int) pq.size()) {
			ans += p;
			pq.push(p);
		} else if (p > pq.top()) {
			ans -= pq.top();
			ans += p;
			pq.pop();
			pq.push(p);
		}
	}
	printf("%lld", ans);
	return 0;
}
