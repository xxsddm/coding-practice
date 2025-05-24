// https://www.acwing.com/problem/content/4081/

#include "iostream"
#include "cstring"

#define mod 1000000007

using namespace std;

int main() {
    int T, k, maxR = 0;
    cin >> T >> k;
    int left[T], right[T];
    memset(left, 0, sizeof(left));
    memset(right, 0, sizeof(right));
    for (int i = 0; i < T; i++) {
        cin >> left[i] >> right[i];
        maxR = max(maxR, right[i]);
    }
    int dp[maxR + 1];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    for (int length = 0; length <= maxR; length++) {
        // 当前字符串末端拼接元素得到length+1(/k)情况
        // 1.当前可行字符串末端均拼接"0"(length+1)
        if (length + 1 <= maxR) {
            dp[length + 1] = (dp[length + 1] + dp[length]) % mod;
        }
        // 2.当前可行字符串末端均拼接"1"*k(length+k)
        if (length + k <= maxR) {
            dp[length + k] = (dp[length + k] + dp[length]) % mod;
        }
    }
    // 转换为前缀和
    for (int length = 2; length <= maxR; length++) {
        dp[length] = (dp[length] + dp[length - 1]) % mod;
    }
    dp[0] = 0;
    int ans;
    for (int i = 0; i < T; i++) {
        ans = dp[right[i]] - dp[left[i] - 1];
        if (ans < 0) {
            ans += mod;
        }
        ans %= mod;
        cout << ans << endl;
    }
}
