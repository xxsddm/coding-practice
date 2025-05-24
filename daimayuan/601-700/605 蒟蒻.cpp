// http://oj.daimayuan.top/course/11/problem/605

#include "map"
#include "iostream"

using namespace std;

int main() {
	int n;
	scanf("%d", &n);
	long long ans = 0;
	map<int, int> cheap, bad;
	for (int i = 0; i < n; i++) {
		int op;
		scanf("%d", &op);
		if (op == 1) {
			int w, t;
			scanf("%d %d", &w, &t);
			if (cheap.count(w) || bad.count(t)) {
				continue;
			}
			ans += w;
			cheap[w] = t;
			bad[t] = w;
			continue;
		}
		if (ans == 0) {
			continue;
		}
		if (op == 2) {
			auto &[w, t] = *cheap.begin();
			cheap.erase(w);
			bad.erase(t);
			ans -= w;
		} else {
			auto &[t, w] = *bad.begin();
			cheap.erase(w);
			bad.erase(t);
			ans -= w;
		}
	}
	printf("%lld", ans);
	return 0;
}
