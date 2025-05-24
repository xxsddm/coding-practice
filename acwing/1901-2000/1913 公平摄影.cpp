// https://www.acwing.com/problem/content/description/1915/

#include "algorithm"
#include "cstring"
#include "iostream"

using namespace std;

int main() {
	int N, sameLen = 0, maxLen = 0;
	scanf("%d", &N);
	pair<int, int> container[N];
	for (int i = 0; i < N; i++) {
		char kind[2];
		scanf("%d %s", &container[i].first, kind);
		container[i].second = kind[0] == 'G' ? -1 : 1;
	}
	sort(container, container + N);

	for (int prev = 0, length = 0, end = 0; end < N; end++) {	// 相同元素最大长度
		if (container[end].second == prev) {
			length += container[end].first - container[end - 1].first;
			sameLen = max(sameLen, length);
		} else {
			prev = container[end].second;
			length = 0;
		}
	}

	for (int i = 1; i < N; i++) {	// 元素数量相同即区间和为0
		container[i].second += container[i - 1].second;
	}
	int start[2 * N + 1];
	memset(start, -1, sizeof(start));
	start[0 + N] = container[0].first;
	for (int i = 0; i < N; i++) {
		int key = container[i].second + N;
		if (start[key] != -1) {
			maxLen = max(maxLen, container[i].first - start[key]);
		} else if (i != N - 1) {
			start[key] = container[i + 1].first;
		}
	}

	printf("%d", max(maxLen, sameLen));
	return 0;
}