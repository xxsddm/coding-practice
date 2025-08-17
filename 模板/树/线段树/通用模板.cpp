#include <vector>

using namespace std;

/**
 * 线段树模板
 *
 * @tparam Info 线段树各节点信息, 包含lazy值. 必须包含hasLazy字段用于判断
 * @tparam Merge 父节点通过子节点更新的方式
 * @tparam ApplyLazy 父节点向子节点通过lazy修改; 树修改操作也通过该方式传递
 */
template<
        typename Info,
        typename Merge,     // Info operator()(Info &left, Info &right)
        typename ApplyLazy  // void operator()(Info &nodeInfo, Info &lazyInfo, int nodeLength)
>
class SegmentTree {
public:
    /**
     * 初始化线段树
     *
     * @param length 线段树长度length(默认线段树下标[1, n])
     * @param mergeFn 合并节点方式
     * @param applyLazyFn 懒操作更新方式
     * @param neutralInfo 默认无效值, 判断无效场景
     */
    SegmentTree(int length, Merge mergeFn, ApplyLazy applyLazyFn, Info neutralInfo)
            : length(length), mergeFn(mergeFn), applyLazyFn(applyLazyFn), neutralInfo(neutralInfo)
    {
        tree.resize(4 * length + 5, this->neutralInfo);
    }

    // arr: [0, length - 1] Info 数组, 对应树的[1, length], 初始化时 arr[i].hasLazy 应为 false. 也可以完全使用change方式初始化
    void build(vector<Info> &arr) {
        build(1, 1, length, arr);
    }

    // 在 [left, right] 上应用 lazyInfo(lazyInfo 中的懒字段应设置好)
    void change(int left, int right, Info &lazyInfo) {
        change(1, 1, length, left, right, lazyInfo);
    }

    // 查询 [left, right] 的聚合 Info(返回的数据部分为聚合结果)
    Info query(int left, int right) {
        return query(1, 1, length, left, right);
    }

private:
    int length;
    vector<Info> tree;
    Merge mergeFn;
    ApplyLazy applyLazyFn;
    Info neutralInfo;   // 设置无效值

    void build(int node, int start, int end, vector<Info> &arr) {
        if (start == end) {
            tree[node] = arr[start - 1];
            // 保证叶节点没有未下推的 lazy
            tree[node].hasLazy = false;
            return;
        }
        int mid = (start + end) >> 1;
        int leftNode = node << 1, rightNode = leftNode | 1;
        build(leftNode, start, mid, arr);
        build(rightNode, mid + 1, end, arr);
        tree[node] = mergeFn(tree[leftNode], tree[rightNode]);
        tree[node].hasLazy = false;
    }

    // 将 lazyInfo 应用到 tree[node]
    void applyToNode(int node, Info &lazyInfo, int start, int end) {
        int nodeLength = end - start + 1;
        // applyLazyFn 应当负责把 node 的 hasLazy / lazyVal 等设置为合成后的状态
        applyLazyFn(tree[node], lazyInfo, nodeLength);
    }

    // 将当前节点的 lazy 下推到子节点
    void pushDown(int node, int start, int end) {
        Info &curInfo = tree[node];
        if (!curInfo.hasLazy) {
            return;
        }
        int mid = (start + end) >> 1;
        int leftNode = node << 1, rightNode = leftNode | 1;
        // 把当前节点作为 lazyInfo 发给左右子节点
        applyToNode(leftNode, curInfo, start, mid);
        applyToNode(rightNode, curInfo, mid + 1, end);
        // 清除父节点的懒标记(保留其它字段不覆盖数据)
        curInfo.hasLazy = false;
    }

    void change(int node, int start, int end, int left, int right, Info &lazyInfo) {
        if (left > end || right < start) {
            return;
        }
        if (left <= start && end <= right) {
            applyToNode(node, lazyInfo, start, end);
            return;
        }
        pushDown(node, start, end);
        int mid = (start + end) >> 1;
        int leftNode = node << 1, rightNode = leftNode | 1;
        if (left <= mid) {
            change(leftNode, start, mid, left, right, lazyInfo);
        }
        if (right > mid) {
            change(rightNode, mid + 1, end, left, right, lazyInfo);
        }
        tree[node] = mergeFn(tree[leftNode], tree[rightNode]);
    }

