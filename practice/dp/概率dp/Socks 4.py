# https://atcoder.jp/contests/abc412/tasks/abc412_f

MOD = 998244353

def add(x: int, y: int) -> int:
    res = x + y
    if res >= MOD:
        res -= MOD
    return res

def mult(x: int, y: int) -> int:
    res = x * y
    if res >= MOD:
        res %= MOD
    return res

def inv(x: int) -> int:
    return pow(x, MOD - 2, MOD)

# 对于数量大于x的count_i, 抽出后放回x. 此时E(x)依赖于E(i)
# 对于数量不大于x的count_i, 抽出后放回i. 此时E(x)只取决于E(x)
# 未抽中x则期望需要+1
N, C = map(int, input().split())
counter = [0]
total = 0
nMax = 0
INVALID = -1
for a in map(int, input().split()):
    counter.append(a)
counter[C] += 1
total = sum(counter)
expect = [INVALID] * (N + 1)    # 当前目标为i时的期望
container = [(counter[i], i) for i in range(1, N + 1)]
container.sort(reverse=True)
cumsum = 0
cumcount = 0
prevExpect = 0
prevColor = 0
for count, color in container:
    if count == counter[prevColor]:
        expect[color] = prevExpect
    else:
        expect[color] = mult(add(total - 1, cumsum), inv(cumcount + count - 1))
    if count == counter[C]:
        expect[C] = expect[color]
        break
    prevColor = color
    prevExpect = expect[color]
    cumsum = add(cumsum, mult(count, expect[color]))
    cumcount += count
print(expect[C])
