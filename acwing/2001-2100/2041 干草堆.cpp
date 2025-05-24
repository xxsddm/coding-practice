// https://www.acwing.com/problem/content/2043/

#include "algorithm"
#include "iostream"
#include "cstring"

using namespace std;

int main() {
	int N, K;
	scanf("%d %d", &N, &K);
	long long cumsum = 0, nums[N];
	memset(nums, 0, sizeof(nums));
	for (int i = 0; i < K; i++) {
		int start, end;
		scanf("%d %d", &start, &end);
		nums[start - 1]++;
		if (end < N) {
			nums[end]--;
		}
	}
	for (int i = 0; i < N; i++) {
		cumsum += nums[i];
		nums[i] = cumsum;
	}
	sort(nums, nums + N);
	cout << nums[N >> 1];
	return 0;
}
