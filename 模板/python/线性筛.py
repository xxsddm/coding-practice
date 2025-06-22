def euler(limit: int) -> list[int]:
    limit += 1
    isPrime = [True] * limit
    primeList = []
    for i in range(2, limit):
        if isPrime[i]:
            primeList.append(i)
        for prime in primeList:
            temp = i * prime
            if temp >= limit:
                break
            isPrime[temp] = False
            if i % prime == 0:
                break
    return primeList