    Info query(int node, int start, int end, int left, int right) {
        if (left > end || right < start) {
            return neutralInfo;
        }
        if (left <= start && end <= right) {
            return tree[node];
        }
        pushDown(node, start, end);
        int mid = (start + end) >> 1;
        int leftNode = node << 1, rightNode = leftNode | 1;
        if (right <= mid) {
            return query(leftNode, start, mid, left, right);
        }
        if (left > mid)  {
            return query(rightNode, mid + 1, end, left, right);
        }
        Info leftInfo = query(leftNode, start, mid, left, right);
        Info rightInfo = query(rightNode, mid + 1, end, left, right);
        return mergeFn(leftInfo, rightInfo);
    }
};



//// ================= 示例：模数下区间赋值 + 区间和(applyLazy 同时做应用与合成) =================
//
//using ll = long long;
//
//ll MOD = 998244353;
//int MOD_INT_2 = 998244351; // MOD - 2
//
//ll quickPower(ll x, int p) {
//    ll res = 1 % MOD;
//    ll base = (x % MOD + MOD) % MOD;
//    while (p) {
//        if (p & 1) res = (res * base) % MOD;
//        base = (base * base) % MOD;
//        p >>= 1;
//    }
//    return res;
//}
//
//// Info 同时包含数据与懒标记(赋值)
//struct SumInfo {
//    ll sum;        // 区间和(数据)
//    bool hasLazy;  // 是否有待下推的懒标记
//    ll lazyVal;    // 懒标记的值(赋值语义)
//
//    SumInfo(ll _sum = 0, bool _hasLazy = false, ll _lazyVal = 0)
//            : sum(((_sum % MOD) + MOD) % MOD),
//              hasLazy(_hasLazy),
//              lazyVal(((_lazyVal % MOD) + MOD) % MOD)
//    {}
//};
//
//// Merge：只合并数据部分(不携带 lazy)
//struct SumMerge {
//    SumInfo operator()(SumInfo &a, SumInfo &b) {
//        return SumInfo((a.sum + b.sum) % MOD, false, 0);
//    }
//};
//
//// applyLazy：负责把 lazyInfo 的懒标记应用到 nodeInfo 的数据部分,
//// 并把 lazyInfo 合成为 nodeInfo 的懒标记(赋值覆盖语义)
//struct SumApplyLazy {
//    void operator()(SumInfo &nodeInfo, SumInfo &lazyInfo, int len) {
//        // 1) 应用到数据：区间赋值 -> 区间和 = lazyVal * len
//        nodeInfo.sum = (lazyInfo.lazyVal * (len % MOD)) % MOD;
//        // 2) 合成 lazy：赋值覆盖旧的 lazy(直接复制)
//        nodeInfo.hasLazy = true;
//        nodeInfo.lazyVal = lazyInfo.lazyVal;
//    }
//};
//
//// ================= 主程序(等价于你原来的逻辑) =================
//int main() {
//    ios::sync_with_stdio(false);
//    cin.tie(nullptr);
//
//    int n, m;
//    if (!(cin >> n >> m)) return 0;
//
//    vector<ll> inputVals(n);
//    for (int i = 0; i < n; ++i) cin >> inputVals[i];
//
//    vector<SumInfo> arr(n);
//    for (int i = 0; i < n; ++i) arr[i] = SumInfo(inputVals[i], false, 0);
//
//    SumMerge mergeFn;
//    SumApplyLazy applyLazyFn;
//    SumInfo neutralInfo(0, false, 0);
//
//    SegmentTree<SumInfo, SumMerge, SumApplyLazy> seg(n, mergeFn, applyLazyFn, neutralInfo);
//    seg.build(arr);
//
//    for (int i = 0; i < m; ++i) {
//        int left, right;
//        cin >> left >> right;
//        SumInfo total = seg.query(left, right);
//        ll avg = total.sum * quickPower(right - left + 1, MOD_INT_2) % MOD;
//        SumInfo lazyInfo(0, true, avg); // 仅 lazy 部分有效
//        seg.change(left, right, lazyInfo);
//    }
//
//    for (int i = 1; i <= n; ++i) {
//        SumInfo v = seg.query(i, i);
//        cout << v.sum % MOD << (i == n ? '\n' : ' ');
//    }
//    return 0;
//}
