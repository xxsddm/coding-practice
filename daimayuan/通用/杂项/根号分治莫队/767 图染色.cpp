// http://oj.daimayuan.top/course/15/problem/767

#include "vector"
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

int *status, *counter;
std::vector<int> *next, *largepoint;

int main() {
	int n, m, q;
	read(n), read(m), read(q);
	status = new int[n + 1], counter = new int[n + 1];
	next = new std::vector<int>[n + 1], largepoint = new std::vector<int>[n + 1];
	int left = 1, right = m << 1;
	while (left <= right) {
		int mid = (left + right) >> 1;
		if (mid < m / mid) {
			left = mid + 1;
		} else if (mid > m / mid) {
			right = mid - 1;
		} else {
			right = mid;
			break;
		}
	}
	int size = right;
	for (int i = 0, u, v; i < m; i++) {
		read(u), read(v);
		next[u].push_back(v);
		next[v].push_back(u);
	}
	for (int i = 1; i <= n; i++) {
		if ((int) next[i].size() > size) {
			for (int &j : next[i]) {
				largepoint[j].push_back(i);
			}
		}
		status[i] = counter[i] = 0;
	}
	for (int i = 0, op, x, temp; i < q; i++) {
		read(op), read(x);
		if (op == 1) {
			status[x] ^= 1;
			temp = status[x] ? 1 : -1;
			for (int &j : largepoint[x]) {
				counter[j] += temp;
			}
		} else {
			if ((int) next[x].size() > size) {
				write(counter[x]);
			} else {
				int ans = 0;
				for (int &j : next[x]) {
					ans += status[j];
				}
				write(ans);
			}
		}
	}
	return 0;
}
