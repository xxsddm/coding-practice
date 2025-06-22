# https://atcoder.jp/contests/abc411/tasks/abc411_g

N, M = map(int, input().split())
counter: list[list[int]] = [[0] * N for _ in range(N)]
for i in range(M):
    u, v = map(int, input().split())
    u -= 1
    v -= 1
    counter[u][v] += 1
    counter[v][u] += 1
MOD = 998244353

def mult(x, y):
    res = x * y
    if res >= MOD:
        res %= MOD
    return res

def add(x, y):
    res = x + y
    if res >= MOD:
        res -= MOD
    return res

def power(x, p):
    res = 1
    temp = x
    while p:
        if p & 1:
            res = mult(res, temp)
        temp = mult(temp, temp)
        p >>= 1
    return res

ans = 0
length = 1 << N
# dp[i][j]当前经过节点状态i, 且当前在节点j时, 可行的路径数量
dp = [[0 for _ in range(N)] for _ in range(length)] # 最小点作为环的起点
for i in range(N):
    dp[1 << i][i] = 1
for status in range(length):
    lowBit = status & -status
    for node in range(N):
        curCount = dp[status][node]
        if not curCount:
            continue
        for nextNode in range(N - 1, -1, -1):
            nextBit = 1 << nextNode
            if nextBit <= lowBit:
                break
            if nextBit & status:
                continue
            count = counter[node][nextNode]
            if not count:
                continue
            nextStatus = status | nextBit
            dp[nextStatus][nextNode] = add(dp[nextStatus][nextNode], mult(curCount, count))
for status in range(length):
    lowBit = status & -status
    for node in range(N):
        curCount = dp[status][node]
        if not curCount:
            continue
        for nextNode in range(N):
            nextBit = 1 << nextNode
            if nextBit < lowBit:
                continue
            count = counter[node][nextNode]
            if status.bit_count() > 2:
                ans = add(ans, mult(curCount, count))
            else:
                ans = add(ans, count * (count - 1))
            break
ans = mult(ans, power(2, MOD - 2))  # 同环有2个方向, 产生2次计算
print(ans)
