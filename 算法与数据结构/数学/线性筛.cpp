#include "cstring"
#include "iostream"

int *primes;
bool *visited;

int main() {	// 线性筛
	int maxnum, length = 0;
	scanf("%d", &maxnum);
	primes = new int[maxnum + 1];
	visited = new bool[maxnum + 1];
	memset(visited, false, sizeof(bool) * (maxnum + 1));
	visited[0] = visited[1] = true;
	for (int i = 2; i <= maxnum; i++) {
		if (!visited[i]) {
			primes[length++] = i;
			printf("%d ", i);
		}
		for (int j = 0; j < length; j++) {
			if ((long long) i * primes[j] > maxnum) {
				break;
			}
			visited[i * primes[j]] = true;
			if (i % primes[j] == 0) {
				break;
			}
		}
	}
	return 0;
}

