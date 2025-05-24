// http://oj.daimayuan.top/course/10/problem/741

#include "cstring"
#include "iostream"

int main() {
	int n;
	scanf("%d", &n);
	int counter[31], container[31];
	memset(counter, 0, sizeof(counter));
	for (int i = 0, num; i < n; i++) {
		scanf("%d", &num);
		int maxLen = 0, idx = 0;
		for (int j = 0, k = 1; j < 31; j++, k <<= 1) {
			if (num & k) {
				container[idx++] = j;
				maxLen = std::max(maxLen, counter[j]);
			}
		}
		for (int j = 0, temp = maxLen + 1; j < idx; j++) {
			counter[container[j]] = std::max(counter[container[j]], temp);
		}
	}
	int ans = 0;
	for (int i = 0; i < 31; i++) {
		ans = std::max(ans, counter[i]);
	}
	printf("%d", ans);
	return 0;
}
