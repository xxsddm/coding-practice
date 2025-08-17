// https://atcoder.jp/contests/abc415/tasks/abc415_f

#include <vector>
#include <iostream>

using namespace std;

struct Info {
    int value = 0, left = 0, right = 0, size = 0;

    void refresh(const Info &next1, const Info &next2, bool flag) {
        value = max(next1.value, next2.value);
        left = next1.left;
        right = next2.right;
        if (!flag) {
            return;
        }
        value = max(value, next1.right + next2.left);
        if (next1.left == next1.size) {
            left = next1.left + next2.left;
        }
        if (next2.right == next2.size) {
            right = next2.right + next1.right;
        }
    }
};

vector<Info> tree;
char* word;

void build(int node, int start, int end) {
    if (start == end) {
        Info &info = tree[node];
        info.value = info.left = info.right = info.size = 1;
        return;
    }
    int nextNode1 = node * 2 + 1, nextNode2 = nextNode1 + 1;
    int mid = (start + end) >> 1;
    build(nextNode1, start, mid);
    build(nextNode2, mid + 1, end);
    Info &info = tree[node], &nextInfo1 = tree[nextNode1], &nextInfo2 = tree[nextNode2];
    info.size = end - start + 1;
    info.refresh(nextInfo1, nextInfo2, word[mid] == word[mid + 1]);
}

void change(int node, int start, int end, int idx) {
    if (idx < start || idx > end) {
        return;
    }
    if (start == end) {
        return;
    }
    int nextNode1 = node * 2 + 1, nextNode2 = nextNode1 + 1;
    int mid = (start + end) >> 1;
    change(nextNode1, start, mid, idx);
    change(nextNode2, mid + 1, end, idx);
    Info &info = tree[node], &nextInfo1 = tree[nextNode1], &nextInfo2 = tree[nextNode2];
    info.refresh(nextInfo1, nextInfo2, word[mid] == word[mid + 1]);
}

Info query(int node, int start, int end, int left, int right) {
    if (left <= start && right >= end) {
        return tree[node];
    }
    int nextNode1 = node * 2 + 1, nextNode2 = nextNode1 + 1;
    int mid = (start + end) >> 1;
    if (mid >= right) {
        return query(nextNode1, start, mid, left, right);
    } else if (mid < left) {
        return query(nextNode2, mid + 1, end, left, right);
    }
    Info nextInfo1 = query(nextNode1, start, mid, left, right);
    Info nextInfo2 = query(nextNode2, mid + 1, end, left, right);
    Info info = tree[node];
    info.refresh(nextInfo1, nextInfo2, word[mid] == word[mid + 1]);
    return info;
}

int main() {    // 维护区间的左端, 右端, 全局最大连续子串长度
    int N, Q;
    scanf("%d %d", &N, &Q);
    word = new char[N + 5];
    scanf("%s", word);
    tree.resize(N << 2);
    build(0, 0, N - 1);
    char x;
    for (int k = 0, op, l, r, i; k < Q; ++k) {
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d %c", &i, &x);
            --i;
            word[i] = x;
            change(0, 0, N - 1, i);
        } else {
            scanf("%d %d", &l, &r);
            --l, --r;
            Info res = query(0, 0, N - 1, l, r);
            printf("%d\n", res.value);
        }
    }
    return 0;
}

