// http://oj.daimayuan.top/course/10/problem/608

#include "cstring"
#include "iostream"

int *nums, *counter, *ans;
bool *visited;

int main() {
	int M, N;
	scanf("%d %d", &M, &N);
	nums = new int[M];
	counter = new int[N + 1];
	memset(counter, 0, sizeof(int) * (N + 1));
	for (int i = 0; i < M; i++) {
		scanf("%d", &nums[i]);
		counter[nums[i]]++;
	}
	ans = new int[N];
	visited = new bool[N + 1];
	memset(visited, false, sizeof(bool) * (N + 1));
	for (int i = 0, idx = 0; i < M; i++) {	// 优先用更小的数字替换前方已填入且后续有剩余的较大数
		int &num = nums[i];
		counter[num]--;
		if (visited[num]) {
			continue;
		}
		visited[num] = true;
		while (idx >= 1 && num < ans[idx - 1] && counter[ans[idx - 1]]) {
			visited[ans[--idx]] = false;
		}
		ans[idx++] = num;
	}
	for (int i = 0; i < N - 1; i++) {
		printf("%d ", ans[i]);
	}
	printf("%d", ans[N - 1]);
	return 0;
}
