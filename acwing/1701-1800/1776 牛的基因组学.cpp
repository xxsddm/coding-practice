// https://www.acwing.com/problem/content/description/1778/

#include "iostream"

using namespace std;

int main() {
	int N, M, ans = 0;
	scanf("%d %d", &N, &M);
	char container[2 * N][M];
	for (int i = 0; i < 2 * N; i++) {
		scanf("%s", container[i]);
	}
	for (int i = 0; i < M; i++) {
		int visited = 0;
		bool skip = false;
		for (int j = 0; j < N; j++) {
			visited |= 1 << (container[j][i] - 'A');
		}
		for (int j = N; j < 2 * N; j++) {
			if (visited & 1 << (container[j][i] - 'A')) {
				skip = true;
				break;
			}
		}
		if (!skip) {
			ans++;
		}
	}
	printf("%d", ans);
	return 0;
}
