// https://www.acwing.com/problem/content/199/

#include "cstring"
#include "queue"
#include "iostream"

using namespace std;

int main() {
	int N;
	deque<int> container;
	cin >> N;
	for (int i = 2; i <= N; i++) {
		bool isPrime = true;
		for (int j = 2; j <= i / j; j++) {
			if (i % j == 0) {
				isPrime = false;
				break;
			}
		}
		if (isPrime) {
			container.push_back(i);
		}
	}
	for (int &prime : container) {
		long long temp = prime;
		int count = 0;
		while (N >= temp) {
			count += N / temp;	// 记录每个质数各次幂的倍数的数量(每个可作为该层的元素记录一次)
			temp *= prime;
		}
		cout << prime << ' ' << count << endl;
	}
	return 0;
}
