// http://oj.daimayuan.top/course/10/problem/811

#include "cstring"
#include "iostream"

int primes[1000000];
long long cumsum[10000001];
bool visited[10000001];

int main() {
	int T;
	scanf("%d", &T);
	memset(visited, false, sizeof(visited));
	int length = 0, num = 3;
	for (int i = 2, limit = 1e7; i <= limit; i++) {
		if (!visited[i]) {
			primes[length++] = i;
		}
		for (int j = 0; j < length; j++) {
			if ((long long) i * primes[j] > limit) {
				break;
			}
			visited[i * primes[j]] = true;
			if ((i % primes[j]) == 0) {
				break;
			}
		}
	}
	cumsum[2] = 0;
	while (T--) {
		int n;
		scanf("%d", &n);
		while (num <= n) {
			cumsum[num] = cumsum[num - 1];
			if (visited[num]) {
				cumsum[num] += num;
			} else {
				cumsum[num] += num << 1;
			}
			num++;
		}
		printf("%lld\n", cumsum[n]);
	}
	return 0;
}
