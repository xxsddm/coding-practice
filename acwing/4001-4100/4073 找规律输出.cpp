// https://www.acwing.com/problem/content/4076/

#include "iostream"

using namespace std;

int main() {
    int num;
    cin >> num;
    for (int i = 1; i < num; i++) {
        if (i & 1) {
            cout << "I hate that ";
        } else {
            cout << "I love that ";
        }
    }
    if (num & 1) {
        cout << "I hate it";
    } else {
        cout << "I love it";
    }
}

