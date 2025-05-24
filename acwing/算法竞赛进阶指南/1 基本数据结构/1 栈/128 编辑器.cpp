// https://www.acwing.com/problem/content/description/130/

#include "stack"
#include "iostream"

using namespace std;

int main() {
	stack<int> left, right;	// 存放左, 右边的数
	int Q, idx = 0;
	scanf("%d", &Q);
	int cumsum[Q], maxsum[Q];
	while (Q--) {
		char command[2];
		scanf("%s", command);
		if (command[0] == 'I') {
			int num;
			scanf("%d", &num);
			if (idx) {
				cumsum[idx] = num + cumsum[idx - 1];
				maxsum[idx] = max(maxsum[idx - 1], cumsum[idx]);
			} else {
				cumsum[idx] = num;
				maxsum[idx] = num;
			}
			idx++;
			left.push(num);
		} else if (command[0] == 'D') {
			if (!left.empty()) {
				idx--;
				left.pop();
			}
		} else if (command[0] == 'L') {
			if (!left.empty()) {
				idx--;
				right.push(left.top());
				left.pop();
			}
		} else if (command[0] == 'R') {
			if (!right.empty()) {
				int num = right.top();
				left.push(num);
				right.pop();
				if (idx) {
					cumsum[idx] = num + cumsum[idx - 1];
					maxsum[idx] = max(maxsum[idx - 1], cumsum[idx]);
				} else {
					cumsum[idx] = num;
					maxsum[idx] = num;
				}
				idx++;
			}
		} else {
			int k;
			scanf("%d", &k);
			printf("%d\n", maxsum[k - 1]);
		}
	}
	return 0;
}
