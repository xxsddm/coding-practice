// http://oj.daimayuan.top/course/10/problem/735

#include "vector"
#include "iostream"

const int maxLen = 100000;
int nums1[maxLen + 1], nums2[maxLen + 1], draw[maxLen], output[maxLen], num2idx[maxLen + 1];
std::vector<int> container[maxLen + 1];

void solve() {
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &nums1[i]);
		num2idx[i] = -1;
		container[i].clear();
	}
	int diff = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &nums2[i]);
		num2idx[nums2[i]] = i;
		if (nums1[i] != nums2[i]) {
			container[nums2[i]].push_back(i);
			diff++;
		}
	}
	for (int i = 0; i < m; i++) {
		scanf("%d", &draw[i]);
	}
	for (int i = m - 1, rest = 0; i >= 0; i--) {
		int &num = draw[i];
		if (!container[num].empty()) {
			output[i] = container[num].back();
			container[num].pop_back();
			rest = output[i];
			diff--;
			continue;
		}
		if (num2idx[num] != -1) {
			output[i] = num2idx[num];
			rest = num2idx[num];
		} else if (rest) {
			output[i] = rest;
		} else {
			printf("NO\n");
			return;
		}
	}
	if (diff) {
		printf("NO\n");
		return;
	}
	printf("YES\n");
	for (int i = 0; i < m; i++) {
		printf("%d ", output[i]);
	}
	printf("\n");
}

int main() {
	int T;
	scanf("%d", &T);
	for (int i = 0; i < T; i++) {
		solve();
	}
	return 0;
}
