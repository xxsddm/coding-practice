// http://oj.daimayuan.top/course/11/problem/55

#include "iostream"

int main() {
	int n, num, next = 1;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &num);
		while (next <= num) {
			printf("push %d\n", next++);
		}
		printf("pop\n");
	}
	return 0;
}
