// https://www.acwing.com/problem/content/description/116/

#include "algorithm"
#include "vector"
#include "iostream"

using namespace std;

vector<int> multiply(const vector<int> &container, int temp) {
	vector<int> nums;
	while (temp) {
		nums.push_back(temp % 10);
		temp /= 10;
	}
	int len1 = (int) container.size(), len2 = (int) nums.size();
	vector<int> ans(len1 + len2, 0);
	for (int i = 0; i < len2; i++) {
		int num = nums[i];
		for (int j = 0; j < len1; j++) {
			temp = num * container[j];
			ans[i + j] += temp % 10;
			ans[i + j + 1] += temp / 10;
		}
	}
	for (int i = 0, limit = (int) ans.size() - 1; i < limit; i++) {
		ans[i + 1] += ans[i] / 10;
		ans[i] %= 10;
	}
	while (ans.size() > 1 && ans.back() == 0) {
		ans.pop_back();
	}
	return ans;
}

vector<int> divide(const vector<int> &container, int num) {
	int length = (int) container.size();
	vector<int> ans(length, 0);
	for (int i = length - 1, temp = 0; i >= 0; i--) {
		temp = temp * 10 + container[i];
		ans[i] = temp / num;
		temp %= num;
	}
	while (ans.size() > 1 && ans.back() == 0) {
		ans.pop_back();
	}
	return ans;
}

bool moreThan(vector<int> &container, vector<int> &temp) {
	if (container.size() != temp.size()) {
		return container.size() > temp.size();
	}
	for (int i = (int) container.size() - 1; i >= 0; i--) {
		if (container[i] != temp[i]) {
			return container[i] > temp[i];
		}
	}
	return true;
}

int main() {	// 贪心策略, 末端计算值为 所有左值乘积/最后左右乘积 , 优先使用乘积较小值对
	int a, b, n;
	cin >> n;
	cin >> a >> b;
	vector<int> container, ans;
	pair<int, int> nums[n];
	while (a) {
		container.push_back(a % 10);
		a /= 10;
	}
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &nums[i].first, &nums[i].second);
	}
	sort(nums, nums + n, [] (auto & p1, auto & p2) -> bool {
		return p1.first * p1.second < p2.first * p2.second;
	});
	for (auto &p : nums) {
		vector<int> temp = divide(container, p.second);
		container = multiply(container, p.first);
		if (!moreThan(ans, temp)) {
			ans = temp;
		}
	}
	for (int i = (int) ans.size() - 1; i >= 0; i--) {
		printf("%d", ans[i]);
	}
	return 0;
}