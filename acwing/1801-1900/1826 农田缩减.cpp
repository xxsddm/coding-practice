// https://www.acwing.com/problem/content/1828/

#include "algorithm"
#include "iostream"

using namespace std;

int main() {
	int N;
	scanf("%d", &N);
	pair<int, int> containerX[N], containerY[N];
	for (int i = 0; i < N; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		containerX[i].first = x, containerX[i].second = y;
		containerY[i].first = y, containerY[i].second = x;
	}
	sort(containerX, containerX + N);
	sort(containerY, containerY + N);
	int ans = (containerX[N - 1].first - containerX[0].first) *
	          (containerY[N - 1].first - containerY[0].first);
	if (containerX[0].second == containerY[0].first) {
		ans = min(ans, (containerX[N - 1].first - containerX[1].first) *
		          (containerY[N - 1].first - containerY[1].first));
	} else if  (containerX[0].second == containerY[N - 1].first) {
		ans = min(ans, (containerX[N - 1].first - containerX[1].first) *
		          (containerY[N - 2].first - containerY[0].first));
	} else {
		ans = min(ans, (containerX[N - 1].first - containerX[1].first) *
		          (containerY[N - 1].first - containerY[0].first));
	}
	if (containerX[N - 1].second == containerY[0].first) {
		ans = min(ans, (containerX[N - 2].first - containerX[0].first) *
		          (containerY[N - 1].first - containerY[1].first));
	} else if  (containerX[N - 1].second == containerY[N - 1].first) {
		ans = min(ans, (containerX[N - 2].first - containerX[0].first) *
		          (containerY[N - 2].first - containerY[0].first));
	} else {
		ans = min(ans, (containerX[N - 2].first - containerX[0].first) *
		          (containerY[N - 1].first - containerY[0].first));
	}
	if (containerY[0].second == containerX[0].first) {
		ans = min(ans, (containerX[N - 1].first - containerX[1].first) *
		          (containerY[N - 1].first - containerY[1].first));
	} else if (containerY[0].second == containerX[N - 1].first) {
		ans = min(ans, (containerX[N - 2].first - containerX[0].first) *
		          (containerY[N - 1].first - containerY[1].first));
	} else {
		ans = min(ans, (containerX[N - 1].first - containerX[0].first) *
		          (containerY[N - 1].first - containerY[1].first));
	}
	if (containerY[N - 1].second == containerX[0].first) {
		ans = min(ans, (containerX[N - 1].first - containerX[1].first) *
		          (containerY[N - 2].first - containerY[0].first));
	} else if (containerY[N - 1].second == containerX[N - 1].first) {
		ans = min(ans, (containerX[N - 2].first - containerX[0].first) *
		          (containerY[N - 2].first - containerY[0].first));
	} else {
		ans = min(ans, (containerX[N - 1].first - containerX[0].first) *
		          (containerY[N - 2].first - containerY[0].first));
	}
	printf("%d", ans);
}
