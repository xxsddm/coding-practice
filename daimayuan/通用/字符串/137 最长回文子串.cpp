// http://oj.daimayuan.top/course/5/problem/137

#include "iostream"

template <typename T>
inline void read(T &x) {
	x = 0;
	char c = getchar();
	while (c < 48 || c > 57) {
		c = getchar();
	}
	while (c >= 48 && c <= 57) {
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = getchar();
	}
}

int length, *word, *radius;

int main() {	// Manacher
	int n;
	read(n);
	int ans = 0;
	length = (n << 1) ^ 1;
	word = new int[length];
	radius = new int[length];
	word[0] = 1;
	for (int i = 0, idx = 1; i < n; i++) {
		read(word[idx++]);
		word[idx++] = 1;
	}
	radius[0] = 1;
	for (int i = 1, center, right = 0; i < length; i++) {
		if (i < right && i + radius[2 * center - i] <= right) {
			radius[i] = radius[2 * center - i];
			continue;
		}
		radius[i] = std::max(1, right - i + 1);
		while (i - radius[i] >= 0 && i + radius[i] < length && word[i - radius[i]] == word[i + radius[i]]) {
			radius[i]++;
		}
		if (i + radius[i] >= right) {
			center = i, right = i + radius[i] - 1;
		}
		ans = std::max(ans, radius[i]);
	}
	ans--;
	printf("%d", ans);
	return 0;
}
