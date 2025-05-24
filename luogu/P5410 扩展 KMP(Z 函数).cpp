// https://www.luogu.com.cn/problem/P5410

#include "cstring"
#include "iostream"

char word1[20000002], word2[20000002];
int *z, *z2;

int main() {
	scanf("%s", word1);
	scanf("%s", word2);
	int length1 = strlen(word1), length2 = strlen(word2);
	long long ans = length2 + 1;
	z = new int[length2], z2 = new int[length1];
	z[0] = z2[0] = 0;
	for (int i = 1, left = 0, right = 0; i < length2; i++) {
		if (i <= right && i + z[i - left] - 1 < right) {
			z[i] = z[i - left];
		} else {
			z[i] = std::max(0, right - i + 1);
			while (i + z[i] < length2 && word2[i + z[i]] == word2[z[i]]) {
				z[i]++;
			}
			if (i + z[i] - 1 > right) {
				left = i;
				right = i + z[i] - 1;
			}
		}
		ans ^= (long long) (i + 1) * (z[i] + 1);
	}
	printf("%lld\n", ans);
	ans = 0;
	for (int i = 0, limit = std::min(length1, length2); i < limit; i++) {
		if (word1[i] != word2[i]) {
			break;
		}
		ans++;
	}
	ans++;
	for (int i = 1, left = 0, right = 0; i < length1; i++) {
		if (i <= right && i + z[i - left] - 1 < right) {
			z2[i] = z[i - left];
		} else {
			z2[i] = std::max(0, right - i + 1);
			while (i + z2[i] < length1 && z2[i] < length2 && word1[i + z2[i]] == word2[z2[i]]) {
				z2[i]++;
			}
			if (i + z2[i] - 1 > right) {
				left = i;
				right = i + z2[i] - 1;
			}
		}
		ans ^= (long long) (i + 1) * (z2[i] + 1);
	}
	printf("%lld\n", ans);
	return 0;
}