// 使用模板, by gpt
//#include <bits/stdc++.h>
//using namespace std;
//
///**
// * 线段树模板
// *
// * 注意：Info 必须包含 hasLazy 字段（用于模板静态检查或运行时代码约定）
// */
//template<
//        typename Info,
//        typename Merge,     // Info operator()(Info &left, Info &right)
//        typename ApplyLazy  // void operator()(Info &nodeInfo, Info &lazyInfo, int nodeLength)
//>
//class SegmentTree {
//public:
//    SegmentTree(int length, Merge mergeFn, ApplyLazy applyLazyFn, Info neutralInfo)
//            : length(length), mergeFn(mergeFn), applyLazyFn(applyLazyFn), neutralInfo(neutralInfo)
//    {
//        tree.resize(4 * length + 5, this->neutralInfo);
//    }
//
//    // arr: [0, length - 1] Info 数组, 对应树的[1, length], 初始化时 arr[i].hasLazy 应为 false.
//    void build(vector<Info> &arr) {
//        build(1, 1, length, arr);
//    }
//
//    // 在 [left, right] 上应用 lazyInfo(lazyInfo 中的懒字段应设置好)
//    void change(int left, int right, Info &lazyInfo) {
//        change(1, 1, length, left, right, lazyInfo);
//    }
//
//    // 查询 [left, right] 的聚合 Info(返回的数据部分为聚合结果)
//    Info query(int left, int right) {
//        return query(1, 1, length, left, right);
//    }
//
//private:
//    int length;
//    vector<Info> tree;
//    Merge mergeFn;
//    ApplyLazy applyLazyFn;
//    Info neutralInfo;   // 设置无效值
//
//    void build(int node, int start, int end, vector<Info> &arr) {
//        if (start == end) {
//            tree[node] = arr[start - 1];
//            // 保证叶节点没有未下推的 lazy
//            tree[node].hasLazy = false;
//            return;
//        }
//        int mid = (start + end) >> 1;
//        int leftNode = node << 1, rightNode = leftNode | 1;
//        build(leftNode, start, mid, arr);
//        build(rightNode, mid + 1, end, arr);
//        tree[node] = mergeFn(tree[leftNode], tree[rightNode]);
//        tree[node].hasLazy = false;
//    }
//
//    // 将 lazyInfo 应用到 tree[node]
//    void applyToNode(int node, Info &lazyInfo, int start, int end) {
//        int nodeLength = end - start + 1;
//        // applyLazyFn 应当负责把 node 的 hasLazy / lazyVal 等设置为合成后的状态
//        applyLazyFn(tree[node], lazyInfo, nodeLength);
//    }
//
//    // 将当前节点的 lazy 下推到子节点
//    void pushDown(int node, int start, int end) {
//        Info &curInfo = tree[node];
//        if (!curInfo.hasLazy) {
//            return;
//        }
//        int mid = (start + end) >> 1;
//        int leftNode = node << 1, rightNode = leftNode | 1;
//        // 把当前节点作为 lazyInfo 发给左右子节点
//        applyToNode(leftNode, curInfo, start, mid);
//        applyToNode(rightNode, curInfo, mid + 1, end);
//        // 清除父节点的懒标记(保留其它字段不覆盖数据)
//        curInfo.hasLazy = false;
//    }
//
//    void change(int node, int start, int end, int left, int right, Info &lazyInfo) {
//        if (left > end || right < start) {
//            return;
//        }
//        if (left <= start && end <= right) {
//            applyToNode(node, lazyInfo, start, end);
//            return;
//        }
//        pushDown(node, start, end);
//        int mid = (start + end) >> 1;
//        int leftNode = node << 1, rightNode = leftNode | 1;
//        if (left <= mid) {
//            change(leftNode, start, mid, left, right, lazyInfo);
//        }
//        if (right > mid) {
//            change(rightNode, mid + 1, end, left, right, lazyInfo);
//        }
//        tree[node] = mergeFn(tree[leftNode], tree[rightNode]);
//    }
//
//    Info query(int node, int start, int end, int left, int right) {
//        if (left > end || right < start) {
//            return neutralInfo;
//        }
//        if (left <= start && end <= right) {
//            return tree[node];
//        }
//        pushDown(node, start, end);
//        int mid = (start + end) >> 1;
//        int leftNode = node << 1, rightNode = leftNode | 1;
//        if (right <= mid) {
//            return query(leftNode, start, mid, left, right);
//        }
//        if (left > mid)  {
//            return query(rightNode, mid + 1, end, left, right);
//        }
//        Info leftInfo = query(leftNode, start, mid, left, right);
//        Info rightInfo = query(rightNode, mid + 1, end, left, right);
//        return mergeFn(leftInfo, rightInfo);
//    }
//};
//
//// ========================= 使用模板重写的题目代码 =========================
//
//struct Info {
//    int value = 0;    // 最大连续子串长度（区间内）
//    int leftVal = 0;  // 从左端开始的连续相同字符长度
//    int rightVal = 0; // 从右端开始的连续相同字符长度
//    int size = 0;     // 区间长度
//    bool hasLazy = false; // 模板约定字段（本问题不使用懒标记传递）
//    char leftChar = 0;    // 区间最左字符
//    char rightChar = 0;   // 区间最右字符
//
//    Info() = default;
//
//    // convenience constructor
//    Info(int val, int l, int r, int sz, char lc, char rc)
//            : value(val), leftVal(l), rightVal(r), size(sz),
//              hasLazy(false), leftChar(lc), rightChar(rc) {}
//
//    // refresh 基于左右子段以及跨段是否相等
//    void refresh(const Info &a, const Info &b) {
//        // handle empty segments
//        if (a.size == 0) {
//            *this = b;
//            return;
//        }
//        if (b.size == 0) {
//            *this = a;
//            return;
//        }
//        size = a.size + b.size;
//        leftChar = a.leftChar;
//        rightChar = b.rightChar;
//
//        value = max(a.value, b.value);
//        bool eq = (a.rightChar == b.leftChar);
//        if (eq) {
//            value = max(value, a.rightVal + b.leftVal);
//        }
//
//        leftVal = a.leftVal;
//        if (a.leftVal == a.size && eq) {
//            leftVal = a.leftVal + b.leftVal;
//        }
//
//        rightVal = b.rightVal;
//        if (b.rightVal == b.size && eq) {
//            rightVal = b.rightVal + a.rightVal;
//        }
//
//        hasLazy = false;
//    }
//};
//
//// Merge function object：合并两个 Info
//struct InfoMerge {
//    Info operator()(const Info &l, const Info &r) const {
//        if (l.size == 0) return r;
//        if (r.size == 0) return l;
//        Info res;
//        res.size = l.size + r.size;
//        res.leftChar = l.leftChar;
//        res.rightChar = r.rightChar;
//
//        res.value = max(l.value, r.value);
//        bool eq = (l.rightChar == r.leftChar);
//        if (eq) res.value = max(res.value, l.rightVal + r.leftVal);
//
//        res.leftVal = l.leftVal;
//        if (l.leftVal == l.size && eq) res.leftVal = l.leftVal + r.leftVal;
//
//        res.rightVal = r.rightVal;
//        if (r.rightVal == r.size && eq) res.rightVal = r.rightVal + l.rightVal;
//
//        res.hasLazy = false;
//        return res;
//    }
//};
//
//// ApplyLazy function object：模板接口要求，但此题无懒传播需求。
//// 我们把它实现为“当 lazyInfo.hasLazy==true 时，把节点设为 lazyInfo 的数据（常用于点更新）”。
//// 注意：模板会把当前节点作为 lazyInfo 下推到子节点，但本实现不会设置 hasLazy = true（避免下推循环）。
//struct InfoApplyLazy {
//    void operator()(Info &nodeInfo, Info &lazyInfo, int nodeLength) const {
//        if (!lazyInfo.hasLazy) return;
//        // 将 lazyInfo 表示的“新叶信息”应用到当前节点
//        nodeInfo.leftChar = lazyInfo.leftChar;
//        nodeInfo.rightChar = lazyInfo.rightChar;
//        nodeInfo.size = nodeLength;
//        if (nodeLength == 1) {
//            // 叶节点被更新成单字符
//            nodeInfo.value = 1;
//            nodeInfo.leftVal = 1;
//            nodeInfo.rightVal = 1;
//        } else {
//            // 对于非叶（一般在本题不会发生），尽量处理成保守的状态：
//            if (nodeInfo.leftChar == nodeInfo.rightChar) {
//                nodeInfo.leftVal = nodeInfo.rightVal = nodeLength;
//                nodeInfo.value = nodeLength;
//            } else {
//                // 保守估计：两个端点都只有 1 个连续长度，最大子串至少为 1
//                nodeInfo.leftVal = 1;
//                nodeInfo.rightVal = 1;
//                nodeInfo.value = max(nodeInfo.leftVal, nodeInfo.rightVal);
//            }
//        }
//        // 我们不把 hasLazy 设为 true（因为本题不需要下推懒标记）
//        nodeInfo.hasLazy = false;
//    }
//};
//
//int main() {
//    ios::sync_with_stdio(false);
//    cin.tie(nullptr);
//
//    int N, Q;
//    if (scanf("%d %d", &N, &Q) != 2) return 0;
//
//    // 读字符串
//    string word;
//    word.resize(N + 2); // 1-based空间或更安全的边界（我们后面使用 0..N-1）
//    // 使用 scanf 读 C 字符串更方便
//    static char buf[2000005];
//    scanf("%s", buf);
//    for (int i = 0; i < N; ++i) word[i] = buf[i];
//
//    // 构造 Info 数组（0-based），每个叶表示单字符段
//    vector<Info> arr(N);
//    for (int i = 0; i < N; ++i) {
//        arr[i] = Info(1, 1, 1, 1, word[i], word[i]);
//    }
//
//    // neutral info（用于 query 时无效段返回）
//    Info neutralInfo;
//    neutralInfo.size = 0;
//    neutralInfo.value = neutralInfo.leftVal = neutralInfo.rightVal = 0;
//    neutralInfo.leftChar = neutralInfo.rightChar = 0;
//    neutralInfo.hasLazy = false;
//
//    // 创建线段树
//    InfoMerge mergeFn;
//    InfoApplyLazy applyLazyFn;
//    SegmentTree<Info, InfoMerge, InfoApplyLazy> seg(N, mergeFn, applyLazyFn, neutralInfo);
//    seg.build(arr);
//
//    for (int k = 0; k < Q; ++k) {
//        int op;
//        scanf("%d", &op);
//        if (op == 1) {
//            int idx;
//            char x;
//            scanf("%d %c", &idx, &x);
//            --idx; // 转成 0-based
//            word[idx] = x;
//            // 构造表示新叶的 lazyInfo，并做点更新
//            Info lazyInfo;
//            lazyInfo.hasLazy = true;
//            lazyInfo.leftChar = x;
//            lazyInfo.rightChar = x;
//            // 传入 change 需要 1-based 下标
//            seg.change(idx + 1, idx + 1, lazyInfo);
//        } else {
//            int l, r;
//            scanf("%d %d", &l, &r);
//            --l; --r;
//            Info res = seg.query(l + 1, r + 1);
//            printf("%d\n", res.value);
//        }
//    }
//
//    return 0;
//}
