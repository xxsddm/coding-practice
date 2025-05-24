// https://www.acwing.com/problem/content/148/

#include "queue"
#include "cstring"
#include "algorithm"
#include "iostream"

using namespace std;

struct com {
	int num, idx1, idx2;
	com(int n, int i, int j): num(n), idx1(i), idx2(j) {}
	bool operator > (com &other) {
		return num > other.num;
	}
};

void solve() {
	int m, n, back = 0;
	scanf("%d %d", &m, &n);
	int nums[2][n], container[n], used[n][n];
	for (int i = 0; i < n; i++) {
		scanf("%d", &nums[back][i]);
	}
	sort(nums[back], nums[back] + n);
	memset(used, 0, sizeof(used));
	for (int i = 1; i < m; i++, back = 1 - back) {	// 路径两两合并, 保留前n小元素
		for (int j = 0; j < n; j++) {
			scanf("%d", &container[j]);
		}
		int idx = 1 - back;
		sort(container, container + n);
		priority_queue<com, vector<com>, greater<>> pq;
		pq.emplace(nums[back][0] + container[0], 0, 0);
		for (int j = 0; j < n; j++) {
			com temp = pq.top();
			pq.pop();
			int &idx1 = temp.idx1, &idx2 = temp.idx2, &num = temp.num;
			nums[idx][j] = num;
			// used记录本轮是否使用过该索引组合
			if (idx1 + 1 < n && used[idx1 + 1][idx2] != i) {
				pq.emplace(nums[back][idx1 + 1] + container[idx2], idx1 + 1, idx2);
				used[idx1 + 1][idx2] = i;
			}
			if (idx2 + 1 < n && used[idx1][idx2 + 1] != i) {
				pq.emplace(nums[back][idx1] + container[idx2 + 1], idx1, idx2 + 1);
				used[idx1][idx2 + 1] = i;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		printf("%d ", nums[back][i]);
	}
	printf("\n");
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}