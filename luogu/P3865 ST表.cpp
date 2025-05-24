// https://www.luogu.com.cn/problem/P3865

#include "iostream"

template <typename T>
inline void read(T &x) {
	x = 0;
	char c = getchar();
	while (c < 48 || c > 57) {
		c = getchar();
	}
	while (c >= 48 && c <= 57) {
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = getchar();
	}
}

int numstk[30];

template <typename T>
inline void write(T x) {
	int length = 0;
	while (x > 9) {
		numstk[length++] = x % 10;
		x /= 10;
	}
	numstk[length++] = x;
	for (int i = length - 1; i >= 0; i--) {
		putchar(numstk[i] ^ 48);
	}
	putchar('\n');
}

int length = 0, *log2idx, **nums;

int main() {
	int N, M;
	read(N), read(M);
	nums = new int*[N + 1];
	for (int i = 1, limit = N >> 1; i <= limit; i <<= 1) {
		length++;
	}
	for (int i = 1; i <= N; i++) {
		nums[i] = new int[length + 1];
		read(nums[i][0]);
	}
	log2idx = new int[(N >> 1) + 1];
	log2idx[0] = 0;
	for (int i = 1, limit = N >> 1; i <= limit; i++) {
		log2idx[i] = log2idx[i - 1] + (i == (1 << log2idx[i - 1]));
	}
	for (int j = 1, subLen = 2; j <= length; j++, subLen <<= 1) {
		for (int i = 1, limit = N - subLen + 1; i <= limit; i++) {
			nums[i][j] = std::max(nums[i][j - 1], nums[i + (subLen >> 1)][j - 1]);
		}
	}
	for (int i = 0, l, r, subLen, idx; i < M; i++) {
		read(l), read(r);
		subLen = (r - l + 1) >> 1;
		idx = log2idx[subLen];
		write(std::max(nums[l][idx], nums[r - (1 << idx) + 1][idx]));
	}
	return 0;
}
