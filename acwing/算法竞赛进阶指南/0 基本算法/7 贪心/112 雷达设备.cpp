// https://www.acwing.com/problem/content/114/

#include "algorithm"
#include "cmath"
#include "iostream"

using namespace std;

int main() {
	int n, d;
	scanf("%d %d", &n, &d);
	double temp = d * d, eps = 1e-6;
	pair<double, double> container[n];
	bool impossible = false;
	for (int i = 0; i < n; i++) {
		double x, y;
		scanf("%lf %lf", &x, &y);
		if (abs(y) > d) {
			impossible = true;
			continue;
		}
		double diff = sqrt(temp - y * y);
		// 记录各节点能连接的源点范围
		container[i].first = x - diff;
		container[i].second = x + diff;
	}
	if (impossible) {
		cout << -1;
		return 0;
	}
	int ans = 0;
	sort(container, container + n);
	double right = container[0].first - 10;
	for (int i = 0; i < n; i++) {
		if (container[i].first > right + eps) {
			ans++;
			right = container[i].second;
		} else {
			right = min(right, container[i].second);
		}
	}
	printf("%d", ans);
	return 0;
}
