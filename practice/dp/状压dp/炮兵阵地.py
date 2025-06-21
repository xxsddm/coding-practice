# https://www.luogu.com.cn/problem/P2704

def main():
    N, M = map(int, input().split())

    row2Invalid = [0] * N
    for i in range(N):
        word = input().strip()
        status = 0
        for c in word:
            status <<= 1
            if c == 'H':
                status |= 1
        row2Invalid[i] = status

    nValid = 0
    validStatus = []    # 记录可行的行状态
    counter = []    # 记录状态的bitCount
    limit = 1 << M
    for i in range(limit):
        if i & (i >> 1) or i & (i >> 2):    # 某一行可行的状态, 检查同行2格内状态
            continue
        count = i.bit_count()
        validStatus.append(i)
        counter.append(count)
        nValid += 1

    # dp[i][j][k] -> 第i行状态j, 上一行(i-1行)状态k时的最大数量
    dp = [[[0] * nValid for _ in range(nValid)] for __ in range(N)]

    ans = 0
    for i in range(nValid):
        status1 = validStatus[i]
        count1 = counter[i]
        invalid1 = row2Invalid[0]
        if status1 & invalid1:
            continue
        ans = max(ans, count1)

    if N <= 1:
        print(ans)
        return

    for i in range(nValid):
        status1 = validStatus[i]
        count1 = counter[i]
        invalid1 = row2Invalid[1]
        if status1 & invalid1:
            continue
        for j in range(nValid):
            status2 = validStatus[j]
            count2 = counter[j]
            invalid2 = row2Invalid[0]
            if status2 & invalid2 or status1 & status2:
                continue
            dp[1][i][j] = max(dp[1][i][j], count1 + count2)

    for row in range(2, N):
        for i in range(nValid):
            status1 = validStatus[i]
            invalid1 = row2Invalid[row]
            if status1 & invalid1:
                continue
            count1 = counter[i]
            for j in range(nValid):
                status2 = validStatus[j]
                invalid2 = row2Invalid[row - 1]
                if status2 & invalid2 or status1 & status2:
                    continue
                for k in range(nValid):
                    status3 = validStatus[k]
                    invalid3 = row2Invalid[row - 2]
                    if status3 & invalid3 or status1 & status3 or status2 & status3:
                        continue
                    temp = count1 + dp[row - 1][j][k]   # 满足row-1, j, k到row, i, j转移条件
                    if temp > dp[row][i][j]:
                        dp[row][i][j] = temp

    for i in range(nValid):
        for j in range(nValid):
            ans = max(ans, dp[N - 1][i][j])

    print(ans)


if __name__ == "__main__":
    main()