// https://www.acwing.com/problem/content/110/

#include "iostream"

using namespace std;

int mergeSort(int start, int end, int *nums, int *aux) {
	if (start >= end) {
		return 0;
	}
	int ans = 0, mid = (start + end) >> 1;
	ans ^= mergeSort(start, mid, nums, aux);
	ans ^= mergeSort(mid + 1, end, nums, aux);
	for (int i = start; i <= end; i++) {
		aux[i] = nums[i];
	}
	int idx = start, left = start, right = mid + 1;
	while (true) {
		if (left == mid + 1) {
			while (idx <= end) {
				nums[idx++] = aux[right++];
			}
			return ans;
		}
		if (right == end + 1) {
			while (idx <= end) {
				nums[idx++] = aux[left++];
			}
			return ans;
		}
		if (aux[left] < aux[right]) {
			nums[idx++] = aux[left++];
		} else {
			nums[idx++] = aux[right++];
			ans ^= (mid - left + 1) & 1;
		}
	}
}

int main() {	// P38
	int n;
	while (cin >> n && n) {
		int length = n * n - 1, nums1[length], nums2[length], aux[length];
		for (int i = 0, idx = 0; i <= length; i++) {
			int num;
			cin >> num;
			if (num == 0) {
				continue;
			}
			nums1[idx++] = num;
		}
		for (int i = 0, idx = 0; i <= length; i++) {
			int num;
			cin >> num;
			if (num == 0) {
				continue;
			}
			nums2[idx++] = num;
		}
		if (mergeSort(0, length - 1, nums1, aux) == mergeSort(0, length - 1, nums2, aux)) {
			cout << "TAK" << endl;
		} else {
			cout << "NIE" << endl;
		}
	}
	return 0;
}
