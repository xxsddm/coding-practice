// https://www.acwing.com/problem/content/4078/

#include "iostream"
#include "vector"
#include "cstring"
#include "unordered_map"

using namespace std;

int find(int *root, int idx) {
    while (idx != root[idx]) {
        root[idx] = root[root[idx]];
        idx = root[idx];
    }
    return idx;
}

void merge(int *root, int *sizes, int idx1, int idx2) {
    int set1 = find(root, idx1), set2 = find(root, idx2);
    if (set1 == set2) {
        return;
    }
    if (sizes[set1] < sizes[set2]) {
        root[set1] = set2;
        sizes[set2] += sizes[set1];
    } else {
        root[set2] = set1;
        sizes[set1] += sizes[set2];
    }
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    int colors[n], sizes[n], root[n];
    for (int i = 0; i < n; i++) {
        cin >> colors[i];
        root[i] = i;
        sizes[i] = 1;
    }
    for (int i = 0; i < m; i++) {
        int idx1, idx2;
        cin >> idx1 >> idx2;
        merge(root, sizes, idx1 - 1, idx2 - 1);
    }
    int ans = 0;
    unordered_map<int, unordered_map<int, int>> counter;
    bool visited[n];
    memset(visited, false, sizeof(visited));
    for (int i = 0; i < n; i++) {
        int head = find(root, i);
        if (head == i) {
            continue;
        }
        if (!visited[head]) {
            visited[head] = true;
            counter[head] = unordered_map<int, int>();
            counter[head][colors[head] - 1]++;
        }
        counter[head][colors[i] - 1]++;
    }
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            continue;
        }
        int maxNum = 0, maxIdx = 0;
        for (auto &[idx, num]: counter[i]) {
            if (num > maxNum) {
                maxIdx = idx;
                maxNum = num;
            }
        }
        if (colors[i] != maxIdx + 1) {
            colors[i] = maxIdx + 1;
            ans++;
        }
    }
    for (int i = 0; i < n; i++) {
        if (colors[i] != colors[find(root, i)]) {
            ans++;
        }
    }
    cout << ans;
}

