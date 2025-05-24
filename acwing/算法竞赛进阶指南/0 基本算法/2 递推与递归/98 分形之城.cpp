// https://www.acwing.com/problem/content/100/

#include "cmath"
#include "iostream"

using namespace std;

#define ll long long

pair<ll, ll> getLoc(ll idx, int k) {
	if (k == 0) {
		return {0, 0};
	}
	ll temp = 1ll << (2 * k - 2), nextIdx = idx % (temp);
	auto next = getLoc(nextIdx, k - 1);
	ll x = next.first, y = next.second, diff = 1ll << (k - 1);
	int part = (int) (idx / temp);
	// 由子区域位置平移得到当前位置(看图观察)
	if (part == 0) {	// 顺时针旋转再水平翻转, 平移
		return { - y - diff, - x + diff};
	} else if (part == 1) {	// 平移
		return {x + diff, y + diff};
	} else if (part == 2) {	// 平移
		return {x + diff, y - diff};
	}
	// 顺时针旋转再上下翻转, 平移
	return {y - diff, x - diff};
}

int main() {
	int n;
	cin >> n;
	while (n--) {
		int N;
		ll A, B;
		scanf("%d %lld %lld", &N, &A, &B);
		pair<ll, ll> loc1 = getLoc(A - 1, N), loc2 = getLoc(B - 1, N);
		// long long 平方时会溢出
		double dx = loc1.first - loc2.first, dy = loc1.second - loc2.second;
		printf("%.0lf\n", sqrt(dx * dx + dy * dy) * 5);
	}
	return 0;
}
