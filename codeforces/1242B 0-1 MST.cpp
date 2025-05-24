// https://codeforces.com/problemset/problem/1242/B

#include "iostream"
#include "vector"
#include "queue"
#include "unordered_set"
#include "unordered_map"

using namespace std;

int find(int idx, int *root) {
    while (idx != root[idx]) {
        root[idx] = root[root[idx]];
        idx = root[idx];
    }
    return idx;
}

// 合并并返回作为子树(被并入较大树)的节点
int merge(int idx1, int idx2, int *root, int *sizes, unordered_map<int, int> *member) {
    int set1 = find(idx1, root), set2 = find(idx2, root);
    if (set1 == set2) {
        return 0;
    }
    if (sizes[set1] < sizes[set2]) {
        root[set1] = set2;
        sizes[set2] += sizes[set1];
        for (auto &[k,v]: member[set1]) {
            member[set2][k] += v;
        }
        return set1;
    } else {
        root[set2] = set1;
        sizes[set1] += sizes[set2];
        for (auto &[k,v]: member[set2]) {
            member[set1][k] += v;
        }
        return set2;
    }
}

// 检查节点node(可能已与其他根节点合并)是否可与根节点source合并
int link(int node, int source, int *root, int *sizes, unordered_map<int, int> *member) {
    if (member[source].count(node) == 0 ||
            member[source][node] < sizes[source]){
        // 若可合并,返回被合并的子树节点(可能是原根节点)
        return merge(node, source, root, sizes, member);
    }
    return -1;
}

int main() {    // 计算0路径点集数量
    int V, E;
    unordered_set<int> counter;     // 根节点集合
    scanf("%d %d", &V, &E);
    int root[V + 1], sizes[V + 1];
    unordered_map<int, int> member[V + 1];  // 记录根节点及其包含的子节点到某节点的路径数量
    for (int i = 1; i <= V; i++) {
        root[i] = i;
        sizes[i] = 1;
    }
    for (int i = 0; i < E; i++) {
        int node1, node2;
        scanf("%d %d", &node1, &node2);
        if (node1 > node2) {
            swap(node1, node2);
        }
        // 小索引指向大索引的路径(因为后面从前往后枚举节点,则只有枚举的节点之前的节点需要路径)
        member[node1][node2] = 1;
    }
    // 从小到大枚举节点,并枚举之前形成的根节点
    // 若根节点及其子节点(树)指向当前枚举节点的长度1路径数量小于数的节点数,说明存在连接树和节点的0路径
    for (int i = 1; i <= V; i++) {
        unordered_set<int> deleting;
        for (int source: counter) {
            if (deleting.count(source) == 1) {
                continue;
            }
            deleting.insert(link(i, source, root, sizes, member));
        }
        counter.insert(i);
        for (int source: deleting) {
            counter.erase(source);
        }
    }
    cout << counter.size() - 1;
}
