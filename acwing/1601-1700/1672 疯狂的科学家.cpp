// https://www.acwing.com/problem/content/1674/

#include "iostream"

using namespace std;

int main() {
	int N;
	scanf("%d", &N);
	char word1[N + 1], word2[N + 1];
	scanf("%s", word1);
	scanf("%s", word2);
	int ans = 0;
	bool keep = false;
	for (int i = 0; i < N; i++) {
		if (word1[i] == word2[i]) {
			keep = false;
		} else if (!keep) {
			keep = true;
			ans++;
		}
	}
	printf("%d", ans);
	return 0;
}
