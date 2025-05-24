// https://www.acwing.com/problem/content/description/1989/

#include "vector"
#include "algorithm"
#include "iostream"

using namespace std;

int main() {
	int N, loc = 0, ans = 0, count = 1;
	scanf("%d", &N);
	int length = N * 2;
	vector<pair<int, int>> container(length);
	for (int i = 0, j = 0; i < N; i++) {
		int diff;
		char dir;
		scanf("%d %c", &diff, &dir);
		if (dir == 'L') {
			container[j++] = {loc, -1};
			loc -= diff;
			container[j++] = {loc, 1};
		} else {
			container[j++] = {loc, 1};
			loc += diff;
			container[j++] = {loc, -1};
		}
	}
	sort(container.begin(), container.end());
	for (int i = 1; i < length; i++) {
		if (count >= 2 && container[i].first > container[i - 1].first) {
			ans += container[i].first - container[i - 1].first;
		}
		count += container[i].second;
	}
	printf("%d", ans);
	return 0;
}
