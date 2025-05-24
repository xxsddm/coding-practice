// http://oj.daimayuan.top/course/10/problem/155

#include "iostream"
#include "cstring"

int k, mod = 1e9 + 7;
int counter[10001][14];

int dfs(int num, int idx) {
	if (idx == 0) {
		return 1;
	}
	if (counter[num][idx] != -1) {
		return counter[num][idx];
	}
	int ans = 0, temp1 = 1 << idx, temp2 = num - (temp1 - 1) * k;
	int start = temp2 > 0 ? (temp2 / temp1 + ((temp2 % temp1) != 0)) : 0;
	int end = std::min(k, num >> idx);
	for (int i = start, temp = num - temp1 * start; i <= end; i++, temp -= temp1) {
		ans += dfs(temp, idx - 1);
		if (ans >= mod) {
			ans -= mod;
		}
	}
	counter[num][idx] = ans;
	return ans;
}

int main() {	// 拆分数字n为各数位取1数量组合
	int n;
	scanf("%d %d", &k, &n);
	memset(counter, -1, sizeof(counter));
	printf("%d", dfs(n, 13));
	return 0;
}