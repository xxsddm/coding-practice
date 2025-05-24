// https://www.acwing.com/problem/content/description/1998/

#include "algorithm"
#include "iostream"

using namespace std;

int N;

int bisect(const string &target, pair<string, int> *container, bool forRight) {
	int left = 0, right = N - 1;
	while (left <= right) {
		int mid = (left + right) >> 1;
		string &temp = container[mid].first;
		if (temp < target || forRight && temp == target) {
			left = mid + 1;
		} else {
			right = mid - 1;
		}
	}
	return left;
}

int main() {	// 小字典序和大字典序排序列表对比找最小位置, 大字典序和小字典序排序列表对比找最大位置
	cin >> N;
	pair<string, int> minwords[N], maxwords[N];
	int ans[N][2];
	for (int i = 0; i < N; i++) {
		string minword, maxword;
		cin >> minword;
		maxword = minword;
		sort(minword.begin(), minword.end());
		sort(maxword.begin(), maxword.end(), [&] (const char &a, const char &b) {
			return a > b;
		});
		minwords[i].first = minword, maxwords[i].first = maxword;
		minwords[i].second = i, maxwords[i].second = i;
	}
	sort(minwords, minwords + N);
	sort(maxwords, maxwords + N);
	for (int i = 0; i < N; i++) {
		int start1 = minwords[i].second, start2 = maxwords[i].second;
		int idx1 = bisect(minwords[i].first, maxwords, false), idx2 = bisect(maxwords[i].first, minwords, true);
		ans[start1][0] = idx1 + 1, ans[start2][1] = idx2;
	}
	for (int i = 0; i < N; i++) {
		cout << ans[i][0] << " " << ans[i][1] << endl;
	}
	return 0;
}
