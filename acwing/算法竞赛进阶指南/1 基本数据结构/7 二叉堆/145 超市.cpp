// https://www.acwing.com/problem/content/147/

#include "queue"
#include "algorithm"
#include "iostream"

using namespace std;

int main() {
	int N;
	while (cin >> N) {
		int ans = 0;
		priority_queue<int, vector<int>, greater<>> pq;
		pair<int, int> nums[N];
		for (int i = 0; i < N; i++) {
			scanf("%d %d", &nums[i].second, &nums[i].first);
		}
		sort(nums, nums + N);
		for (auto &p : nums) {
			if (p.first > pq.size()) {
				ans += p.second;
				pq.push(p.second);
				continue;
			}
			if (p.second > pq.top()) {
				ans -= pq.top();
				ans += p.second;
				pq.pop();
				pq.push(p.second);
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}