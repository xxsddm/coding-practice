// https://www.acwing.com/problem/content/3350/

#include "cstring"
#include "iostream"

using namespace std;

int N, nums[101], counter[1001];

int calculate(int length) {
	int cumsum = 0, ans = 0;
	memset(counter, 0, sizeof(counter));
	for (int i = 1; i <= length; i++) {
		cumsum += nums[i];
		counter[nums[i]]++;
	}
	if (cumsum % length == 0 && counter[cumsum / length]) {
		ans++;
	}
	for (int i = length + 1; i <= N; i++) {
		cumsum -= nums[i - length];
		cumsum += nums[i];
		counter[nums[i - length]]--;
		counter[nums[i]]++;
		if (cumsum % length == 0 && counter[cumsum / length]) {
			ans++;
		}
	}
	return ans;
}

int main() {
	int ans = 0;
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &nums[i]);
	}
	for (int length = 1; length <= N; length++) {
		ans += calculate(length);
	}
	printf("%d", ans);
	return 0;
}
