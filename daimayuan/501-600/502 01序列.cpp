// http://oj.daimayuan.top/course/11/problem/502

#include "cstring"
#include "iostream"

char s[1000001];

int main() {
	int k;
	scanf("%d", &k);
	scanf("%s", s);
	int size = strlen(s);
	if (size < k) {
		printf("%d", 0);
		return 0;
	}
	long long ans = 0;
	if (k == 0) {
		int idx = 0;
		while (idx < size) {
			if (s[idx] == '1') {
				idx++;
				continue;
			}
			int start = idx;
			while (idx + 1 < size && s[idx + 1] == '0') {
				idx++;
			}
			long long temp = idx++ - start + 1;
			ans += temp + (temp * (temp - 1) >> 1);
		}
		printf("%lld", ans);
		return 0;
	}
	int length = 1, memo[size + 2];
	memset(memo, -1, sizeof(memo));
	for (int i = 0; i < size; i++) {
		if (s[i] == '1') {
			memo[length++] = i;
		}
	}
	if (length - 1 < k) {
		printf("%d", 0);
		return 0;
	}
	memo[length] = size;
	for (int i = k; i < length; i++) {
		if (memo[i] == -1) {
			break;
		}
		ans += (long long) (memo[i - k + 1] - memo[i - k]) * (memo[i + 1] - memo[i]);
	}
	printf("%lld", ans);
	return 0;
}
