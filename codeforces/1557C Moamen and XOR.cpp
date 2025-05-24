// https://codeforces.com/problemset/problem/1557/C

#define ll long long
#define mod 1000000007

#include "iostream"
#include "stack"

using namespace std;

int idx = 1, power2[200001];

int mul(int a, int b) {
    return (int) ((ll) a * b % mod);
}

int solve(int n, int k) {
    if (k == 0) {
        return 1;
    }
    while (idx <= n) {
        power2[idx] = (power2[idx - 1] << 1) % mod;
        idx++;
    }
    int back1 = power2[n], back2 = power2[n - 1];
    bool even = (n & 1) == 0;
    if (!even) {    // 奇数个则不可能严格大于,计算相等情况即(2^(n-1))^k
        int ans = 1;
        for (int i = k, benchmark = back2 + 1, temp = benchmark; i > 0; i >>= 1, temp = mul(temp, temp)) {
            if (i & 1) {
                ans = mul(ans, temp);   // 快速幂
            }
        }
        return ans;
    }
    stack<int> kthPower;
    for (int i = 0, temp = 1; i < k; i++, temp = mul(temp, back1)) {    // (2^n)^i
        // 记录低位组合数(2^n)^i,由第i+1位使用
        kthPower.push(temp);
    }
    int ans = 0, upperCount = 1, benchmark = back2 - 1;   // upperCount记录高位相同的组合数
    // 考虑第i位(二进制)大于的情况(则高位相同,低位任意)
    for (int i = k; i >= 1; i--, kthPower.pop(), upperCount = mul(upperCount, benchmark)) {   // >
        // 仅n为偶数时可能严格大于
        ans = (ans + mul(upperCount, kthPower.top())) % mod;
    }
    ans = (ans + upperCount) % mod;  // == 此时高位相同组合数即相同的组合数
    return ans;
}

int main() {
    int t;
    cin >> t;
    power2[0] = 1;
    for (int i = 0; i < t; i++) {
        int n, k;
        cin >> n >> k;
        cout << solve(n, k) << endl;
    }
}
