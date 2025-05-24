// http://oj.daimayuan.top/course/15/problem/783

#include <cstring>
#include <iostream>
#include <vector>

using std::vector;

template <typename T>
inline void read(T &x) {
    x = 0;
    bool neg = false;
    char c = getchar();
    while (c < 48 || c > 57) {
        if (c == '-') {
            neg = true;
        }
        c = getchar();
    }
    while (c >= 48 && c <= 57) {
        x = (x << 3) + (x << 1) + (c ^ 48);
        c = getchar();
    }
    if (neg) {
        x = -x;
    }
}

int numstk[20];

template <typename T>
inline void write(T x) {
    int tempLen = 0;
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    while (x > 9) {
        numstk[tempLen++] = x % 10;
        x /= 10;
    }
    numstk[tempLen++] = x;
    for (int i = tempLen - 1; i >= 0; i--) {
        putchar(numstk[i] ^ 48);
    }
    putchar('\n');
}

int length = 0, *memo;
vector<int> *container;
vector<long long> *shortPart;

int main() {  // 根据序列长度分治, 短序列按照长度分组维护
    int n, q;
    read(n), read(q);
    container = new vector<int>[n + 1];
    int left = 1, right = q;
    while (left <= right) {
        int mid = (left + right) >> 1;
        if (mid <= q / mid) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    int limit = right;
    memo = new int[limit];
    shortPart = new vector<long long>[limit + 1];
    for (int k = 0, op, x, y; k < q; k++) {
        read(op), read(x);
        if (op == 1) {
            read(y);
            int size = (int)container[x].size();
            container[x].push_back(y);
            if (size <= limit) {
                for (int i = 0; i < size; i++) {
                    shortPart[size][i] -= container[x][i];
                }
                if (size++ == limit) {
                    memo[length++] = x;
                } else {
                    if (shortPart[size].empty()) {
                        shortPart[size] = vector<long long>(size, 0);
                    }
                    for (int i = 0; i < size; i++) {
                        shortPart[size][i] += container[x][i];
                    }
                }
            }
        } else {
            long long ans = 0;
            for (int i = 1; i <= limit; i++) {
                if (shortPart[i].empty()) {
                    continue;
                }
                ans += shortPart[i][x % shortPart[i].size()];
            }
            for (int i = 0; i < length; i++) {
                ans += container[memo[i]][x % container[memo[i]].size()];
            }
            write(ans);
        }
    }
    return 0;
}