// http://oj.daimayuan.top/course/15/problem/718

#include "iostream"

unsigned int A, B, C;
inline unsigned int rng61() {
	A ^= A << 16;
	A ^= A >> 5;
	A ^= A << 1;
	unsigned int t = A;
	A = B;
	B = C;
	C ^= t ^ A;
	return C;
}

unsigned int *nums, **container;
int length = 1, *log2idx;

int main() {	// ST表O(1)查询区间最值
	int n, q;
	scanf("%d %d %u %u %u", &n, &q, &A, &B, &C);
	nums = new unsigned int[n + 1];
	container = new unsigned int*[n + 1];	// container[i][j] -> max(nums[i] ~ nums[i + (1 << j)])
	log2idx = new int[(n >> 1) + 1];
	log2idx[0] = 0;
	for (int i = 1, limit = n >> 1; i <= limit; i++) {
		log2idx[i] = log2idx[i - 1] + (i == (1 << log2idx[i - 1]));
	}
	for (int limit = n >> 1, temp = 1; temp <= limit; temp <<= 1) {
		length++;
	}
	for (int i = 1; i <= n; i++) {
		nums[i] = rng61();
		container[i] = new unsigned int[length];
		container[i][0] = nums[i];
	}
	for (int i = 1, temp = 2; i < length; i++, temp <<= 1) {
		for (int j = 1, limit = n + 1 - temp; j <= limit; j++) {
			container[j][i] = std::max(container[j][i - 1], container[j + (temp >> 1)][i - 1]);
		}
	}
	unsigned int ans = 0;
	for (int i = 1, subLen, idx; i <= q; i++) {
		unsigned int l = rng61() % n + 1, r = rng61() % n + 1;
		if (l > r) {
			std::swap(l, r);
		}
		subLen = (r - l + 1) >> 1;
		idx = log2idx[subLen];
		ans ^= std::max(container[l][idx], container[r - (1 << idx) + 1][idx]);
	}
	printf("%u", ans);
	return 0;
}