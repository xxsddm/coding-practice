// https://www.acwing.com/problem/content/151/

#include "queue"
#include "iostream"

using namespace std;

typedef long long ll;

bool operator > (pair<ll, int> &a, pair<ll, int> &b) {
	if (a.first != b.first) {
		return a.first > b.first;
	}
	return a.second < b.second;
}

int main() {
	int n, k, maxLength = 0;
	scanf("%d %d", &n, &k);
	ll ans = 0;
	priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
	for (int i = 0; i < n; i++) {
		ll num;
		scanf("%lld", &num);
		pq.emplace(num, 0);
	}
	while ((n - 1) % (k - 1)) {
		pq.emplace(0, 0);
		n++;
	}
	while (n > 1) {
		int length = 0;
		ll temp = 0;
		for (int i = 0; i < k; i++) {
			auto p = pq.top();
			pq.pop();
			temp += p.first;
			length = max(length, p.second + 1);
		}
		pq.emplace(temp, length);
		maxLength = max(maxLength, length);
		ans += temp;
		n -= k - 1;
	}
	printf("%lld\n%d", ans, maxLength);
	return 0;
}
