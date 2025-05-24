// https://www.acwing.com/problem/content/106/

#include "algorithm"
#include "cstring"
#include "iostream"
#define ll long long

using namespace std;

int counter[40001];

int main() {
	memset(counter, 0, sizeof(counter));
	// 记录初始位置之前和之后的数量
	int N, start = 40000, end = 0, prevcount = 0, lattcount = 0;
	ll cumsum = 0, ans;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		int idx;
		cin >> idx;
		counter[idx]++;
		start = min(start, idx);
		end = max(end, idx);
	}
	for (int i = start + 1; i <= end; i++) {
		cumsum += 1LL * (i - start) * counter[i];
		lattcount += counter[i];
	}
	ans = cumsum;
	// 移动到当前位置i, 则前面的元素距离均+1, 后面的元素距离均-1
	for (int i = start + 1; i <= end; i++) {
		prevcount += counter[i - 1];
		cumsum += prevcount - lattcount;
		lattcount -= counter[i];
		ans = min(ans, cumsum);
	}
	printf("%lld", ans);
	return 0;
}