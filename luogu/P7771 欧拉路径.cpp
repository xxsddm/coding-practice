// https://www.luogu.com.cn/problem/P7771

#include "algorithm"
#include "vector"
#include "cstring"
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
	numstk[length++] = x % 10;
	for (int i = length - 1; i >= 0; i--) {
		putchar(numstk[i] ^ 48);
	}
	putchar(' ');
}

int idx, *indegree, *outdegree, *nums;
std::vector<int> *next;

void dfs(int node) {
	while (!next[node].empty()) {
		int nextNode = next[node].back();
		next[node].pop_back();
		dfs(nextNode);
	}
	nums[idx--] = node;
}

int main() {
	int n, m;
	read(n), read(m);
	indegree = new int[n + 1], outdegree = new int[n + 1];
	next = new std::vector<int>[n + 1];
	memset(indegree, 0, sizeof(int) * (n + 1));
	memset(outdegree, 0, sizeof(int) * (n + 1));
	int start = 1;	// 考虑欧拉回路情况, 起点默认为1
	bool same = true, head = false, tail = false;
	for (int i = 0, u, v; i < m; i++) {
		read(u), read(v);
		outdegree[u]++, indegree[v]++;
		next[u].push_back(v);
	}
	for (int i = 1; i <= n; i++) {
		if (outdegree[i] == indegree[i] + 1) {
			same = false;
			if (head) {
				printf("No");
				return 0;
			}
			start = i;
			head = true;
		} else if (outdegree[i] + 1 == indegree[i]) {
			same = false;
			if (tail) {
				printf("No");
				return 0;
			}
			tail = true;
		}
	}
	if (!same && !(head && tail)) {
		printf("No");
		return 0;
	}
	idx = m;
	nums = new int[m + 1];
	for (int i = 1; i <= n; i++) {
		sort(next[i].begin(), next[i].end(), [] (int &num1, int &num2) -> bool {
			return num1 > num2;
		});
	}
	dfs(start);
	memset(indegree, 0, sizeof(int) * (n + 1));
	for (int i = 0; i <= m; i++) {
		indegree[nums[i]] = 1;
	}
	for (int i = 1; i <= n; i++) {
		if (!indegree[i]) {
			printf("No");
			return 0;
		}
	}
	for (int i = 0; i <= m; i++) {
		write(nums[i]);
	}
	return 0;
}
