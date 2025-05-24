// http://oj.daimayuan.top/course/10/problem/853

#include "algorithm"
#include "iostream"

void read(int &x) {
	x = 0;
	char c = getchar();
	while (c >= 48 && c <= 57) {
		x = (x << 3) + (x << 1) + c - 48;
		c = getchar();
	}
}

std::pair<int, int> *hor, *vert, *aux;

long long mergeSort(int start, int end, std::pair<int, int> *nums) {
	if (start >= end) {
		return 0;
	}
	int mid = (start + end) >> 1, left = start, right = mid + 1, idx = start;
	long long ans = mergeSort(start, mid, nums) + mergeSort(mid + 1, end, nums);
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
		if (aux[left].second <= aux[right].second) {
			nums[idx++] = aux[left++];
		} else {
			nums[idx++] = aux[right++];
			ans += mid - left + 1;
		}
	}
}

int main() {	// 区域数 = 1 + 切线数 + 切线交点数	(也可欧拉公式: R + V - E = 1)
	int n, m, x, y;
	read(n), read(m), read(x), read(y);
	hor = new std::pair<int, int>[x];
	vert = new std::pair<int, int>[y];
	for (int i = 0; i < x; i++) {
		read(hor[i].first), read(hor[i].second);
	}
	for (int i = 0; i < y; i++) {
		read(vert[i].first), read(vert[i].second);
	}
	aux = new std::pair<int, int>[std::max(x, y)];
	std::sort(hor, hor + x);
	std::sort(vert, vert + y);
	long long ans = 1 + x + y
	                + mergeSort(0, x - 1, hor) + mergeSort(0, y - 1, vert)
	                + (long long) x * y;
	printf("%lld", ans);
	return 0;
}
