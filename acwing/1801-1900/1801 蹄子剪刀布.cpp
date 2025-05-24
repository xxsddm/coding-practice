// https://www.acwing.com/problem/content/description/1803/

#include "iostream"

using namespace std;

int getNext(int num) {
	return num == 3 ? 1 : (num + 1);
}

int main() {	// 对比关系一定为1>2>3>1 / 1<2<3<1
	int num1 = 0, num2 = 0, N;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		if (getNext(x) == y) {	// 1>2>3>1
			num1++;
		}
		if (x == getNext(y)) {	// 1<2<3<1
			num2++;
		}
	}
	printf("%d", max(num1, num2));
	return 0;
}
