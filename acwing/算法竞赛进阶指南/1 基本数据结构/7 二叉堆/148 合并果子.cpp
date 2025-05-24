// https://www.acwing.com/problem/content/150/

#include "queue"
#include "iostream"

using namespace std;

int main() {	// Huffman树
	int n, ans = 0;
	scanf("%d", &n);
	priority_queue<int, vector<int>, greater<>> pq;
	for (int i = 0; i < n; i++) {
		int num;
		scanf("%d", &num);
		pq.push(num);
	}
	while (n-- > 1) {
		int num = pq.top();
		pq.pop();
		num += pq.top();
		pq.pop();
		ans += num;
		pq.push(num);
	}
	printf("%d", ans);
	return 0;
}
