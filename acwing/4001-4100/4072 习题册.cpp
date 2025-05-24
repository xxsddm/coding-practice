// https://www.acwing.com/problem/content/4075/

#include "iostream"
#include "algorithm"
#include "vector"

using namespace std;

int main() {
    int num;
    cin >> num;
    int nums[num][3], length = num, ans = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < num; j++) {
            int temp;
            cin >> temp;
            nums[j][i] = temp;
        }
    }
    cin >> num;
    int target[num];
    for (int i = 0; i < num; i++) {
        int temp;
        cin >> temp;
        target[i] = temp;
    }

    int idxs[3];
    for (int &idx : idxs) {
        idx = 0;
    }
    bool visited[length];
    for (bool &judge: visited) {
        judge = false;
    }
    vector<pair<int, int>> container[3];
    for (int i = 0; i < length; i++) {
        pair<int, int> temp = {nums[i][0], i};
        for (int j = 1; j <= 3; j++) {
            if (nums[i][1] == j || nums[i][2] == j) {
                container[j - 1].emplace_back(temp);
            }
        }
    }
    for (auto &subcontainer : container) {
        sort(subcontainer.begin(), subcontainer.end());
    }

    for (int i = 0; i < num; i++) {
        int loc = target[i] - 1;
        vector<pair<int, int>> &subcontainer = container[loc];
        while (idxs[loc] < subcontainer.size() && visited[subcontainer[idxs[loc]].second]) {
            idxs[loc]++;
        }
        if (idxs[loc] == subcontainer.size()) {
            ans = -1;
            cout << ans;
            if (i != num - 1) {
                cout << ' ';
            }
            continue;
        }
        ans = subcontainer[idxs[loc]].first;
        visited[subcontainer[idxs[loc]++].second] = true;
        cout << ans;
        if (i != num - 1) {
            cout << ' ';
        }
    }
}

