// http://oj.daimayuan.top/course/11/problem/552

#include "iostream"

int next[1001];
char word[1001], txt[2001];

void solve() {
	int n;
	scanf("%d", &n);
	scanf("%s", txt);
	for (int i = 0; i < n; i++) {
		word[i] = txt[n - 1 - i];
	}
	for (int i = n, limit = n << 1; i < limit; i++) {
		txt[i] = txt[i - n];
	}
	// KMP
	for (int i = 1, j = 0; i < n; i++) {
		while (j > 0 && word[i] != word[j]) {
			j = next[j - 1];
		}
		next[i] = word[i] == word[j] ? ++j : 0;
	}
	for (int i = 0, j = 0, length = n << 1; i < length; i++) {
		while (j > 0 && txt[i] != word[j]) {
			j = next[j - 1];
		}
		if (txt[i] == word[j]) {
			if (++j == n) {
				printf("YES\n");
				return;
			}
		}
	}
	printf("NO\n");
}

int main() {
	int t;
	scanf("%d", &t);
	next[0] = 0;
	while (t--) {
		solve();
	}
	return 0;
}
