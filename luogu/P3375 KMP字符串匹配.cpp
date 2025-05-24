// https://www.luogu.com.cn/problem/P3375

#include "cstring"
#include "iostream"

int *next;
char word1[1000001], word2[1000001];

int main() {
	scanf("%s", word1);
	scanf("%s", word2);
	int length1 = strlen(word1), length2 = strlen(word2);
	next = new int[length2];
	next[0] = 0;
	for (int i = 1, j = 0; i < length2; i++) {
		while (j && word2[i] != word2[j]) {
			j = next[j - 1];
		}
		next[i] = word2[i] == word2[j] ? ++j : 0;
	}
	if (length1 >= length2) {
		for (int i = 0, j = 0; i < length1; i++) {
			while (j && word1[i] != word2[j]) {
				j = next[j - 1];
			}
			if (word1[i] == word2[j]) {
				if (++j == length2) {
					printf("%d\n", i - length2 + 2);
					j = next[length2 - 1];
				}
			}
		}
	}
	for (int i = 0; i < length2; i++) {
		printf("%d ", next[i]);
	}
	return 0;
}