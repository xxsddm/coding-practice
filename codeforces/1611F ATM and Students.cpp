// https://codeforces.com/problemset/problem/1611/F

#include "iostream"
#include "queue"

using namespace std;

typedef long long ll;

void solve(int *nums, int n, int s) {   // DP
    int maxLength = 0, start = 0, end = 0;
    ll cumsum = s;
    deque<int> container;
    for (int i = 0; i < n; i++) {
        while (cumsum + nums[i] < 0 && !container.empty()) {
            cumsum -= container.front();
            container.pop_front();
        }
        if (cumsum + nums[i] >= 0) {
            container.push_back(nums[i]);
            cumsum += nums[i];
            int length = (int) container.size();    // dp[i]可抵达i的最大长度
            if (length > maxLength) {
                maxLength = length;
                start = i - length + 2;
                end = i + 1;
            }
        }
    }
    if (maxLength == 0) {
        cout << -1 << endl;
        return;
    }
    cout << start << " " << end << endl;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n, s;
        cin >> n >> s;
        int nums[n];
        for (int i = 0; i < n; i++) {
            cin >> nums[i];
        }
        solve(nums, n, s);
    }
}




