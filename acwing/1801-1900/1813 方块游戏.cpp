// https://www.acwing.com/problem/content/description/1815/

#include "cstring"
#include "iostream"

using namespace std;

int main() {
	int N, counter[26];
	memset(counter, 0, sizeof(counter));
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		string word1, word2;
		int counter1[26], counter2[26];
		memset(counter1, 0, sizeof(counter1));
		memset(counter2, 0, sizeof(counter2));
		cin >> word1 >> word2;
		for (char &c : word1) {
			counter1[c - 'a']++;
		}
		for (char &c : word2) {
			counter2[c - 'a']++;
		}
		for (int j = 0; j < 26; j++) {
			counter[j] += max(counter1[j], counter2[j]);
		}
	}
	for (int &count : counter) {
		printf("%d\n", count);
	}
	return 0;
}
