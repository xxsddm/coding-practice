// https://www.acwing.com/problem/content/112/

#include "algorithm"
#include "cstring"
#include "iostream"

using namespace std;

int main() {
	int C, L, ans = 0;
	cin >> C >> L;
	bool visited[C];
	pair<int, int> container[C], spf[L];
	memset(visited, false, sizeof(visited));
	for (int i = 0; i < C; i++) {
		scanf("%d %d", &container[i].first, &container[i].second);
	}
	for (int i = 0; i < L; i++) {
		scanf("%d %d", &spf[i].first, &spf[i].second);
	}
	sort(container, container + C, [] (auto & p1, auto & p2) -> bool {
		if (p1.second != p2.second) {
			return p1.second < p2.second;
		}
		return p1.first < p2.first;
	});
	sort(spf, spf + L);
	for (int i = 0; i < L; i++) {
		int num = spf[i].first, count = spf[i].second;
		for (int j = 0; j < C; j++) {
			if (visited[j]) {
				continue;
			}
			if (num <= container[j].second && num >= container[j].first) {
				ans++;
				visited[j] = true;
				if (--count == 0) {
					break;
				}
			}
		}
	}
	cout << ans;
	return 0;
}
