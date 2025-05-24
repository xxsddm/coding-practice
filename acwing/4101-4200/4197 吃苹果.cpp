// https://www.acwing.com/problem/content/4200/

#include "iostream"

using namespace std;

int main() {
	int n, h;
	cin >> n >> h;
	int ans = n;
	for (int i = 0; i < n; i++) {
		int a;
		cin >> a;
		if (a > h) {
			ans++;
		}
	}
	cout << ans;
}
