// https://www.acwing.com/problem/content/4202/

#include "iostream"
#include "vector"
#include "algorithm"
#include "unordered_map"

using namespace std;

vector<int> container;
vector<pair<int, int>> nums;

void backtrack(int idx, int cum) {
	if (idx == (int) nums.size()) {
		container.push_back(cum);
		return;
	}
	int num = nums[idx].first, limit = nums[idx].second;
	for (int i = 0, temp = cum; i <= limit; i++) {
		backtrack(idx + 1, temp);
		temp *= num;
	}
}

int bisect(int target) {
	int left = 0, right = (int) container.size() - 1;
	while (left <= right) {
		int mid = left + ((right - left) >> 1);
		if (container[mid] <= target) {
			left = mid + 1;
		} else {
			right = mid - 1;
		}
	}
	if (right == -1) {
		return -1;
	}
	return container[right];
}

int main() {
	int a, b, q;
	cin >> a >> b >> q;
	unordered_map<int, int> counterA, counterB;
	for (int i = 2; i <= a / i; i++) {
		while (a % i == 0) {
			a /= i;
			counterA[i]++;
		}
	}
	counterA[a]++;
	for (int i = 2; i <= b / i; i++) {
		while (b % i == 0) {
			b /= i;
			counterB[i]++;
		}
	}
	counterB[b]++;
	for (auto &[k, v] : counterA) {
		if (counterB.count(k)) {
			nums.emplace_back(k, min(v, counterB[k]));
		}
	}
	backtrack(0, 1);
	sort(container.begin(), container.end());
	while (q--) {
		int l, r;
		cin >> l >> r;
		int temp = bisect(r);
		if (temp < l) {
			cout << -1 << endl;
		} else {
			cout << temp << endl;
		}
	}
	return 0;
}
