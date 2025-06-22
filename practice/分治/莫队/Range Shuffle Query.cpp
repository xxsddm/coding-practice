// https://atcoder.jp/contests/abc405/tasks/abc405_g

#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using std::sort;
using std::vector;

int MOD = 998244353;
long long MOD_LL = 998244353, MOD2 = MOD_LL << 1;

int mult(int x, int y) {
    long long res = (long long) x * y;
    if (res < MOD_LL) {
        return (int) res;
    }
    if (res < MOD2) {
        return (int) (res - MOD_LL);
    }
    return (int) (res % MOD_LL);
}

int length, blockLength;
int counter[250001], blockCounter[501];
int blockDeno[501];
int fact[250001], invFact[250001], inv[250001];

int getPart1(int num) {
    int res = 0;
    int blockIdx = (num - 1) / blockLength;
    for (int i = 0; i < blockIdx; ++i) {
        res += blockCounter[i];
    }
    for (int i = blockIdx * blockLength + 1; i <= num; ++i) {
        res += counter[i];
    }
    res = fact[res];
    return res;
}

int getPart2(int num) {
    int res = 1;
    int blockIdx = (num - 1) / blockLength;
    for (int i = 0; i < blockIdx; ++i) {
        res = mult(res, blockDeno[i]);
    }
    for (int i = blockIdx * blockLength + 1; i <= num; ++i) {
        res = mult(res, invFact[counter[i]]);
    }
    return res;
}

void addNum(int num) {
    int blockIdx = (num - 1) / blockLength;
    ++blockCounter[blockIdx];
    ++counter[num];
    blockDeno[blockIdx] = mult(blockDeno[blockIdx], inv[counter[num]]);
}

void removeNum(int num) {
    int blockIdx = (num - 1) / blockLength;
    --blockCounter[blockIdx];
    blockDeno[blockIdx] = mult(blockDeno[blockIdx], counter[num]);
    --counter[num];
}

struct Info {
    int l, r, x, id;
    Info(int l, int r, int x, int id): l(l), r(r), x(x), id(id) {}
};

int main() {    // 按值域进行根号分治
    int N, Q;
    scanf("%d %d", &N, &Q);
    vector<int> nums(N);
    vector<Info> queryList;
    queryList.reserve(Q);
    for (int i = 0; i < N; ++i) {
        scanf("%d", &nums[i]);
    }
    length = N;
    blockLength = std::sqrt(length) + 0.0001;
    fact[0] = invFact[0] = inv[1] = 1;
    for (int i = 2, temp; i <= length; ++i) {
        temp = MOD / i;
        inv[i] = mult(MOD - temp, inv[MOD - temp * i]); // 线性求逆元
    }
    for (int i = 1; i <= length; ++i) {
        fact[i] = mult(fact[i - 1], i);
        invFact[i] = mult(invFact[i - 1], inv[i]);
    }
    for (int i = 0; i <= blockLength; ++i) {
        blockDeno[i] = 1;
    }
    for (int i = 0, L, R, X; i < Q; ++i) {
        scanf("%d %d %d", &L, &R, &X);
        queryList.emplace_back(L - 1, R - 1, X, i);
    }
    sort(queryList.begin(), queryList.end(), [](const Info& o1, const Info& o2) -> bool {
        int blockIdx1 = o1.l / blockLength, blockIdx2 = o2.l / blockLength;
        if (blockIdx1 == blockIdx2) {
            return (blockIdx1 & 1) ? o2.r < o1.r : o1.r < o2.r;
        }
        return blockIdx1 < blockIdx2;
    });
    vector<int> res(Q);
    int start = 0, end = -1;
    for (auto& q : queryList) {
        auto& [L, R, X, id] = q;
        while (end < R) {
            addNum(nums[++end]);
        }
        while (start > L) {
            addNum(nums[--start]);
        }
        while (end > R) {
            removeNum(nums[end--]);
        }
        while (start < L) {
            removeNum(nums[start++]);
        }
        int part1 = getPart1(X - 1), part2 = getPart2(X - 1);
        res[id] = mult(part1, part2);
    }
    for (auto & n : res) {
        printf("%d\n", n);
    }
    return 0;
}
