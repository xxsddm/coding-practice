// https://www.luogu.com.cn/problem/P1494

#include "array"
#include "algorithm"

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
}

long long gcd(long long num1, long long num2) {
	long long temp;
	while (num2) {
		temp = num2;
		num2 = num1 % num2;
		num1 = temp;
	}
	return num1;
}

int *counter, *container;
std::pair<long long, long long> *ans;
std::array<int, 3> *query;

int main() {
	int n, m;
	read(n), read(m);
	counter = new int[n + 1], container = new int[n + 1];
	ans = new std::pair<long long, long long>[m];
	query = new std::array<int, 3>[m];
	for (int i = 1; i <= n; i++) {
		read(container[i]);
		counter[i] = 0;
	}
	for (int i = 0; i < m; i++) {
		read(query[i][0]), read(query[i][1]);
		query[i][2] = i;
	}
	int block = n;
	for (int left = 1, mid; left <= block;) {
		mid = (left + block) >> 1;
		if (mid < n / mid) {
			left = mid + 1;
		} else if (mid > n / mid) {
			block = mid - 1;
		} else {
			block = mid;
			break;
		}
	}
	sort(query, query + m, [&] (auto & p1, auto & p2) -> bool {
		if (p1[0] / block != p2[0] / block) {
			return p1[0] < p2[0];
		}
		return p1[1] < p2[1];
	});
	long long num = 0;
	for (int i = 0, start = 1, end = 0; i < m; i++) {
		int left = query[i][0], right = query[i][1];
		if (left == right) {
			ans[query[i][2]] = {0,  1};
			continue;
		}
		while (end < right) {
			end++;
			num += counter[container[end]];
			counter[container[end]]++;
		}
		while (start < left) {
			counter[container[start]]--;
			num -= counter[container[start]];
			start++;
		}
		while (start > left) {
			start--;
			num += counter[container[start]];
			counter[container[start]]++;
		}
		while (end > right) {
			counter[container[end]]--;
			num -= counter[container[end]];
			end--;
		}
		ans[query[i][2]] = {num, ((long long) (right - left + 1) * (right - left)) >> 1};
	}
	for (int i = 0, temp; i < m; i++) {
		temp = gcd(ans[i].first, ans[i].second);
		write(ans[i].first / temp);
		putchar('/');
		write(ans[i].second / temp);
		putchar('\n');
	}
	return 0;
}