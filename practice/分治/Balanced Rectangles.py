# https://atcoder.jp/contests/abc410/tasks/abc410_f

BASE = 300000
memo = [0] * (BASE * 2 + 1)

def solve():
    H, W = map(int, input().split())
    counter = [[0] * (W + 1) for _ in range(H + 1)]
    for i in range(1, H + 1):
        word = input()
        for j in range(1, W + 1):
            if word[j - 1] == '#':
                counter[i][j] = 1
            else:
                counter[i][j] = -1

    if H > W:   # 使用长, 宽中较小的枚举上下界
        nextCounter = [[0] * (H + 1) for _ in range(W + 1)]
        for i in range(1, H + 1):
            for j in range(1, W + 1):
                nextCounter[j][i] = counter[i][j]
        counter = nextCounter
        H, W = W, H
    for i in range(1, H + 1):
        for j in range(1, W + 1):
            counter[i][j] = counter[i][j] + counter[i][j - 1] + counter[i - 1][j] - counter[i - 1][j - 1]
    ans = 0
    for i in range(H):
        for j in range(i + 1, H + 1):
            toClear = []
            for col in range(W + 1):
                temp = counter[j][col] - counter[i][col]
                idx = temp + BASE
                ans += memo[idx]
                memo[idx] += 1
                toClear.append(idx)
            for c in toClear:
                memo[c] = 0
    print(ans)

if __name__ == "__main__":
    T = int(input())
    for t in range(T):
        solve()
