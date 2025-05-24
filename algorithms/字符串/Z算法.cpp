#include "iostream"

using namespace std;

int main() {
	string word;
	cin >> word;
	int length = (int) word.size(), z[length];
	z[0] = 0;
	for (int i = 1, left = 0, right = 0; i < length; i++) {
		if (i <= right && i + z[i - left] - 1 < right) {
			z[i] = z[i - left];
			continue;
		}
		z[i] = max(0, right - i + 1);
		while (i + z[i] < length && word[i + z[i]] == word[z[i]]) {
			z[i]++;
		}
		if (i + z[i] - 1 > right) {
			left = i;
			right = i + z[i] - 1;
		}
	}
	for (int i = 0; i < length; i++) {
		printf("%d ", z[i]);
	}
	return 0;
}
