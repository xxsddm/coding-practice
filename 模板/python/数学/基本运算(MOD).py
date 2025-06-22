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

def power(x: int, p: int) -> int:
    res = 1
    temp = x
    while p:
        if p & 1:
            res = mult(res, temp)
        temp = mult(temp, temp)
        p >>= 1
    return res

def div(x: int, y: int) -> int:
    return mult(x, power(y, MOD - 2))