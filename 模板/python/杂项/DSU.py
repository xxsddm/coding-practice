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