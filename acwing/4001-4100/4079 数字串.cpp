// https://www.acwing.com/problem/content/4082/

#include "iostream"

using namespace std;

int main() {
    string sb;
    for (int i = 1; i <= 1000 && sb.size() <= 1000; i++) {
        sb += to_string(i);
    }
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        cout << sb[n - 1] << endl;
    }
}
