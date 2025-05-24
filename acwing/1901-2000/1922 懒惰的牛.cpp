// https://www.acwing.com/problem/content/1924/

#include "cstring"
#include "iostream"

using namespace std;

long long counter[1000001];

int main() {
	int N, K;
	int left = 1000001, right = -1;
	long long ans = 0;
	scanf("%d %d", &N, &K);
	memset(counter, 0, sizeof(counter));
	for (int i = 0; i < N; i++) {
		int num, idx;
		scanf("%d %d", &num, &idx);
		counter[idx] += num;
		left = min(left, idx);
		right = max(right, idx);
	}
	if (right - left <= 2 * K) {
		for (int i = left; i <= right; i++) {
			ans += counter[i];
		}
		printf("%lld", ans);
		return 0;
	}
	for (int i = left + 1; i <= right; i++) {
		counter[i] += counter[i - 1];
	}
	ans = counter[left + 2 * K] - (left == 0 ? 0 : counter[left - 1]);
	for (int start = left + 1, limit = right - 2 * K; start <= limit; start++) {
		ans = max(ans, counter[start + 2 * K] - counter[start - 1]);
	}
	printf("%lld", ans);
	return 0;
}
