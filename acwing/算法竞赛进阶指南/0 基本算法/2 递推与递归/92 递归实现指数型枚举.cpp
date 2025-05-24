// https://www.acwing.com/problem/content/94/

#include "iostream"

using namespace std;

int main() {
	int n;
	cin >> n;
	for (int i = 0, all = (1 << n) - 1; i <= all; i++) {
		for (int j = 1, temp = 1; j <= n; j++, temp <<= 1) {
			if (temp & i) {
				cout << j << ' ';
			}
		}
		cout << endl;
	}
	return 0;
}