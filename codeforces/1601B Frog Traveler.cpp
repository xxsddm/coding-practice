// https://codeforces.com/problemset/problem/1601/B

#include "iostream"
#include "queue"
#include "cstring"
#include "stack"

using namespace std;

int main() {    // BFS
    int n;
    cin >> n;
    int a[n + 1], b[n + 1], pre[n + 1];
    a[0] = 0, b[0] = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    memset(pre, -1, sizeof(pre));
    int ans = 0, maxlimit = n;  // 保存下滑前位置上限
    queue<int> nodes;   // 保存下滑前位置,即可锁定下滑前的范围,减少重复continue
    nodes.push(n);
    while (!nodes.empty()) {
        ans++;
        int size = (int) nodes.size();
        for (int i = 0; i < size; i++) {
            int node = nodes.front();
            nodes.pop();
            int afterSlip = node + b[node], minLoc = afterSlip - a[afterSlip];  // 计算下滑后位置和下步跳跃最低位置
            for (int beforeSlip = min(maxlimit, afterSlip); beforeSlip >= minLoc; beforeSlip--) {
                if (beforeSlip <= 0) {
                    cout << ans << endl;
                    pre[0] = node;
                    stack<int> path;
                    for (int k = 0; k != n; k = pre[k]) {
                        path.push(k);
                    }
                    while (!path.empty()) {
                        cout << path.top() << " ";
                        path.pop();
                    }
                    return 0;
                }
                if (pre[beforeSlip] != -1) {    // 已访问
                    continue;
                }
                pre[beforeSlip] = node; // 当前下滑前位置 -> 上一步下滑前位置
                nodes.push(beforeSlip);
            }
            maxlimit = min(maxlimit, afterSlip - a[afterSlip]);
        }
    }
    cout << -1 << endl;
    return 0;
}
