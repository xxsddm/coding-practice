// https://www.acwing.com/problem/content/1980/

#include "algorithm"
#include "cstring"
#include "iostream"

using namespace std;

int main() {
	int N, ans = 0;
	scanf("%d", &N);
	int counter[N], diff = 0;
	pair<int, int> containerA[N], containerB[N];
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &containerA[i].first, &containerB[i].first);
		containerA[i].second = i, containerB[i].second = i;
	}
	sort(containerA, containerA + N);
	sort(containerB, containerB + N);
	memset(counter, 0, sizeof(counter));
	for (int i = 0; i < N; i++) {
		// 当前点对应相同线段, 且起点终点前方的其他起点终点对应线段组合相同
		if (diff == 0 && containerA[i].second == containerB[i].second) {
			ans++;
		}
		if (++counter[containerA[i].second] == 0) {
			diff--;
		} else {
			diff++;
		}
		if (--counter[containerB[i].second] == 0) {
			diff--;
		} else {
			diff++;
		}
	}
	printf("%d", ans);
	return 0;
}
