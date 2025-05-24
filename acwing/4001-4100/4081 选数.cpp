// https://www.acwing.com/problem/content/4084/

#define ll long long

#include "iostream"
#include "cstring"

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    int ans = 0, m = 25 * n, num2[n + 1], num5[n + 1], dp[k + 1][m + 1];
    memset(num2, 0, sizeof(num2));
    memset(num5, 0, sizeof(num5));
    memset(dp, -0x3f, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        ll num;
        cin >> num;
        while (num % 5 == 0) {
            num /= 5;
            num5[i]++;
        }
        while ((num & 1) == 0) {
            num >>= 1;
            num2[i]++;
        }
    }
    // 二维背包
    for (int i = 1; i <= n; i++) {
        //
        for (int j = k; j >= 1; j--) {
            for (int l = m; l >= num5[i]; l--) {
                dp[j][l] = max(dp[j][l], dp[j - 1][l - num5[i]] + num2[i]);
            }
        }
    }
    for (int i = 0; i <= m; i++) {
        ans = max(ans, min(dp[k][i], i));
    }
    cout << ans << endl;
    return 0;
}



