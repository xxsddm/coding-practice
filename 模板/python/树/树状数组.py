class BinaryIndexTree:  # tree[i]包含[i - lowbit(i) + 1, i]信息
    __slots__ = ["length", "tree"]

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