// https://www.acwing.com/problem/content/4074/

#include "iostream"
#include "unordered_set"

using namespace std;

int main() {
    string loc;
    int loc1[2], loc2[2];
    cin >> loc;
    loc1[0] = loc[0] - 'a', loc1[1] = loc[1] - '1';
    cin >> loc;
    loc2[0] = loc[0] - 'a', loc2[1] = loc[1] - '1';
    unordered_set<int> container;
    container.insert(loc1[0] * 10 + loc1[1]);
    container.insert(loc2[0] * 10 + loc2[1]);
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (row == loc1[0] ||
                    col == loc1[1] ||
                    abs(row - loc1[0]) == 1 && abs(col - loc1[1]) == 2 ||
                    abs(row - loc1[0]) == 2 && abs(col - loc1[1]) == 1 ||
                    abs(row - loc2[0]) == 1 && abs(col - loc2[1]) == 2 ||
                    abs(row - loc2[0]) == 2 && abs(col - loc2[1]) == 1) {
                container.insert(row * 10 + col);
            }
        }
    }
    cout << 64 - (int) container.size();
}

