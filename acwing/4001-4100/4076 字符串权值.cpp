// https://www.acwing.com/problem/content/4079/

#include "iostream"
#include "string"

using namespace std;

int main() {
    string target;
    cin >> target;
    int ans = 1;
    for (int i = 1; i < 7; i++) {
        if (target[i] == '1') {
            ans += 10;
        } else {
            ans += target[i] - '0';
        }
    }
    cout << ans;
}