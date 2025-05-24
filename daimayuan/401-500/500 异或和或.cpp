// http://oj.daimayuan.top/course/11/problem/500

#include "iostream"

int main() {	// 10->11->01
	int T;
	scanf("%d", &T);
	std::string s, t;
	while (T--) {
		std::cin >> s >> t;
		if (s.size() != t.size() || (s.size() == 1 && s != t)) {
			printf("NO\n");
			continue;
		}
		bool all0s = true, all0t = true;
		for (char &c : s) {
			if (c == '1') {
				all0s = false;
				break;
			}
		}
		for (char &c : t) {
			if (c == '1') {
				all0t = false;
				break;
			}
		}
		printf(((all0s && !all0t) || (!all0s && all0t)) ? "NO\n" : "YES\n");
	}
	return 0;
}
