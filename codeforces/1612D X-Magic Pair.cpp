// https://codeforces.com/problemset/problem/1612/D

#define ll long long

#include "iostream"
#include "utility"
#include "queue"
#include "unordered_set"

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        ll a, b, x;
        cin >> a >> b >> x;
        string ans = "NO";
        if (a > b) {
            swap(a, b);
        }
        while (b >= x && a > 0) {
            if (x >= a && x <= b && (b - x) % a == 0) {
                ans = "YES";
                break;
            }
            ll temp = b;
            b = a;
            a = temp % a;
        }
        cout << ans << endl;
    }
    return 0;
}
