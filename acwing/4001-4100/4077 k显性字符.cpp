// https://www.acwing.com/problem/content/4080/

#include "iostream"
#include "string"
#include "cstring"

using namespace std;

bool check(string &target, int num, int length) {
    int counter[26], cum = 0, prev;
    memset(counter, 0, sizeof(counter));
    for (int i = 0; i < num; i++) {
        counter[target[i] - 'a']++;
        cum |= 1 << (target[i] - 'a');
    }
    prev = cum;
    for (int i = num; i < length; i++) {
        int idx1 = target[i - num] - 'a', idx2 = target[i] - 'a';
        counter[idx1]--;
        if (counter[idx1] == 0) {
            prev ^= 1 << idx1;
        }
        counter[idx2]++;
        if (counter[idx2] == 1) {
            prev ^= 1 << idx2;
        }
        cum &= prev;
        if (cum == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    string target;
    cin >> target;
    int length = (int) target.length(), left = 1, right = length;
    while (left <= right) {
        int mid = (left + right) >> 1;
        if (check(target, mid, length)) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    cout << left;
}
