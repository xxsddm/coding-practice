// https://www.acwing.com/problem/content/96/

#include "iostream"

using namespace std;

int n;

void dfs(int idx, int used, int *nums) {
	if (idx == n) {
		for (int i = 0; i < n; i++) {
			cout << nums[i] << ' ';
		}
		cout << endl;
		return;
	}
	for (int num = 1, temp = 1; num <= n; num++, temp <<= 1) {
		if (used & temp) {
			continue;
		}
		nums[idx] = num;
		dfs(idx + 1, used ^ temp, nums);
	}
}

int main() {
	cin >> n;
	int nums[n];
	dfs(0, 0, nums);
	return 0;
}
