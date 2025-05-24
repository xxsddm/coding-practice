// https://www.acwing.com/problem/content/141/

#include "iostream"

using namespace std;

int main() {	// Manacher
	int count = 1;
	string input;
	while (cin >> input && input != "END") {
		int length = (int) input.size() * 2 + 1, idx = 0;
		char container[length];
		container[idx++] = 'a';
		while (idx < length) {
			container[idx++] = input[idx >> 1];
			container[idx++] = 'a';
		}
		int ans = 0, radius[length];
		for (int i = 0, right = -1, center; i < length; i++) {	// 记录最右边界和相应中心
			if (i < right && right - i + 1 > radius[2 * center - i]) {	// 可以直接确定半径的情况
				radius[i] = radius[2 * center - i];
				continue;
			}
			radius[i] = i >= right ? 1 : (right - i + 1);
			while (i - radius[i] >= 0 && i + radius[i] < length
			        && container[i - radius[i]] == container[i + radius[i]]) {	// 中心扩散
				radius[i]++;
			}
			if (i + radius[i] - 1 > right) {
				center = i;
				right = i + radius[i] - 1;
			}
		}
		for (int i = 0; i < length; i++) {
			ans = max(ans, radius[i] - 1);
		}
		printf("Case %d: %d\n", count++, ans);
	}
	return 0;
}
