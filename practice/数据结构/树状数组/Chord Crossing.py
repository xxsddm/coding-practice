# https://atcoder.jp/contests/abc405/tasks/abc405_f

class BIT:
    def __init__(self, length):
        self.length = length
        self.tree = [0] * (length + 1)

    def change(self, loc, delta):
        while loc <= self.length:
            self.tree[loc] += delta
            loc += loc & -loc

    def query(self, loc):
        ans = 0
        while loc:
            ans += self.tree[loc]
            loc ^= loc & -loc
        return ans


N, M = map(int, input().split())
container1, container2 = [], []
for i in range(M):
    a, b = map(int, input().split())
    container1.append((a, b))
Q = int(input())
for i in range(Q):
    c, d = map(int, input().split())
    container2.append((c, d))
tree = BIT(N << 1)
result = [0] * Q
idxList1, idxList2 = [i for i in range(M)], [i for i in range(Q)]
idxList1.sort(key=lambda x: container1[x][0])
idxList2.sort(key=lambda x: container2[x][0])
idx1 = 0
for idx2 in idxList2:
    c, d = container2[idx2]
    while idx1 < M and container1[idxList1[idx1]][0] < c:
        a, b = container1[idxList1[idx1]]
        tree.change(b, 1)
        idx1 += 1
    result[idx2] += tree.query(d) - tree.query(c - 1)   # 左交叉
for i in range(N << 1 ^ 1):
    tree.tree[i] = 0
idxList1.sort(key=lambda x: - container1[x][1])
idxList2.sort(key=lambda x: - container2[x][1])
idx1 = 0
for idx2 in idxList2:
    c, d = container2[idx2]
    while idx1 < M and container1[idxList1[idx1]][1] > d:
        a, b = container1[idxList1[idx1]]
        tree.change(a, 1)
        idx1 += 1
    result[idx2] += tree.query(d) - tree.query(c - 1)   # 右交叉
for res in result:
    print(res)
