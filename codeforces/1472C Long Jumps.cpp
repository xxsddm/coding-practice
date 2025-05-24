// https://codeforces.com/problemset/problem/1472/C

#include "iostream"

using namespace std;

int calculate(int* nums, int length) {  // DP
    int ans = 0;
    for (int i = length - 1; i >= 0; i--) {
        if (i + nums[i] < length) {
            nums[i] += nums[i + nums[i]];
        }
        ans = max(ans, nums[i]);
    }
    return ans;
}

int main() {
    int turns;
    cin >> turns;
    for (int i = 0; i < turns; i++) {
        int length;
        cin >> length;
        int nums[length];
        for (int idx = 0; idx < length; idx++) {
            cin >> nums[idx];
        }
        cout << calculate(nums, length) << endl;
    }
}
