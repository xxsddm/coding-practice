// https://www.acwing.com/problem/content/4198/

#define ll long long

#include "iostream"
#include "algorithm"
#include "cstring"
#include "vector"

using namespace std;

int main() {
    int n;
    cin >> n;
    ll counter[n + 1];
    memset(counter, 0, sizeof(counter));
    vector<pair<ll, int>> container;
    for (int i = 0; i < n; i++) {
        ll left, right;
        cin >> left >> right;
        container.emplace_back(left, 1);
        container.emplace_back(right + 1, -1);
    }
    sort(container.begin(), container.end());
    int count = 1;
    for (int i = 1, length = (int) container.size(); i < length; i++) {
        if (container[i].first > container[i - 1].first) {
            counter[count] += container[i].first - container[i - 1].first;
        }
        count += container[i].second;
    }
    counter[count]++;
    for (int i = 1; i <= n; i++) {
        cout << counter[i] << " ";
    }
}
