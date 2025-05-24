// https://www.acwing.com/problem/content/109/

#include "iostream"

using namespace std;

typedef long long ll;

ll mergeSort(int start, int end, int *nums, int *aux) {
	if (start >= end) {
		return 0LL;
	}
	ll ans = 0;
	int mid = (start + end) >> 1;
	ans += mergeSort(start, mid, nums, aux);
	ans += mergeSort(mid + 1, end, nums, aux);
	int left = start, right = mid + 1, idx = start;
	for (int i = start; i <= end; i++) {
		aux[i] = nums[i];
	}
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
		if (aux[left] <= aux[right]) {
			nums[idx++] = aux[left++];
		} else {
			nums[idx++] = aux[right++];
			ans += mid - left + 1;
		}
	}

}

int main() {
	int n;
	while (cin >> n && n) {
		int nums[n], aux[n];
		for (int i = 0; i < n; i++) {
			scanf("%d", &nums[i]);
		}
		printf("%lld\n", mergeSort(0, n - 1, nums, aux));
	}
	return 0;
}
