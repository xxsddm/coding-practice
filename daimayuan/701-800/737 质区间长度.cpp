// http://oj.daimayuan.top/course/10/problem/737

#include "cstring"
#include "iostream"

int start, end, k, idx = 0, primes[100000];
bool *visited;

bool check(int size) {
	int count = 0;
	for (int i = 0, j = start; i < size; i++, j++) {
		if (!visited[j]) {
			count++;
		}
	}
	if (count < k) {
		return false;
	}
	for (int i = start + size; i <= end; i++) {
		if (!visited[i]) {
			count++;
		}
		if (!visited[i - size]) {
			count--;
		}
		if (count < k) {
			return false;
		}
	}
	return true;
}

int main() {	// 线性筛 + 二分
	scanf("%d %d %d", &start, &end, &k);
	visited = new bool[end + 1];
	memset(visited, false, sizeof(bool) * (end + 1));
	visited[1] = true;
	for (int i = 2; i <= end; i++) {
		if (!visited[i]) {
			primes[idx++] = i;
		}
		for (int j = 0; j < idx; j++) {
			if ((long long) primes[j] * i > end) {
				break;
			}
			visited[primes[j] * i] = true;
			if (i % primes[j] == 0) {
				break;
			}
		}
	}
	int left = 1, right = end - start + 1, count = 0;
	for (int i = start; i <= end; i++) {
		if (!visited[i]) {
			count++;
		}
	}
	if (count < k) {
		printf("-1");
		return 0;
	}
	while (left <= right) {
		int mid = (left + right) >> 1;
		if (check(mid)) {
			right = mid - 1;
		} else {
			left = mid + 1;
		}
	}
	printf("%d", left);
	return 0;
}
