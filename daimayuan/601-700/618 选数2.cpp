// http://oj.daimayuan.top/course/10/problem/618

#include "algorithm"
#include "iostream"

int N, p, q, *status;
bool *container;
std::pair<int, int> *nums;

bool check(int length) {
	long long cumsum = 0;
	for (int i = 0; i < length; i++) {
		cumsum += nums[i].first;
	}
	if ((long long) nums[length - 1].first * length * q <= cumsum * p) {
		return true;
	}
	for (int i = length; i < N; i++) {
		cumsum = cumsum - nums[i - length].first + nums[i].first;
		if ((long long) nums[i].first * length * q <= cumsum * p) {
			return true;
		}
	}
	return false;
}

int bisect(long long target, int right) {
	int left = 0;
	while (left <= right) {
		int mid = (left + right) >> 1;
		if ((long long) nums[mid].first * p < target) {
			left = mid + 1;
		} else {
			right = mid - 1;
		}
	}
	return left;
}

int main() {
	scanf("%d", &N);
	status = new int[N + 1];
	container = new bool[N];
	nums = new std::pair<int, int>[N];
	for (int i = 0; i < N; i++) {
		scanf("%d", &nums[i].first);
		nums[i].second = i;
		status[i] = 0;
	}
	std::sort(nums, nums + N);
	scanf("%d %d", &p, &q);
	int left = 1, right = N;
	while (left <= right) {
		int mid = (left + right) >> 1;
		if (check(mid)) {
			left = mid + 1;
		} else {
			right = mid - 1;
		}
	}
	int length = right;
	long long cumsum = 0;
	for (int i = 0; i < length; i++) {
		cumsum += nums[i].first;
	}
	if ((long long) nums[length - 1].first * length * q <= cumsum * p) {
		status[0] += 1;
		status[length] -= 1;
	}
	// 确定后续length-1个数, 选择可使用的最小首元素, 即确定可用范围
	for (int i = length; i < N; i++) {
		cumsum = cumsum - nums[i - length].first + nums[i].first;
		if ((long long) nums[i].first * length * q <= cumsum * p) {
			long long target = (long long) nums[i].first * length * q
			                   - (cumsum - nums[i - length + 1].first) * p;
			status[bisect(target, i - length + 1)] += 1;
			status[i + 1] -= 1;
		}
	}
	int ans = status[0] == 0;
	container[nums[0].second] = ans;
	for (int i = 1; i < N; i++) {
		status[i] += status[i - 1];
		if (status[i] == 0) {
			ans++;
			container[nums[i].second] = true;
		} else {
			container[nums[i].second] = false;
		}
	}
	printf("%d\n", ans);
	if (ans == 0) {
		return 0;
	}
	for (int i = 0; i < N; i++) {
		if (container[i]) {
			printf("%d ", i + 1);
		}
	}
	return 0;
}
