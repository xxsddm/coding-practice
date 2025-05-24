// https://www.acwing.com/problem/content/115/

class Solution {
public:
	int aux[1000];

	vector<int> specialSort(int N) {
		vector<int> ans(N);
		for (int i = 0; i < N; i++) {
			ans[i] = i + 1;
		}
		// 归并排序满足性质要求
		mergeSort(ans, 0, N - 1);
		return ans;
	}

	void mergeSort(vector<int> &nums, int start, int end) {
		if (start >= end) {
			return;
		}
		int mid = (start + end) >> 1, idx = start, left = start, right = mid + 1;
		mergeSort(nums, start, mid);
		mergeSort(nums, mid + 1, end);
		for (int i = start; i <= end; i++) {
			aux[i] = nums[i];
		}
		while (true) {
			if (left == mid + 1) {
				while (idx <= end) {
					nums[idx++] = aux[right++];
				}
				return;
			}
			if (right == end + 1) {
				while (idx <= end) {
					nums[idx++] = aux[left++];
				}
				return;
			}
			if (compare(aux[left], aux[right])) {
				nums[idx++] = aux[left++];
			} else {
				nums[idx++] = aux[right++];
			}

		}
	}
};
