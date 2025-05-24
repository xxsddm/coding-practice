// http://oj.daimayuan.top/course/10/problem/678

#include "unordered_set"
#include "cstring"
#include "iostream"

using namespace std;

int length, half, counter[26];
char word[41];
unordered_set<string> visited;
string word1, word2;

bool dfs(int idx1, int idx2, int idx) {
	if (idx == length) {
		return true;
	}
	string key = word1 + " " + word2;
	if (visited.count(key)) {
		return false;
	}
	char &c = word[idx];
	if (idx == 0) {
		word1 += c;
		return dfs(1, 0, 1);
	}
	if (idx1 == half) {
		while (idx2 < half) {
			if (word1[idx2++] != word[idx++]) {
				visited.insert(key);
				return false;
			}
		}
		return true;
	}
	if (idx2 < idx1 && word1[idx2] == c) {
		word2 += c;
		if (dfs(idx1, idx2 + 1, idx + 1)) {
			return true;
		}
		word2.pop_back();
	}
	word1 += c;
	if (dfs(idx1 + 1, idx2, idx + 1)) {
		return true;
	}
	word1.pop_back();
	visited.insert(key);
	return false;
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%s", word);
		length = strlen(word);
		if (length & 1) {
			printf("impossible\n");
			continue;
		}
		half = length >> 1;
		bool judge = true;
		memset(counter, 0, sizeof(counter));
		for (int i = 0; i < length; i++) {
			counter[word[i] - 'a']++;
		}
		for (int i = 0; i < 26; i++) {
			if (counter[i] & 1) {
				judge = false;
				break;
			}
		}
		if (judge) {
			visited.clear();
			word1 = "";
			word2 = "";
		}
		printf(judge && dfs(0, 0, 0) ? "possible\n" : "impossible\n");
	}
	return 0;
}
