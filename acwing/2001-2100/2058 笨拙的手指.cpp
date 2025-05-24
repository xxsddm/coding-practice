// https://www.acwing.com/problem/content/2060/

#include "unordered_set"
#include "iostream"

using namespace std;

int str2int(string &target) {
	int ans = 0;
	for (int i = 0, length = target.size(); i < length; i++) {
		ans = ans * 3 + target[i] - '0';
	}
	return ans;
}

int main() {
	string str2, str3;
	cin >> str2 >> str3;
	int len2 = (int) str2.size(), len3 = (int) str3.size();
	int num2 = 0;
	for (int i = 0; i < len2; i++) {
		num2 <<= 1;
		num2 |= str2[i] - '0';
	}
	if (str2[0] == '0') {
		cout << (num2 ^ (1 << (len2 - 1)));
		return 0;
	}
	unordered_set<int> container;
	for (int i = 0, temp = 1; i < len2; i++, temp <<= 1) {
		container.insert(num2 ^ temp);
	}
	for (int i = 0; i < len3; i++) {
		char temp = str3[i];
		for (char j = '0'; j <= '2'; j++) {
			if (j != temp) {
				str3[i] = j;
				int ans = str2int(str3);
				if (container.count(ans)) {
					cout << ans;
					return 0;
				}
			}
		}
		str3[i] = temp;
	}
	return 0;
}
