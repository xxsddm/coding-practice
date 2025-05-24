// https://www.acwing.com/problem/content/4197/

#include "iostream"

using namespace std;

int main() {
    int n, t;
    cin >> n >> t;
    double ans = n;
    for (int i = 0; i < t; i++) {
        ans *= 1.00011;
    }
    printf("%.6f",ans);
}
