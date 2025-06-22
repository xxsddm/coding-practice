MOD = 998244353
length = 10000
inv = [0] * length
inv[1] = 1

for i in range(2, length):
    inv[i] = (MOD - MOD // i) * inv[MOD % i]
    inv[i] %= MOD
