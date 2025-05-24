// https://www.acwing.com/problem/content/1906/

#include "stack"
#include "cstring"
#include "algorithm"
#include "iostream"

using namespace std;

int main() {
	int N;
	scanf("%d", &N);
	int size[N];
	pair<int, int> cow[N];
	memset(size, 1, sizeof(size));
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &cow[i].first, &cow[i].second);
	}
	sort(cow, cow + N);
	stack<int> container;
	for (int i = 0; i < N; i++) {
		int v = cow[i].second;
		while (!container.empty() && v < cow[container.top()].second) {
			size[i] += size[container.top()];
			container.pop();
		}
		container.push(i);
	}
	printf("%d", container.size());
	return 0;
}
