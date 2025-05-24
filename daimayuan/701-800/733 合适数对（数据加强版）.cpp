// http://oj.daimayuan.top/course/10/problem/733

#include "cstring"
#include "iostream"

int length = 0, limit = 1e7, counter[10000001], primes[1000000];
bool visited[10000001];

int quickPower(int num, int power) {
	long long ans = 1, temp = num;
	while (power && temp <= limit) {
		if (power & 1) {
			ans = ans * temp;
			if (ans > limit) {
				return limit + 1;
			}
		}
		temp = temp * temp;
		power >>= 1;
	}
	if (temp > limit && power) {
		return limit + 1;
	}
	return ans;
}

int main() {
	int n, k;
	scanf("%d %d", &n, &k);
	memset(counter, 0, sizeof(counter));
	memset(visited, false, sizeof(visited));
	for (int i = 2; i <= limit; i++) {	// 素数线性筛
		if (!visited[i]) {
			primes[length++] = i;
		}
		for (int j = 0; j < length; j++) {
			if ((long long) i * primes[j] > limit) {
				break;
			}
			visited[i * primes[j]] = true;
			if (i % primes[j] == 0) {
				break;
			}
		}
	}
	long long ans = 0;
	for (int i = 0, num; i < n; i++) {
		int change = 1;
		long long match = 1;
		bool judge = true;
		scanf("%d", &num);
		for (int j = 0; j < length; j++) {
			int &prime = primes[j];
			if (prime > num) {
				break;
			}
			if (!visited[num]) {
				change *= num;
				match *= quickPower(num, k - 1);
				if (match > limit) {
					judge = false;
				}
				break;
			}
			if (num % prime == 0) {
				int count = 0;
				while (num % prime == 0) {
					num /= prime;
					count++;
				}
				count %= k;
				if (count) {
					change *= quickPower(prime, count);
					match *= quickPower(prime, k - count);
					if (match > limit) {
						judge = false;
						break;
					}
				}
			}
		}
		if (judge) {
			ans += counter[match];
			counter[change]++;
		}
	}
	printf("%lld", ans);
	return 0;
}
