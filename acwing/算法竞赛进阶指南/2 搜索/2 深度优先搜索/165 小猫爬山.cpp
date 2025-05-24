// https://www.acwing.com/problem/content/167/

#include "algorithm"
#include "iostream"

using namespace std;

int N, W, ans, *nums, *rest;

void backtrack(int idx, int length) {
	if (length >= ans) {
		return;
	}
	if (idx == N) {
		ans = length;
		return;
	}
	int &num = nums[idx];
	for (int i = 0; i < length; i++) {
		if (num <= rest[i]) {
			rest[i] -= num;
			backtrack(idx + 1, length);
			rest[i] += num;
		}
	}
	rest[length] = W - num;
	backtrack(idx + 1, length + 1);
}

int main() {
	scanf("%d %d", &N, &W);
	ans = N;
	nums = new int[N], rest = new int[N];
	for (int i = 0; i < N; i++) {
		scanf("%d", &nums[i]);
	}
	sort(nums, nums + N, [] (int &a, int &b) -> bool {
		return a > b;
	});
	backtrack(0, 0);
	printf("%d", ans);
	return 0;
}
