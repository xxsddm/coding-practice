# https://codeforces.com/problemset/problem/2114/G

def solve():
    n, k = map(int, input().split())
    nums = list(map(int, input().split()))
    factor = [0] * n
    power = [0] * n
    leftCounter = [0] * n
    rightCounter = [0] * n
    # 除以2产生元素是为二叉树, 可构成 满二叉树
    # 注意不可产生左端(右侧放入)/右端(左侧放入)作为分裂后的元素
    for i in range(n):
        num = nums[i]
        count = 0
        while num & 1 ^ 1:
            num >>= 1
            count += 1
        factor[i] = num     # 叶节点元素
        power[i] = count    # 满二叉树高度
    for i in range(n):  # 左侧放入
        f1 = factor[i]
        f2 = factor[i + 1] if i + 1 < n else -1
        p1 = power[i]
        p2 = power[i + 1] if i + 1 < n else -1
        if f1 != f2 or p1 <= p2:
            leftCounter[i] = 1 << p1
        else:
            leftCounter[i] = (1 << p1) - (1 << p2 + 1) + 1  # 邻点元素属于二叉树
    for i in range(n - 1, -1, -1):  # 右侧放入
        f1 = factor[i]
        f2 = factor[i - 1] if i else -1
        p1 = power[i]
        p2 = power[i - 1] if i else -1
        if f1 != f2 or p1 <= p2:
            rightCounter[i] = 1 << p1
        else:
            rightCounter[i] = (1 << p1) - (1 << p2 + 1) + 1 # 邻点元素属于二叉树
    for i in range(1, n):
        leftCounter[i] += leftCounter[i - 1]
    for i in range(n - 2, -1, -1):
        rightCounter[i] += rightCounter[i + 1]
    if leftCounter[n - 1] >= k or rightCounter[0] >= k:
        print("YES")
        return
    for i in range(n - 1):  # 组合时, 边界元素无需受另一端元素制约
        originLeft = leftCounter[i] - (leftCounter[i - 1] if i else 0)
        originRight = rightCounter[i + 1] - (rightCounter[i + 2] if i + 2 < n else 0)
        valLeft = 1 << power[i]
        valRight = 1 << power[i + 1]
        temp = leftCounter[i] + rightCounter[i + 1] - originLeft - originRight + valLeft + valRight
        if temp >= k:
            print("YES")
            return
    print("NO")
    return

if __name__ == "__main__":
    T = int(input())
    for t in range(T):
        solve()