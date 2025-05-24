// https://codeforces.com/problemset/problem/1610/C

#include "iostream"

using namespace std;

bool check(int num, int n, const int *lower, const int *upper) {    // 检查是否可以组成num个元素
    int idx = 0;
    for (int i = 0; i < n && idx < num; i++) {
        // 选择第idx个,需要满足左侧(idx个)不超过lower[i],右侧(未填入的num-1-idx个)不超过upper[i]
        if (lower[i] >= idx && upper[i] >= num - 1 - idx) {
            idx++;
        }
    }
    return idx == num;
}

int calculate(int n, const int *lower, const int *upper) {  // 二分
    int left = 0, right = n;
    while (left <= right) {
        int mid = (left + right) >> 1;
        if (check(mid, n, lower, upper)) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return right;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int lower[n], upper[n];
        for (int i  = 0; i < n; i++) {
            cin >> upper[i] >> lower[i];
        }
        cout << calculate(n, lower, upper) << endl;
    }
    return 0;
}
