// https://atcoder.jp/contests/arc136/tasks/arc136_d

#include "cstring"
#include "iostream"

int *counter;

int main() {
	int N, maxnum = 0, length = 0, size = 1;
	scanf("%d", &N);
	int nums[N];
	for (int i = 0; i < N; i++) {
		scanf("%d", &nums[i]);
		if (nums[i] > maxnum) {
			maxnum = nums[i];
		}
	}
	if (maxnum == 0) {
		printf("%lld", (long long) N * (N - 1) >> 1);
		return 0;
	}
	while (maxnum) {
		length++;
		size *= 10;
		maxnum /= 10;
	}
	long long ans = 0;
	counter = new int[size];
	memset(counter, 0, sizeof(int) * size);
	for (int i = 0; i < N; i++) {
		int num = nums[i];
		bool skip = false;
		counter[num]++;
		while (num) {
			if (num % 10 > 4) {
				skip = true;
				break;
			}
			num /= 10;
		}
		if (!skip) {	// 自身相加不会进位则产生不符条件的情况
			ans--;
		}
	}
	for (int i = 1, temp = 1; i <= length; i++, temp *= 10) {	// DP
		for (int j = temp; j < size; j++) {
			if ((j / temp) % 10) {	// 并入高位相同时低位小于该数的情况
				counter[j] += counter[j - temp];
			}
		}
	}
	for (int i = 0, base = size - 1; i < N; i++) {
		ans += counter[base - nums[i]];
	}
	ans >>= 1;
	printf("%lld", ans);
	return 0;
}