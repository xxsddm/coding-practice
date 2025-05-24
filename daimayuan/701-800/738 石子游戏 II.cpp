// http://oj.daimayuan.top/course/10/problem/738

#include "iostream"

int main() {
	int n;
	scanf("%d", &n);
	int count = 0;
	for (int i = 0, num; i < n; i++) {
		scanf("%d", &num);
		if ((num & 1) == 0) {
			count++;
		}
	}
	if ((count & 1) || count == 0) {
		printf("Bob");
	} else {
		printf("Alice");
	}
	return 0;
}
