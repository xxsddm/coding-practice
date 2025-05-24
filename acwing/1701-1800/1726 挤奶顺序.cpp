// https://www.acwing.com/problem/content/description/1728/

#include "cstring"
#include "iostream"

using namespace std;

int main() {
	int N, M, K;
	scanf("%d %d %d", &N, &M, &K);
	int nums[N + 1], num2idx[N + 1], subnums[M];
	bool used = false;
	memset(nums, 0, sizeof(nums));
	memset(num2idx, 0, sizeof(num2idx));
	for (int i = 0; i < M; i++) {
		scanf("%d", &subnums[i]);
		if (subnums[i] == 1) {
			used = true;
		}
	}
	for (int i = 0; i < K; i++) {
		int num, idx;
		scanf("%d %d", &num, &idx);
		nums[idx] = num;
		num2idx[num] = idx;
	}
	if (num2idx[1]) {	// 1已规定索引
		printf("%d", num2idx[1]);
		return 0;
	}
	if (used) {			// 1已确定相对顺序, 则相对顺序序列优先填入 较前位置
		for (int i = 1, j = 0; i <= N; i++) {
			if (nums[i]) {
				if (nums[i] == subnums[j]) {
					j++;
				}
				continue;
			}
			if (num2idx[subnums[j]] == 0 && subnums[j++] == 1) {
				printf("%d", i);
				return 0;
			}
		}
	}
	for (int i = N, j = M - 1; i >= 1; i--) {	// 1无显式限定, 则相对顺序序列优先填入 较后位置
		if (nums[i]) {
			if (j >= 0 && nums[i] == subnums[j]) {
				j--;
			}
			continue;
		}
		if (j >= 0 && num2idx[subnums[j]] == 0) {
			nums[i] = subnums[j--];
		}
	}
	for (int i = 1; i <= N; i++) {
		if (nums[i] == 0) {
			printf("%d", i);
			return 0;
		}
	}
	return 0;
}
