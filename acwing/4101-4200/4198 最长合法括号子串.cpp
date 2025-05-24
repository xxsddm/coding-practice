// https://www.acwing.com/problem/content/4201/

#include "iostream"
#include "stack"
#include "string"

using namespace std;

int main() {
	string s;
	cin >> s;
	int length = (int) s.size(), maxLen = 0, count = 1;
	stack<int> container;
	stack<pair<int, int>> pre;
	for (int i = 0; i < length; i++) {
		if (s[i] == '(') {
			container.push(i);
			continue;
		}
		if (container.empty()) {
			continue;
		}
		int start = container.top(), temp = i + 1 - start;
		container.pop();
		while (!pre.empty() && start < pre.top().first) {
			pre.pop();
		}
		if (!pre.empty() && start == pre.top().first + 1) {
			temp += pre.top().second;
			pre.pop();
		}
		pre.push({i, temp});
		if (maxLen == temp) {
			count++;
		} else if (maxLen < temp) {
			maxLen = temp;
			count = 1;
		}
	}
	cout << maxLen << " " << count;
	return 0;
}

/**
#include "unordered_set"
#include "string"
#include "iostream"

using namespace std;

int main() {
	string s;
	cin >> s;
	int ans = 0;
	unordered_set<int> container;
	for (int i = 0, left = 0, right = 0, length = (int) s.size(); i < length; i++) {
		if (s[i] == '(') {
			left++;
		} else if (++right > left) {
			left = right = 0;
			continue;
		}
		if (left == right) {
			int temp = left << 1;
			if (temp == ans) {
				container.insert(i - ans + 1);
			} else if (temp > ans) {
				ans = temp;
				container.clear();
				container.insert(i - ans + 1);
			}
		}
	}
	for (int left = 0, right = 0, i = (int) s.size() - 1; i >= 0; i--) {
		if (s[i] == ')') {
			right++;
		} else if (++left > right) {
			left = right = 0;
			continue;
		}
		if (left == right) {
			int temp = left << 1;
			if (temp == ans) {
				container.insert(i);
			} else if (temp > ans) {
				ans = temp;
				container.clear();
				container.insert(i);
			}
		}
	}
	if (ans == 0) {
		cout << "0 1";
		return 0;
	}
	cout << ans << " " << container.size();
	return 0;
}
 */
