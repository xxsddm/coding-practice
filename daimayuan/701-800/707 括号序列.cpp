// http://oj.daimayuan.top/course/10/problem/707

#include "stack"
#include "cstring"
#include "iostream"

int *left, *dp;
char word[1000001];

int main() {
	scanf("%s", word);
	int length = strlen(word);
	long long ans = 0;
	left = new int[length], dp = new int[length];
	std::stack<int> stk;
	for (int i = 0; i < length; i++) {
		dp[i] = 0;
		if (word[i] == '(') {
			stk.push(i);
		} else if (!stk.empty()) {
			left[i] = stk.top();
			stk.pop();
		} else {
			left[i] = -1;
		}
	}
	for (int i = 1; i < length; i++) {
		if (word[i] == ')' && left[i] != -1) {
			dp[i] = 1 + (left[i] ? dp[left[i] - 1] : 0);
			ans += dp[i];
		}
	}
	printf("%lld", ans);
	return 0;
}
