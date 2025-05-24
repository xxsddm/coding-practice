// https://www.acwing.com/problem/content/105/

#include "unordered_map"
#include "iostream"

using namespace std;

int main() {
	unordered_map<int, int> counter;
	int n, m, ans = 0;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int a;
		scanf("%d", &a);
		counter[a] += 1;
	}
	cin >> m;
	pair<int, int> container[m];
	for (int i = 0; i < m; i++) {
		scanf("%d", &container[i].first);
	}
	for (int i = 0; i < m; i++) {
		scanf("%d", &container[i].second);
	}
	pair<int, int> ansPair = {counter[container[0].first], counter[container[0].second]};
	for (int i = 1; i < m; i++) {
		int temp1 = counter[container[i].first], temp2 = counter[container[i].second];
		if (temp1 > ansPair.first) {
			ansPair.first = temp1;
			ansPair.second = temp2;
			ans = i;
		} else if (temp1 == ansPair.first && temp2 > ansPair.second) {
			ansPair.first = temp1;
			ansPair.second = temp2;
			ans = i;
		}
	}
	cout << ans + 1;
	return 0;
}
