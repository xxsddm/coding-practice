// https://www.luogu.com.cn/problem/P3201

#include "vector"
#include "iostream"

using namespace std;

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

int numstk[20];

template <typename T>
inline void write(T x) {
	int tempLen = 0;
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	while (x > 9) {
		numstk[tempLen++] = x % 10;
		x /= 10;
	}
	numstk[tempLen++] = x;
	for (int i = tempLen - 1; i >= 0; i--) {
		putchar(numstk[i] ^ 48);
	}
	putchar('\n');
}

const int length = 1000001;
int n, counter = 1, *nums;
vector<int> container[length];

void merge(int idx1, int idx2) {
	if (idx1 == idx2) {
		return;
	}
	// 将小集合并入大集合
	if (container[idx1].size() > container[idx2].size()) {
		swap(container[idx1], container[idx2]);
	}
	if (container[idx1].empty()) {
		return;
	}
	// 颜色具体取值不重要, temp1, temp2不一定为idx1, idx2
	int temp1 = nums[container[idx1][0]], temp2 = nums[container[idx2][0]];
	for (int &i : container[idx1]) {
		container[idx2].push_back(i);
		nums[i] = temp2;
		if (i) {
			if (nums[i - 1] == temp1) {
				counter++;
			} else if (nums[i - 1] == temp2) {
				counter--;
			}
		}
		if (i != n - 1) {
			if (nums[i + 1] == temp1) {
				counter++;
			} else if (nums[i + 1] == temp2) {
				counter--;
			}
		}
	}
	container[idx1].clear();
}

int main() {
	int m;
	read(n), read(m);
	nums = new int[n];
	for (int i = 0; i < n; i++) {
		read(nums[i]);
		container[nums[i]].push_back(i);
	}
	for (int i = 1; i < n; i++) {
		if (nums[i] != nums[i - 1]) {
			counter++;
		}
	}
	for (int i = 0, op, x, y; i < m; i++) {
		read(op);
		if (op == 1) {
			read(x), read(y);
			merge(x, y);
		} else {
			write(counter);
		}
	}
	return 0;
}
