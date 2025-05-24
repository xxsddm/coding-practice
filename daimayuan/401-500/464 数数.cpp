// http://oj.daimayuan.top/course/10/problem/464

#include "algorithm"
#include "cstring"
#include "iostream"

using namespace std;

struct Node {
	int num, idx, start, end;
	bool operator < (Node &other) {
		return num < other.num;
	}
} query[100000];

int N, node[100001], container[100000];
pair<int, int> nums[100000];

void add(int idx, int delta) {
	while (idx <= N) {
		node[idx] += delta;
		idx += idx & -idx;
	}
}

int count(int idx) {
	int ans = 0;
	while (idx) {
		ans += node[idx];
		idx ^= idx & -idx;
	}
	return ans;
}

void solve() {
	int Q, idx = 0;
	scanf("%d %d", &N, &Q);
	memset(node, 0, sizeof(node));
	for (int i = 0; i < N; i++) {
		scanf("%d", &nums[i].first);
		nums[i].second = i + 1;
	}
	for (int i = 0; i < Q; i++) {
		scanf("%d %d %d", &query[i].start, &query[i].end, &query[i].num);
		query[i].idx = i;
	}
	sort(nums, nums + N);
	sort(query, query + Q);
	for (int i = 0; i < Q; i++) {
		int &num = query[i].num;
		while (idx < N && nums[idx].first <= num) {
			add(nums[idx].second, 1);
			idx++;
		}
		container[query[i].idx] = count(query[i].end) - count(query[i].start - 1);
	}
	for (int i = 0; i < Q; i++) {
		printf("%d ", container[i]);
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
