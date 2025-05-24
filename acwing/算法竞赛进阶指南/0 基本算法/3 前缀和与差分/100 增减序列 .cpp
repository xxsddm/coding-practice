// https://www.acwing.com/problem/content/102/

#include "iostream"

using namespace std;

int main() {
	int n;
	cin >> n;
	int nums[n], countPos = 0, countNeg = 0;
	// 0~n-1原数组
	for (int i = 0; i < n; i++) {
		scanf("%d", &nums[i]);
	}
	// 1~n-1修改为差分数组, 目标即使该部分全部为0
	for (int i = n - 1; i >= 1; i--) {
		nums[i] -= nums[i - 1];
		if (nums[i] > 0) {
			countPos++;
		} else if (nums[i] < 0) {
			countNeg--;
		}
	}
	// 修改区域[l, r]即nums[l]+1 (l!=0), nums[r+1]-1 (r!=n-1)即选择一正一负搭配相消
	// 剩余选l=0或r=n-1消除
	printf("%d\n", abs(countPos - countNeg) + min(countPos, countNeg));
	// 剩余部分对0和n-1选择不同产生不同情况
	printf("%d", abs(countPos - countNeg) + 1);
	return 0;
}
