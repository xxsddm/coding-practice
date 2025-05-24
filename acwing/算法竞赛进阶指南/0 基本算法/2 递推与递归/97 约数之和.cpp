// https://www.acwing.com/problem/content/description/99/

#include "iostream"

using namespace std;

int mod = 9901;

int quickPower(int num, int power) {
	int temp = num % mod, ans = 1;
	while (power) {
		if (power & 1) {
			ans = ans * temp % mod;
		}
		temp = temp * temp % mod;
		power >>= 1;
	}
	return ans;
}

// num的0~numPoly-1次幂多项式求和
int sum(int num, int numPoly) {
	if (numPoly == 1) {
		return 1;
	}
	if ((numPoly & 1) == 0) {
		return (quickPower(num, numPoly >> 1) + 1) * sum(num, numPoly >> 1) % mod;
	}
	return (sum(num, numPoly - 1) + quickPower(num, numPoly - 1)) % mod;
}

int main() {
	int A, B, S = 1;
	scanf("%d %d", &A, &B);
	if (A == 0) {
		cout << 0;
		return 0;
	}
	if (B == 0) {
		cout << 1;
		return 0;
	}

	// 对A分解质因数并计算约束的和
	// 约数的和为 各约数的(0~最高次幂)求和 的乘积
	for (int num = 2; num <= A / num; num++) {
		if (A % num == 0) {
			int count = 0;
			while (A % num == 0) {
				A /= num;
				count++;
			}
			// 计算某约数相应多项式的和
			S = S * sum(num, count * B + 1) % mod;
		}
	}
	if (A > 1) {
		S = S * sum(A, B + 1) % mod;
	}

	printf("%d", S);
	return 0;
}
