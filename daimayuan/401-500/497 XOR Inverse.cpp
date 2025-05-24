// http://oj.daimayuan.top/problem/497

#include "iostream"

int *nums, *aux, *container;

long long mergeSort(int start, int end) {
	if (start == end) {
		return 0;
	}
	int mid = (start + end) >> 1, left = start, right = mid + 1, idx = start;
	long long ans = mergeSort(start, mid) + mergeSort(mid + 1, end);
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
	// 较低位可改变的逆序对关系, 较高位一定相同, 较高位改变对其逆序关系无影响
	int n, ans = 0, maxnum = 0, base = 1;
	long long prev;
	scanf("%d", &n);
	nums = new int[n], aux = new int[n], container = new int[n];
	for (int i = 0; i < n; i++) {
		scanf("%d", &container[i]);
		nums[i] = container[i];
		if (container[i] > maxnum) {
			maxnum = container[i];
		}
	}
	prev = mergeSort(0, n - 1);
	while (base <= maxnum) {
		ans ^= base;
		for (int i = 0; i < n; i++) {
			nums[i] = container[i] ^ ans;
		}
		long long temp = mergeSort(0, n - 1);
		if (temp < prev) {
			prev = temp;
		} else {
			ans ^= base;
		}
		base <<= 1;
	}
	printf("%lld %d", prev, ans);
	return 0;
}
