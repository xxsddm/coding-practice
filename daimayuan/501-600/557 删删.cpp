// http://oj.daimayuan.top/course/11/problem/557

#include "iostream"

int main() {
	int T;
	scanf("%d", &T);
	for (int t = 0; t < T; t++) {
		int length, memo = 0;
		scanf("%d", &length);
		char word[length + 1];
		scanf("%s", word);
		bool judge = true;
		for (int left = 0, right = length - 1; left < right; left++, right--) {
			if (word[left] != word[right]) {
				judge = false;
				break;
			}
		}
		if (judge) {
			printf("0\n");
			continue;
		}
		for (int i = 0; i < length; i++) {
			memo |= 1 << (word[i] - 'a');
		}
		int ans = length;
		for (int i = 0, j = 1; i < 26; i++, j <<= 1) {	// 枚举删除的字符种类
			if ((memo & j) == 0) {
				continue;
			}
			char temp = i + 'a';
			bool skip = false;
			int left = 0, right = length - 1, count = 0;
			while (left < right) {
				if (word[left] == word[right]) {
					left++, right--;
					continue;
				}
				if (word[left] == temp) {
					left++, count++;
				} else if (word[right] == temp) {
					right--, count++;
				} else {
					skip = true;
					break;
				}
			}
			if (!skip && ans > count) {
				ans = count;
			}
		}
		printf("%d\n", ans == length ? -1 : ans);
	}
	return 0;
}
