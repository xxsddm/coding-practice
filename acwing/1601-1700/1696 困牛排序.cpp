// https://www.acwing.com/problem/content/1698/

#include "iostream"

using namespace std;

int main() {
	int N;
	scanf("%d", &N);
	int nums[N], minnum = 101;
	for (int i = 0; i < N; i++) {
		scanf("%d", &nums[i]);
	}
	for (int i = N - 1; i >= 0; i--) {	// 后续部分有序无需参与移动
		if (nums[i] > minnum) {
			printf("%d", i + 1);	// 找到需要移动的位置i, 则0~i需移动
			return 0;
		}
		minnum = nums[i];
	}
	printf("%d", 0);
	return 0;
}
