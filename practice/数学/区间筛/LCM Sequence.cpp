// https://atcoder.jp/contests/abc412/tasks/abc412_e

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<long long> euler(long long limit) {
    ++limit;
    vector<bool> isPrime(limit, true);
    vector<long long> primeList;
    for (long long i = 2; i < limit; ++i) {
        if (isPrime[i]) {
            primeList.push_back(i);
        }
        for (long long p : primeList) {
            long long temp = i * p;
            if (temp >= limit) {
                break;
            }
            isPrime[temp] = false;
            if (i % p == 0) {
                break;
            }
        }
    }
    return primeList;
}

int main() {
    long long L, R;
    scanf("%lld %lld", &L, &R);
    vector<long long> primeList = euler(sqrt(R) + 2);
    int length = (int) (R - L + 1);
    vector<bool> visited(length, false);
    int ans = 1;
    // 区间筛
    for (long long prime : primeList) {
        for (long long num = (L / prime + 1) * prime; num <= R; num += prime) {
            if (visited[num - L]) {
                continue;
            }
            visited[num - L] = true;
            long long temp = num;
            while (temp % prime == 0) {
                temp /= prime;
            }
            if (temp == 1) {    // 指数最大的, 产生新数
                ++ans;
            }
        }
    }
    for (int i = 2; i < length; ++i) {  // 本身为质数的, 也会导致指数最大
        if (!visited[i]) {
            ++ans;
        }
    }
    printf("%d", ans);
    return 0;
}