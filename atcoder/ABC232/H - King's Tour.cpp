// https://atcoder.jp/contests/abc232/tasks/abc232_h

#include "iostream"
#include "vector"

using namespace std;

vector<pair<int, int>> path(int h, int w, int a, int b) {   // 反转使path起始位置始终为(1,1)
    vector<pair<int, int>> ans;
    // h=2/w=2终止
    if (h == 2) {
        int x = 1, y = 1;
        while (y != b) {
            ans.emplace_back(x, y);
            if (x == 2) {
                y++;
            }
            x = 3 - x;
        }
        for (int i = b, temp = 3 - a; i <= w; i++) {
            ans.emplace_back(temp, i);
        }
        for (int i = w; i >= b; i--) {
            ans.emplace_back(a, i);
        }
        return ans;
    }
    if (w == 2) {
        int x = 1, y = 1;
        while (x != a) {
            ans.emplace_back(x, y);
            if (y == 2) {
                x++;
            }
            y = 3 - y;
        }
        for (int i = a, temp = 3 - b; i <= h; i++) {
            ans.emplace_back(i, temp);
        }
        for (int i = h; i >= a; i--) {
            ans.emplace_back(i, b);
        }
        return ans;
    }
    // 填完第一行，左右反转下轮path
    if (a != 1 && (a != 2 || b != w)) {
        for (int i = 1; i <= w; i++) {
            ans.emplace_back(1, i);
        }
        vector<pair<int, int>> temp = path(h - 1, w, a - 1, w - b + 1);
        for (auto &next : temp) {
            ans.emplace_back(next.first + 1, w - next.second + 1);
        }
        return ans;
    }
    // 填完第一列，上下反转下轮path
    for (int i = 1; i <= h; i++) {
        ans.emplace_back(i, 1);
    }
    vector<pair<int, int>> temp = path(h, w - 1, h - a + 1, b - 1);
    for (auto &next : temp) {
        ans.emplace_back(h - next.first + 1, next.second + 1);
    }
    return ans;
}

int main() {
    int h, w, a, b;
    cin >> h >> w >> a >> b;
    auto temp = path(h, w, a, b);
    for (auto &p : temp) {
        cout << p.first << " " << p.second << endl;
    }
    return 0;
}
