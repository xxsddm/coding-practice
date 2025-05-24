// https://www.acwing.com/problem/content/description/139/

#include "iostream"
#include "vector"

using namespace std;

const int mod = 100007;

int getKey(int *nums) {
	int ans = 0;
	for (int i = 0; i < 6; i++) {
		ans = (ans + nums[i]) % mod;
	}
	return ans;
}

int next(int idx) {
	return idx == 5 ? 0 : (idx + 1);
}

int prev(int idx) {
	return idx == 0 ? 5 : (idx - 1);
}

bool check(int *nums1, int *nums2) {
	if (nums1[0] != nums2[0]) {
		return false;
	}
	int minnum = nums1[0];
	for (int i = 0; i < 6; i++) {
		if (nums2[i] != minnum) {
			continue;
		}
		int idx1 = next(0), idx2 = next(i);
		while (idx1 != 0) {
			if (nums1[idx1] != nums2[idx2]) {
				break;
			}
			idx1 = next(idx1), idx2 = next(idx2);
		}
		if (idx1 == 0) {
			return true;
		}
		idx1 = prev(0), idx2 = next(i);
		while (idx1 != 0) {
			if (nums1[idx1] != nums2[idx2]) {
				break;
			}
			idx1 = prev(idx1), idx2 = next(idx2);
		}
		if (idx1 == 0) {
			return true;
		}
	}
	return false;
}

int main() {
	int N, temp[6];
	vector<int*> visited[mod];
	scanf("%d", &N);
	bool skip = false;
	for (int n = 0; n < N; n++) {
		int *nums = new int[6], minnum = 1e7, minidx = -1;	// 必须new
		for (int i = 0; i < 6; i++) {
			scanf("%d", &temp[i]);
			if (temp[i] < minnum) {
				minnum = temp[i];
				minidx = i;
			}
		}
		if (skip) {
			continue;
		}
		for (int i = minidx, j = 0; j < 6; i = next(i), j++) {	// 最小数字放在首端
			nums[j] = temp[i];
		}
		int key = getKey(nums);
		for (int *other : visited[key]) {
			if (check(other, nums)) {
				skip = true;
				break;
			}
		}
		visited[key].push_back(nums);
	}
	if (skip) {
		printf("Twin snowflakes found.");
		return 0;
	}
	printf("No two snowflakes are alike.");
	return 0;
}