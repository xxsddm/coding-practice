// https://codeforces.com/problemset/problem/1606/E

#define ll long long
#define mod 998244353

#include "iostream"
#include "cstring"

using namespace std;

int add(int num1, int num2) {
    return (num1 + num2) % mod;
}

int mul(int num1, int num2) {
    ll ans = (ll) num1 * num2;
    ans %= mod;
    return (int) ans;
}

int main() {    // DP
    int n, x;
    scanf("%d %d", &n, &x);
    int dp[n + 1][x + 1], c[n + 1][n + 1];
    memset(dp, 0, sizeof(dp));
    dp[n][0] = 1;   // 本轮开始时,当前剩余生存人数,生存者受到的总伤害 -> 情况数量
    for (int i = 0; i <= n; i++) {  // C_i^{j}
        c[i][0] = 1;
        c[i][i] = 1;
        for (int j = 1; j < i; j++) {
            c[i][j] = add(c[i - 1][j - 1], c[i - 1][j]);
        }
    }
    for (int rest = n; rest >= 2; rest--) {
        for (int damage = n - rest; damage <= x; damage++) {
            if (dp[rest][damage] == 0) {
                continue;
            }
            // 由当前人数和受到伤害,枚举本轮结束后(下轮开始时)剩余人数
            int nextDamage = min(x, damage + rest - 1), hurt = nextDamage - damage, pow = 1, temp = dp[rest][damage];
            for (int nextRest = rest; nextRest >= 0; nextRest--) {
                // 剩余生存者受到上轮伤害固定,可推得上轮淘汰者在上轮开始时剩余血量范围[1,hurt](hurt正好淘汰)
                dp[nextRest][nextDamage] = add(dp[nextRest][nextDamage], mul(temp, mul(c[rest][nextRest], pow)));
                pow = mul(pow, hurt);
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= x; i++) {
        ans = add(ans, dp[0][i]);
    }
    cout << ans;
}
