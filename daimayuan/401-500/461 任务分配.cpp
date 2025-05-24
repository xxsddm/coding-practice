// http://oj.daimayuan.top/course/11/problem/461

#include "algorithm"
#include "iostream"

using namespace std;

struct task {
	int start, end, w;
	bool operator < (task &other) {
		if (end != other.end) {
			return end < other.end;
		}
		return start < other.start;
	}
};

int main() {	// DP
	int n;
	scanf("%d", &n);
	task container[n];
	for (int i = 0; i < n; i++) {
		scanf("%d %d %d", &container[i].start, &container[i].end, &container[i].w);
	}
	sort(container, container + n);
	// dp[i] -> 0~i时间内可取得最大值
	int length = container[n - 1].end, dp[length + 1];
	dp[0] = 0;
	for (int t = 1, i = 0; t <= length; t++) {
		dp[t] = dp[t - 1];
		while (i < n && container[i].end == t) {
			int &start = container[i].start, &w = container[i].w;
			dp[t] = max(dp[t], dp[start] + w);
			i++;
		}

	}
	printf("%d", dp[length]);
	return 0;
}
