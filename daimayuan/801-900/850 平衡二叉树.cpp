// http://oj.daimayuan.top/course/10/problem/850

#include "cstring"
#include "iostream"

int mod = 1e9 + 7, minnum[17], maxnum[17];	// 记录树高的相应最小最大节点数
int counter[17][20001];	// counter[树高][节点数] -> 组合数

int dfs(int height, int num) {
	if (counter[height][num] != -1) {
		return counter[height][num];
	}
	if (num > maxnum[height] || num < minnum[height]) {
		counter[height][num] = 0;
		return 0;
	}
	int count = 0, temp = num - 1;
	for (int i = minnum[height - 2], limit = std::min(temp, maxnum[height - 2]); i <= limit; i++) {
		count = (count + (((long long) dfs(height - 2, i) * dfs(height - 1, temp - i) % mod) << 1) % mod) % mod;

	}
	for (int i = minnum[height - 1], j = temp - i; i < j; i++, j--) {
		count = (count + (((long long) dfs(height - 1, i) * dfs(height - 1, j) % mod) << 1) % mod) % mod;
	}
	if ((temp & 1) == 0) {
		count = (count + ((long long) dfs(height - 1, temp >> 1) * dfs(height - 1, temp >> 1) % mod)) % mod;
	}
	counter[height][num] = count;
	return count;
}

int main() {
	int T;
	scanf("%d", &T);
	memset(counter, -1, sizeof(counter));
	memset(counter[0], 0, sizeof(counter[0]));
	memset(counter[1], 0, sizeof(counter[1]));
	memset(counter[2], 0, sizeof(counter[2]));
	counter[0][0] = 1;
	counter[1][1] = 1;
	counter[2][2] = 2;
	counter[2][3] = 1;
	minnum[0] = 0, minnum[1] = 1;
	maxnum[0] = 0, maxnum[1] = 1;
	for (int i = 2; i < 17; i++) {
		minnum[i] = minnum[i - 1] + minnum[i - 2] + 1;
		maxnum[i] = (1 << i) - 1;
	}
	for (int i = 0, n; i < T; i++) {
		scanf("%d", &n);
		int ans = 0;
		for (int j = 0; j < 17; j++) {
			if (n < minnum[j]) {
				break;
			}
			if (n > maxnum[j]) {
				continue;
			}
			ans = (ans + dfs(j, n)) % mod;
		}
		printf("%d\n", ans);
	}
	return 0;
}
