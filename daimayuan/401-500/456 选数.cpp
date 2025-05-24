// http://oj.daimayuan.top/course/10/problem/456

#include "cstring"
#include "iostream"

using namespace std;

int main() {
	int n;
	scanf("%d", &n);
	int nums[n + 1];
	nums[0] = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &nums[i]);
	}
	for (int i = 1; i <= n; i++) {
		nums[i] = (nums[i] + nums[i - 1]) % n;
		if (nums[i] == 0) {
			printf("%d\n", i);
			for (int j = 1; j <= i; j++) {
				printf("%d ", j);
			}
			return 0;
		}
	}
	// 若不存在前缀和余数为0, 则余数为1~n-1
	// 必然存在两个相同余数前缀和, 其相邻部分满足条件
	int visited[n];
	memset(visited, 0, sizeof(visited));
	for (int i = 1; i <= n; i++) {
		if (visited[nums[i]]) {
			printf("%d\n", i - visited[nums[i]]);
			for (int j = visited[nums[i]] + 1; j <= i; j++) {
				printf("%d ", j);
			}
			return 0;
		}
		visited[nums[i]] = i;
	}
	return 0;
}