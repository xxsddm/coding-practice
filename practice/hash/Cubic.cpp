// https://atcoder.jp/contests/abc238/tasks/abc238_g

#include "cstring"
#include "iostream"

int nextIdx = 1, mod = 1e9 + 7, move = 131;
int num2idx[1000001], counter[100000], base[100000];

int main() {	// 按质数的 (幂%3) 和 索引 构建hash
	int N, Q;
	scanf("%d %d", &N, &Q);
	int nums[N + 1];
	nums[0] = 0, base[0] = 1;
	memset(counter, 0, sizeof(counter));
	memset(num2idx, -1, sizeof(num2idx));
	for (int i = 1; i <= N; i++) {
		int num, next = nums[i - 1];
		scanf("%d", &num);
		for (int j = 2; j <= num / j; j++) {
			if (num % j == 0) {
				if (num2idx[j] == -1) {
					num2idx[j] = nextIdx;
					base[nextIdx] = (long long) base[nextIdx - 1] * move % mod;
					nextIdx++;
				}
				int count = 0;
				while (num % j == 0) {
					num /= j;
					count++;
				}
				if (count % 3 == 0) {
					continue;
				}
				int idx = num2idx[j], prev = counter[idx];
				counter[idx] = (counter[idx] + count) % 3;
				next = (next + mod + (long long) base[idx] * (counter[idx] - prev)) % mod;
			}
		}
		if (num > 1) {
			if (num2idx[num] == -1) {
				num2idx[num] = nextIdx;
				base[nextIdx] = (long long) base[nextIdx - 1] * move % mod;
				nextIdx++;
			}
			int idx = num2idx[num], prev = counter[idx];
			counter[idx] = (counter[idx] + 1) % 3;
			next = (next + mod + (long long) base[idx] * (counter[idx] - prev)) % mod;
		}
		nums[i] = next;
	}
	for (int i = 0; i < Q; i++) {
		int L, R;
		scanf("%d %d", &L, &R);
		printf(nums[R] == nums[L - 1] ? "YES\n" : "NO\n");
	}
	return 0;
}
