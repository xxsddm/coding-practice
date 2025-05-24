// https://www.acwing.com/problem/content/description/1845/

#include "iostream"

using namespace std;

int main() {	// DP
	int n;
	cin >> n;
	int r[n], numLatter = 0, temp = 0;
	for (int i = 0; i < n; i++) {
		scanf("%d", &r[i]);
	}
	for (int i = 1; i < n; i++) {
		numLatter += r[i];
		temp += r[i] * i;
	}
	int ans = temp;
	for (int i = 1; i < n; i++) {
		temp = temp - numLatter + r[i - 1] * (n - 1);
		numLatter = numLatter - r[i] + r[i - 1];
		ans = min(ans, temp);
	}
	printf("%d", ans);
	return 0;
}
