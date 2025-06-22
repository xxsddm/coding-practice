#include <vector>

using namespace std;

vector<int> euler(int limit) {
    ++limit;
    vector<bool> isPrime(limit, true);
    vector<int> primeList;
    for (int i = 2; i < limit; ++i) {
        if (isPrime[i]) {
            primeList.push_back(i);
        }
        for (int p : primeList) {
            if ((long long) i * p >= limit) {
                break;
            }
            isPrime[i * p] = false;
            if (i % p == 0) {
                break;
            }
        }
    }
    return primeList;
}