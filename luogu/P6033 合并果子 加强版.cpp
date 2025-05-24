// https://www.luogu.com.cn/problem/P6033

#include "cstring"
#include "queue"
#include "iostream"

void read(int &x) {
	x = 0;
	char c = getchar();
	while (c >= 48 && c <= 57) {
		x = (x << 3) + (x << 1) + c - 48;
		c = getchar();
	}
}

const int limit = 1e5 + 1;
int counter[limit];

int main() {
	int n;
	read(n);
	memset(counter, 0, sizeof(counter));
	for (int i = 0, num; i < n; i++) {	// 计数排序
		read(num);
		counter[num]++;
	}
	std::queue<long long> q1, q2;	// 单调队列分别维护排序后和合并后的值
	for (int i = 1; i < limit; i++) {
		for (int j = counter[i]; j; j--) {
			q1.push(i);
		}
	}
	long long ans = 0, temp;
	for (int i = 1; i < n; i++) {
		if (q2.empty() || (!q1.empty() && q1.front() <= q2.front())) {
			temp = q1.front();
			q1.pop();
		} else {
			temp = q2.front();
			q2.pop();
		}
		if (q2.empty() || (!q1.empty() && q1.front() <= q2.front())) {
			temp += q1.front();
			q1.pop();
		} else {
			temp += q2.front();
			q2.pop();
		}
		q2.push(temp);
		ans += temp;
	}
	printf("%lld", ans);
	return 0;
}
