// https://www.acwing.com/problem/content/description/4087/

#include "iostream"

using namespace std;

int sizes[101], root[101];

int find(int idx) {
    while (idx != root[idx]) {
        root[idx] = root[root[idx]];
        idx = root[idx];
    }
    return idx;
}

void merge(int a, int b) {
    int idx1 = find(a), idx2 = find(b);
    if (idx1 == idx2) {
        return;
    }
    if (sizes[idx1] < sizes[idx2]) {
        sizes[idx2] += sizes[idx1];
        root[idx1] = idx2;
    } else {
        sizes[idx1] += sizes[idx2];
        root[idx2] = idx1;
    }
}

int main() {
    int n;
    cin >> n;
    int a[n + 1], d[n + 1];
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sizes[i] = 1;
        root[i] = i;
    }
    for (int i = 1; i <= n; i++) {
        cin >> d[i];
    }
    for (int i = 1; i <= n; i++) {
        if (i + d[i] <= n) {
            merge(i, i + d[i]);
        }
    }
    for (int i = n; i >= 1; i--) {
        if (i - d[i] >= 1) {
            merge(i, i - d[i]);
        }
    }
    for (int i = 1; i <= n; i++) {
        if (find(a[i]) != find(i)) {
            cout << "NO";
            return 0;
        }
    }
    cout << "YES";
    return 0;
}
