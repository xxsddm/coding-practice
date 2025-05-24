// https://www.acwing.com/problem/content/108/

#include "queue"
#include "iostream"

using namespace std;

void solve(int p) {
	priority_queue<int> pq1;
	priority_queue<int, vector<int>, greater<>> pq2;
	int idx, M;
	scanf("%d %d", &idx, &M);
	cout << p << " " << (M >> 1) + 1 << endl;
	for (int i = 1, count = 0; i <= M; i++) {
		int num, half = i >> 1;
		scanf("%d", &num);
		if (!pq2.empty() && num >= pq2.top()) {
			pq2.push(num);
			if (pq2.size() > half) {
				pq1.push(pq2.top());
				pq2.pop();
			}
		} else {
			pq1.push(num);
			if (pq1.size() > half + 1) {
				pq2.push(pq1.top());
				pq1.pop();
			}
		}
		if (i & 1) {
			printf("%d ", pq1.top());
			if (++count % 10 == 0 || i == M) {
				count = 0;
				cout << endl;
			}
		}
	}
}

int main() {
	int P;
	cin >> P;
	for (int p = 1; p <= P; p++) {
		solve(p);
	}
	return 0;
}
