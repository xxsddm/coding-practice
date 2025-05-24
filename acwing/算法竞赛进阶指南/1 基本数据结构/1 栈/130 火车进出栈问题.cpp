// https://www.acwing.com/problem/content/description/132/

#include "vector"
#include "iostream"
#include "cstring"

using namespace std;

int length = 1;
vector<int> container;
long long mod = 1e9;

void count(int start, int end, int *counter) {	// 质因数阶乘分解
	for (int i = max(2, start); i <= end; i++) {	// 查找目标范围质因数
		bool isPrime = true;
		for (int j = 2; j <= i / j; j++) {
			if (i % j == 0) {
				isPrime = false;
				break;
			}
		}
		if (isPrime) {
			container.push_back(i);
		}
	}
	for (int &prime : container) {
		int temp = prime, count = 0;
		while (end >= temp) {
			count += end / temp;
			temp *= prime;
		}
		counter[prime] += count;
	}
}

int quickPower(int num, int power) {
	if (power == 1) {
		return num;
	}
	int ans = 1, temp = num;
	while (power) {
		if (power & 1) {
			ans *= temp;
		}
		temp *= temp;
		power >>= 1;
	}
	return ans;
}

void multiply(long long *nums, int num) {
	long long add = 0;
	for (int i = 0; i < length; i++) {
		long long temp = nums[i] * num + add;
		nums[i] = temp % mod;
		add = temp / mod;
	}
	if (add) {
		nums[length++] = add;
	}
}

int main() {	// catalan数
	int n;
	scanf("%d", &n);
	int counter[2 * n + 1];
	long long ans[max(3, n / 10)];
	memset(counter, 0, sizeof(counter));
	memset(ans, 0, sizeof(ans));
	ans[0] = 1;
	// /(n!)^2
	count(1, n, counter);
	for (int &prime : container) {
		counter[prime] = - (counter[prime] << 1);
	}
	// /(n + 1)
	int temp = n + 1;
	for (int i = 2; i <= temp / i; i++) {
		while ((temp % i) == 0) {
			temp /= i;
			counter[i]--;
		}
	}
	if (temp > 1) {
		counter[temp]--;
	}
	// *(2n!)
	count(n + 1, 2 * n, counter);
	for (int &prime : container) {
		if (counter[prime]) {
			multiply(ans, quickPower(prime, counter[prime]));
		}
	}

	printf("%lld", ans[length - 1]);
	for (int i = (int) length - 2; i >= 0; i--) {
		printf("%09lld", ans[i]);
	}
	return 0;
}
