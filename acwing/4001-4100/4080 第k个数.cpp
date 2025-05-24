// https://www.acwing.com/problem/content/4083/

#define ll long long

#include "iostream"

using namespace std;

ll n, m, k;

bool check(ll target) {
    ll sum = 0;
    for (int i = 1; i <= n && target / i > 0; i++) {
        sum += min(m, target / i);
        if (sum >= k) {
            return true;
        }
    }
    return false;
}

int main() {
    cin >> n >> m >> k;
    ll left = 1, right = n * m;
    while (left <= right) {
        ll mid = (left + right) >> 1;
        if (check(mid)) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    cout << left << endl;
    return 0;
}
