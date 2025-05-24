// https://www.luogu.com.cn/problem/P2827

#include "queue"
#include "algorithm"
#include "iostream"

using namespace std;

typedef long long ll;

int main() {
	int n, m, t;
	ll q, u, v, delta = 0;
	queue<ll> container[3];	// 三个非减队列
	scanf("%d %d %lld %lld %lld %d", &n, &m, &q, &u, &v, &t);
	ll nums[n], minNum = - (ll) q * m - 1;
	for (int i = 0; i < n; i++) {
		scanf("%lld", &nums[i]);
	}
	sort(nums, nums + n, [](ll & num1, ll & num2) -> bool {
		return num1 > num2;
	});
	for (ll &num : nums) {
		container[0].push(num);
	}
	for (int time = 1; time <= m; time++, delta += q) {
		ll maxNum = minNum;
		int idx = -1;
		for (int i = 0; i < 3; i++) {
			if (!container[i].empty() && container[i].front() > maxNum) {
				maxNum = container[i].front();
				idx = i;
			}
		}
		maxNum += delta;
		container[idx].pop();
		if (time % t == 0) {
			printf("%lld ", maxNum);
		}
		ll temp = maxNum * u / v;
		// 其余元素+q, 可视为当前分割元素-q
		// 全部元素暂时不考虑变化增长部分, 则无需修改队列内元素
		container[1].push(temp - delta - q);
		container[2].push(maxNum - temp - delta - q);
	}
	cout << endl;
	priority_queue<pair<ll, int>> pq;
	for (int i = 0; i < 3; i++) {
		if (!container[i].empty()) {
			pq.emplace(container[i].front(), i);
			container[i].pop();
		}
	}
	for (int i = 1; i <= n + m; i++) {
		pair<ll, int> temp = pq.top();
		pq.pop();
		if (!container[temp.second].empty()) {
			pq.emplace(container[temp.second].front(), temp.second);
			container[temp.second].pop();
		}
		if (i % t == 0) {
			printf("%lld ", temp.first + delta);
		}
	}
	return 0;
}