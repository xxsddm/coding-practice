// http://oj.daimayuan.top/course/11/problem/812

#include "cstring"
#include "iostream"

int primes[30000];
bool visited[100001], *used;

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	int idx = 0;
	used = new bool[m + 1];
	memset(visited, false, sizeof(visited));
	memset(used, false, sizeof(bool) * (m + 1));
	visited[1] = true;
	for (int i = 2, limit = 100001; i < limit; i++) {
		if (!visited[i]) {
			primes[idx++] = i;
		}
		for (int j = 0; j < idx; j++) {
			if ((long long) primes[j] * i >= limit) {
				break;
			}
			visited[primes[j] * i] = true;
			if ((i % primes[j]) == 0) {
				break;
			}
		}
	}
	for (int i = 0, num; i < n; i++) {
		scanf("%d", &num);
		for (int j = 0; j < idx; j++) {
			if (!visited[num]) {
				if (num <= m) {
					used[num] = true;
				}
				break;
			}
			int &temp = primes[j];
			if (temp > num) {
				break;
			}
			if ((num % temp) == 0) {
				used[temp] = true;
				while ((num % temp) == 0) {
					num /= temp;
				}
			}
		}
	}
	for (int i = 0; i < idx && primes[i] <= m; i++) {
		int temp = primes[i];
		if (used[temp]) {
			while (temp <= m) {
				used[temp] = true;
				temp += primes[i];
			}
		}
	}
	int ans = 0;
	for (int i = 1; i <= m; i++) {
		if (!used[i]) {
			ans++;
		}
	}
	printf("%d\n", ans);
	for (int i = 1; i <= m; i++) {
		if (!used[i]) {
			printf("%d\n", i);
		}
	}
	return 0;
}
