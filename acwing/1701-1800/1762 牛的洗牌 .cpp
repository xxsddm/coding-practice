// https://www.acwing.com/problem/content/description/1764/

#include "iostream"

using namespace std;

int N;

int main() {
	scanf("%d", &N);
	int a[N + 1], nums[N + 1], aux[N + 1];
	for (int i = 1; i <= N; i++) {
		scanf("%d", &a[i]);
	}
	for (int i = 1; i <= N; i++) {
		scanf("%d", &aux[i]);
	}
	for (int i = 1; i <= N; i++) {
		nums[i] = aux[a[a[a[i]]]];
	}
	for (int i = 1; i <= N; i++) {
		printf("%d\n", nums[i]);
	}
	return 0;
}
