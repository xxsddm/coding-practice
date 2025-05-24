// https://www.acwing.com/problem/content/description/131/

#include "vector"
#include "iostream"

using namespace std;

int n, count = 0;

void dfs(int idx, int num, vector<int> &nums, int *output) {
	if (count == 20) {
		return;
	}
	if (nums.empty()) {
		nums.push_back(num);
		dfs(idx, num + 1, nums, output);
		nums.pop_back();
		return;
	}
	if (num == n + 1 || idx + (int) nums.size() == n) {
		for (int i = (int) nums.size() - 1; i >= 0; i--) {
			output[idx++] = nums[i];
		}
		for (int i = 0; i < n; i++) {
			printf("%d", output[i]);
		}
		printf("\n");
		count++;
		return;
	}
	// 选择输出
	output[idx] = nums.back();
	nums.pop_back();
	dfs(idx + 1, num, nums, output);
	nums.push_back(output[idx]);
	// 选择入栈
	nums.push_back(num);
	dfs(idx, num + 1, nums, output);
	nums.pop_back();
}

int main() {
	cin >> n;
	int container[n];
	vector<int> nums;
	dfs(0, 1, nums, container);
	return 0;
}