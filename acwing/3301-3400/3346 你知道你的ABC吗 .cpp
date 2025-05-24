// https://www.acwing.com/problem/content/3349/

#include "algorithm"
#include "iostream"

using namespace std;

int main() {
	int nums[7];
	for (int i = 0; i < 7; i++) {
		scanf("%d", &nums[i]);
	}
	sort(nums, nums + 7);
	// 解方程
	printf("%d %d %d", nums[0], nums[1], nums[6] - nums[0] - nums[1]);
	return 0;
}
