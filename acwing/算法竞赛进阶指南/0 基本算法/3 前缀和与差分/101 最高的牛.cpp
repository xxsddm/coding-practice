// https://www.acwing.com/problem/content/103/

#include "cstring"
#include "unordered_set"
#include "iostream"

using namespace std;

int main() {
	int N, P, H, M;
	scanf("%d %d %d %d", &N, &P, &H, &M);
	int counter[N + 1];	// 构造差分数组
	unordered_set<int> used;	// 可能存在相同数对
	memset(counter, 0, sizeof(counter));
	for (int i = 0; i < M; i++) {
		int A, B;
		cin >> A >> B;
		if (A > B) {
			swap(A, B);
		}
		int key = A * 100000 + B;
		if (used.count(key)) {
			continue;
		}
		used.insert(key);
		if (A >= P) {
			counter[A]--;
			counter[B - 1]++;
		} else {
			counter[A - 1]++;
			counter[B - 2]--;
		}
	}
	for (int i = P, h = H; i < N; i++) {
		h += counter[i];
		counter[i] = h;
	}
	for (int i = P - 2, h = H; i >= 0; i--) {
		h += counter[i];
		counter[i] = h;
	}
	counter[P - 1] = H;
	for (int i = 0; i < N; i++) {
		printf("%d\n", counter[i]);
	}
	return 0;
}
