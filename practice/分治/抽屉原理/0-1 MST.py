class DSU:
    __slots__ = ["size", "prev", "nRest"]

    def __init__(self, length: int):
        self.size = [1] * length
        self.prev = [i for i in range(length)]
        self.nRest = length

    def find(self, idx: int) -> int:
        prev = self.prev
        while prev[idx] != idx:
            prev[idx] = prev[prev[idx]]
            idx = prev[idx]
        return idx

    def merge(self, idx1: int, idx2: int) -> bool:
        root1, root2 = self.find(idx1), self.find(idx2)
        if root1 == root2:
            return False
        size, prev = self.size, self.prev
        if size[root1] < size[root2]:
            root1, root2 = root2, root1
        size[root1] += size[root2]
        prev[root2] = root1
        self.nRest -= 1
        return True

def solve():
    n, m = map(int, input().split())
    adj = [set() for _ in range(n + 1)]
    for i in range(m):
        a, b = map(int, input().split())
        adj[a].add(b)
        adj[b].add(a)

    # 首先处理权重1临边最少的点, 由于度不超过[2m/n], 最后产生的0连通块数量不超过[2m/n]+1
    minRoot, minSize = 1, n
    for i in range(1, n + 1):
        if len(adj[i]) < minSize:
            minRoot = i
            minSize = len(adj[i])
    dsu = DSU(n + 1)
    for i in range(1, n + 1):
        if i not in adj[minRoot]:
            dsu.merge(minRoot, i)

    # 暴力处理剩下的0连通块
    rootList = []
    for i in range(1, n + 1):
        if dsu.find(i) == i:
            rootList.append(i)
    for root in rootList:
        memo = adj[root]
        for i in range(1, n + 1):
            if i not in memo:
                dsu.merge(root, i)
    rest = dsu.nRest - 1
    print(rest - 1)
    return

if __name__ == "__main__":
    solve()