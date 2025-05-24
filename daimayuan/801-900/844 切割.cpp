// http://oj.daimayuan.top/course/11/problem/844

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

int main() {
	int n;
	read(n);
	std::priority_queue<long long, std::vector<long long>, std::greater<>> pq;
	for (int i = 0, num; i < n; i++) {
		read(num);
		pq.push(num);
	}
	long long ans = 0, temp;
	for (int i = 1; i < n; i++) {
		temp = pq.top();
		pq.pop();
		temp += pq.top();
		pq.pop();
		ans += temp;
		pq.push(temp);
	}
	printf("%lld", ans);
	return 0;
}
