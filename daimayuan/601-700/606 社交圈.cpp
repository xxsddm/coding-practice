// http://oj.daimayuan.top/course/10/problem/606

#include "algorithm"
#include "iostream"

std::pair<int, bool> *nums;

int main() {
	int N;
	scanf("%d", &N);
	int length = N << 1, count = 0;
	nums = new std::pair<int, bool>[length];
	for (int i = 0, j = 0; i < N; i++) {
		int L, R;
		scanf("%d %d", &L, &R);
		nums[j++] = {L, true};
		nums[j++] = {R, false};
	}
	std::sort(nums, nums + length);
	bool status = true;
	long long ans = N;
	for (int i = 0; i < length; i++) {
		auto &[num, judge] = nums[i];
		if (count == 0) {
			status = judge;
			count++;
			continue;
		}
		if (judge == status) {
			count++;
		} else {
			ans += num;
			count--;
		}
	}
	printf("%lld", ans);
	return 0;
}
