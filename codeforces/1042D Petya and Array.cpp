// https://codeforces.com/contest/1042/problem/D

#include "iostream"

template <typename T>
inline void read(T &x) {
	x = 0;
	bool neg = false;
	char c = getchar();
	while (c < 48 || c > 57) {
		if (c == '-') {
			neg = true;
		}
		c = getchar();
	}
	while (c >= 48 && c <= 57) {
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = getchar();
	}
	if (neg) {
		x = -x;
	}
}

long long t, *nums, *aux;

long long mergeSort(int start, int end) {
	if (start == end) {
		return 0;
	}
	int mid = (start + end) >> 1;
	long long ans = mergeSort(start, mid) + mergeSort(mid + 1, end);
	for (int left = start, right = mid + 1; left <= mid && right <= end; right++) {
		long long &temp = nums[right];
		while (left <= mid && temp - nums[left] >= t) {
			left++;
		}
		ans += mid - left + 1;
	}
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
		if (aux[left] <= aux[right]) {
			nums[idx++] = aux[left++];
		} else {
			nums[idx++] = aux[right++];
		}
	}
}

int main() {
	int n;
	read(n), read(t);
	nums = new long long[n + 1];
	aux = new long long[n + 1];
	nums[0] = 0;
	for (int i = 1; i <= n; i++) {
		read(nums[i]);
		nums[i] += nums[i - 1];
	}
	printf("%lld", mergeSort(0, n));
	return 0;
}
