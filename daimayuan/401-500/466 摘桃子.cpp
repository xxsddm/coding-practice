// http://oj.daimayuan.top/course/10/problem/466

#include "deque"
#include "unordered_map"
#include "iostream"

using namespace std;

int main() {
	// (cumsum[right] - cumsum[left - 1]) % k = right - (left - 1)
	// -> (cumsum[right] - right) % k = (cumsum[left - 1] - (left - 1)) % k
	int n, k;
	scanf("%d %d", &n, &k);
	int cumsum = 0;
	long long ans = 0;
	unordered_map<int, deque<int>> counter;
	counter[0].push_back(0);
	for (int i = 1; i <= n; i++) {
		int num;
		scanf("%d", &num);
		cumsum = (cumsum + num) % k;
		int key = (cumsum - (i % k) + k) % k;
		deque<int> &dq = counter[key];
		while (!dq.empty() && i - dq.front() >= k) {	// 注意区间长度小于k
			dq.pop_front();
		}
		ans += dq.size();
		dq.push_back(i);
	}
	printf("%lld", ans);
	return 0;
}
