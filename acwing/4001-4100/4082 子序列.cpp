// https://www.acwing.com/problem/content/4085/

#include "iostream"
#include "cstring"

using namespace std;

int main() {
    string s;
    cin >> s;
    int length = (int) s.length();
    int dp[3];
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < length; i++) {
        char temp = s[i];
        if (temp != 'Q' && temp != 'A') {
            continue;
        }
        if (temp == 'Q') {
            dp[0]++;
            dp[2] += dp[1];
        } else if (i > 0) {
            dp[1] += dp[0];
        }
    }
    cout << dp[2];
    return 0;
}
