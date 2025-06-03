#include <vector>

using namespace std;

class LCA {
public:
    int size;
    vector<vector<int>> adj, anc;
    vector<int> lg2, depth;

    LCA(int root, const vector<pair<int, int>> &edgeList): root(root) {
        size = (int) edgeList.size() + 2;
        adj.resize(size);
        anc.resize(size);
        lg2.resize(size);
        depth.resize(size, 0);
        for (auto& [u, v] : edgeList) {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        lg2[0] = 0;
        for (int i = 1; i < size; ++i) {
            lg2[i] = lg2[i - 1] + (i == 1 << lg2[i - 1]);
        }
        dfs(root, -1);
    }

    void dfs(int node, int prevNode) {
        int curDepth = depth[node];
        int length = lg2[curDepth];
        anc[node].resize(length);
        if (length) {
            anc[node][0] = prevNode;
        }
        for (int i = 1; i < length; ++i) {
            anc[node][i] = anc[anc[node][i - 1]][i - 1];
        }
        for (int nextNode : adj[node]) {
            if (nextNode == prevNode || depth[nextNode]) {
                continue;
            }
            depth[nextNode] = curDepth + 1;
            dfs(nextNode, node);
        }
    }

    int query(int u, int v) {
        if (depth[u] < depth[v]) {
            swap(u, v);
        }
        while (depth[u] > depth[v]) {
            u = anc[u][lg2[depth[u] - depth[v]] - 1];
        }
        if (u == v) {
            return u;
        }
        for (int i = lg2[depth[u]] - 1; i >= 0; --i) {
            if (i < lg2[depth[u]] && anc[u][i] != anc[v][i]) {
                u = anc[u][i];
                v = anc[v][i];
            }
        }
        return anc[u][0];
    }
};