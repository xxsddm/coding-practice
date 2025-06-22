# https://codeforces.com/problemset/problem/2114/F

INF = 10 ** 9

def gcd(a, b):
    while b:
        a, b = b, a % b
    return a

# 计算num最少多少次被不超过k的正整数整除, 最终得到1
def calc(num, k):
    factor = 1
    container = []
    while factor <= num // factor:  # 获取num的所有因数, 因数数量级约为num的1/3次方
        temp = num // factor
        if factor * temp == num:
            container.append(factor)
            if factor != temp:
                container.append(temp)
        factor += 1
    container.sort()
    length = len(container)
    dp = [INF] * length
    dp[0] = 0
    for i in range(1, length):  # 整除过程, 只需要考虑因数
        x1 = container[i]
        if x1 <= k:
            dp[i] = 1
            continue
        for j in range(i - 1, -1, -1):
            x2 = container[j]
            if x2 * k < x1:
                break
            if x1 % x2:
                continue
            dp[i] = min(dp[i], dp[j] + 1)
    res = dp[-1]
    return res

def solve():
    x, y, k = map(int, input().split())
    factor = gcd(x, y)
    x //= factor
    y //= factor
    temp1 = calc(x, k)
    if temp1 == INF:
        print(-1)
        return
    temp2 = calc(y, k)
    if temp2 == INF:
        print(-1)
        return
    print(temp1 + temp2)
    return

if __name__ == "__main__":
    T = int(input())
    for _ in range(T):
        solve()