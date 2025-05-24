// https://www.acwing.com/problem/content/1445/

#include "cstring"
#include "iostream"

using namespace std;

int N;

bool check(int start, int *nums, bool *visited) {
	visited[start] = true;
	int prev = start;
	for (int i = 1; i < N; i++) {
		int temp = nums[i] - prev;
		if (temp < 1 || temp > N || visited[temp]) {
			return false;
		}
		visited[temp] = true;
		prev = temp;
	}
	return true;
}

int main() {
	scanf("%d", &N);
	int nums[N];
	bool visited[N + 1];
	for (int i = 1; i < N; i++) {
		scanf("%d", &nums[i]);
	}
	for (int i = 1, limit = nums[1]; i < limit; i++) {
		memset(visited, false, sizeof(visited));
		if (check(i, nums, visited)) {
			printf("%d ", i);
			for (int j = 1, prev = i; j < N; j++) {
				prev = nums[j] - prev;
				printf("%d ", prev);
			}
			return 0;
		}
	}
	return 0;
}
