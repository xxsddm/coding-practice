// https://www.acwing.com/problem/content/description/1000/

#include "iostream"

using namespace std;

int main() {	// DP
	int n, m, length = 0;
	scanf("%d %d", &n, &m);
	for (int i = m; i; i >>= 1) {
		length++;
	}
	// opt: 全为1参与运算; nonOpt: 全为0参与运算; temp: 原始值参与运算
	int opt = (1 << length) - 1, nonOpt = 0, temp = m;
	for (int i = 0; i < n; i++) {
		string word;
		int num;
		cin >> word >> num;
		if (word == "AND") {
			opt &= num;
			nonOpt &= num;
			temp &= num;
		} else if (word == "OR") {
			opt |= num;
			nonOpt |= num;
			temp |= num;
		} else {
			opt ^= num;
			nonOpt ^= num;
			temp ^= num;
		}
	}
	// dp考虑当前subLen位(从右往左)为0时, 更高位不变, 更低位随意设定可取得最大值
	// 注意最低位取0时, 更低位随意设定则等价于只考虑最低位的0参与运算结果, 即nonOpt最低位运算结果
	int ans = temp;
	for (int subLen = 1, dp = 0, i = 1; subLen <= length; subLen++, i <<= 1) {
		dp ^= nonOpt & i;
		if (m & i) {
			// 考虑当前subLen位取0, 更低位随意设定的拼接情况
			// temp的高位, dp的低位
			ans = max(ans, (temp >> subLen << subLen) ^ dp);
		}
		dp |= opt & i;
	}
	printf("%d", ans);
	return 0;
}