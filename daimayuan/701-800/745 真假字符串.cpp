// http://oj.daimayuan.top/course/11/problem/745

#include "cstring"
#include "iostream"

char word1[300001], word2[300001];

int main() {
	scanf("%s", word1);
	scanf("%s", word2);
	int length = strlen(word1);
	int idx1 = 0, idx2 = 0;
	bool skip1 = false, skip2 = false;
	for (int i = 0; i < length && idx1 < length && idx2 < length; i++) {
		if (word1[idx1] == word2[idx2]) {
			idx1++, idx2++;
			continue;
		}
		if (!skip1 && (idx2 + 1 == length || word1[idx1] == word2[idx2 + 1])) {
			skip1 = true;
			idx2++;
		} else if (!skip2 && (idx1 + 1 == length || word1[idx1 + 1] == word2[idx2])) {
			skip2 = true;
			idx1++;
		} else if (!skip1 && !skip2) {
			skip1 = skip2 = true;
			idx1++, idx2++;
		} else {
			printf("%d", 0);
			return 0;
		}
	}
	printf("%d", 1);
	return 0;
}
