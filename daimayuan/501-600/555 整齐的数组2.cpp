// http://oj.daimayuan.top/problem/555

#include "cstring"
#include "iostream"

using namespace std;

int visited[2000001], counter[2000001];

int main() {
	int t, n;
	int round = 1, add = 1000000, nums[40];
	scanf("%d", &t);
	memset(visited, 0, sizeof(visited));
	while (t--) {
		scanf("%d", &n);
		int limit = n >> 1;
		for (int i = 0; i < n; i++) {
			scanf("%d", &nums[i]);
			nums[i] += add;
		}
		bool skip = false;
		for (int i = 0; i < n; i++) {
			int num = nums[i];
			if (visited[num] < round) {
				visited[num] = round;
				counter[num] = 0;
			}
			if (++counter[num] == limit) {
				skip = true;
				break;
			}
		}
		round++;
		if (skip) {
			printf("-1\n");
			continue;
		}
		for (int k = add << 1; k > 0; k--) {	// 暴力枚举
			for (int i = 0; i < n; i++) {
				int num = nums[i] % k;
				if (visited[num] < round) {
					visited[num] = round;
					counter[num] = 0;
				}
				if (++counter[num] == limit) {
					skip = true;
					break;
				}
			}
			round++;
			if (skip) {
				printf("%d\n", k);
				break;
			}
		}
	}
	return 0;
}
