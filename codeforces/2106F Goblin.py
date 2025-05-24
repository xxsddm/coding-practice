# https://codeforces.com/problemset/problem/2106/F

def solve():
    length = int(input())
    word = list(input())
    word = [int(word[i]) for i in range(length)]
    counter = []    # 记录从上至下的各段面积, 从左往右遍历过程中, 两段的连接位置是确定的, 无需记录
    ans = 0
    for i in range(length):
        num = word[i]
        if num == 0:
            nextCounter = [i, length - 1 - i]
            for j in range(len(counter)):
                nextCounter[j] += counter[j]
        else:
            nextCounter = [1] if len(counter) != 2 else [1 + counter[1]]
        counter = nextCounter
        ans = max(ans, max(counter))
    print(ans)


if __name__ == "__main__":
    T = int(input())
    for t in range(T):
        solve()
