#include "iostream"

using namespace std;

int quickPower(int num, int power) {
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

int polySum(int num, int numPoly) {
	if (numPoly == 1) {
		return 1;
	}
	if (numPoly & 1) {
		return polySum(num, numPoly - 1) + quickPower(num, numPoly - 1);
	}
	return polySum(num, numPoly >> 1) * (quickPower(num, numPoly >> 1) + 1);
}

int main() {
	// https://www.acwing.com/problem/content/99/
	int n, ans = 1;
	cin >> n;
	if (n <= 1) {
		cout << n;
		return 0;
	}

	// 质因数分解并求和
	for (int num = 2; num <= n / num; num++) {
		if (n % num == 0) {
			int count = 0;
			while (n % num == 0) {
				n /= num;
				count++;
			}
			ans *= polySum(num, count + 1);
		}
	}
	if (n > 1) {
		ans *= polySum(n, 2);
	}

	cout << ans;
	return 0;
}