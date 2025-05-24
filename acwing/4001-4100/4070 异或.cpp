// https://www.acwing.com/problem/content/4073/

#include "iostream"
using namespace std;

int main() {
    int num, last, maxnum;
    cin >> num;
    while (num--) {
        cin >> last;
        maxnum = max(maxnum, last);
    }
    cout << (maxnum ^ last);
}
