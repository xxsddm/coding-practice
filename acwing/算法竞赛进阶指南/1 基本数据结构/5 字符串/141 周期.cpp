// https://www.acwing.com/problem/content/143/

#include "iostream"

using namespace std;

int main() {	// KMP
	int count = 1, length;
	while (cin >> length && length) {
		printf("Test case #%d\n", count++);
		char container[length + 1];
		scanf("%s", container);
		int next[length];
		next[0] = 0;
		for (int i = 1, j = 0; i < length; i++) {
			char &temp = container[i];
			while (j && temp != container[j]) {
				j = next[j - 1];
			}
			next[i] = temp == container[j] ? ++j : 0;
			if (next[i] && subLength % (subLength - next[i]) == 0) {
				// 0~subLength-next[i]-1(最长公共前后缀以外的部分可作为循环部分)
				// 若该部分不可行则改取其最长公共前后缀依然不可行
				printf("%d %d\n", subLength, subLength / (subLength - next[k]));
			}
		}
		printf("\n");
	}
	return 0;
}
