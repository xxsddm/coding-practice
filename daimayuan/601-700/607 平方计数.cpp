// http://oj.daimayuan.top/course/10/problem/607

#include "cstring"
#include "iostream"

using namespace std;

int *nums, *counter;
bool *visited;

int main() {
	int n, maxnum = 0;
	scanf("%d", &n);
	nums = new int[n];
	for (int i = 0; i < n; i++) {
		scanf("%d", &nums[i]);
		maxnum = max(maxnum, nums[i]);
	}
	counter = new int[maxnum + 1];
	visited = new bool[maxnum + 1];
	memset(counter, 0, sizeof(int) * (maxnum + 1));
	memset(visited, false, sizeof(bool) * (maxnum + 1));
	for (int i = 0; i < n; i++) {
		counter[nums[i]]++;
	}
	long long ans = 0;
	for (int i = 0; i < n; i++) {
		if (visited[nums[i]]) {
			continue;
		}
		visited[nums[i]] = true;
		long long num = (long long) nums[i] * nums[i];
		// 枚举平方数的根
		for (int root = nums[i] + 1; root <= maxnum; root++) {
			long long temp = (long long) root * root - num;
			if (temp > maxnum) {
				break;
			}
			ans += counter[nums[i]] * counter[temp];
		}
	}
	printf("%lld", ans);
	return 0;
}
