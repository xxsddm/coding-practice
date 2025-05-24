// https://www.acwing.com/problem/content/4086/

#include "iostream"
#include "cstring"

using namespace std;

int main() {
    int n, ans = 1;
    cin >> n;
    int counter[100001];
    memset(counter, 0, sizeof(counter));
    for (int i = 0; i < n; i++) {
        int temp;
        cin >> temp;
        if (temp == 1) {
            continue;
        }
        for (int j = 2; j <= temp / j; j++) {
            if ((temp % j) == 0) {
                ans = max(ans, ++counter[j]);
                while ((temp % j) == 0) {
                    temp /= j;
                }
            }
        }
        ans = max(ans, ++counter[temp]);
    }
    cout << ans;
    return 0;
}
