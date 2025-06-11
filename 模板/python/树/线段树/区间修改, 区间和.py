class Info:
    __slots__ = ["val", "lazy"]

    def __init__(self):
        self.val = 0
        self.lazy = 0

class SegmentTree:
    __slots__ = ["length", "tree"]

    def __init__(self, length: int):
        self.length = length
        self.tree: list[Info] = [Info() for _ in range(length << 2)]

    def change(self, left: int, right: int, delta: int):
        self._change(1, 1, self.length, left, right, delta)

    def query(self, left: int, right: int) -> int:
        return self._query(1, 1, self.length, left, right)

    def _pushDown(self, node, start, end):
        info = self.tree[node]
        lazy = info.lazy
        if lazy == 0:
            return
        info.lazy = 0
        leftNode, rightNode = node << 1, node << 1 ^ 1
        mid = (start + end) >> 1
        leftInfo, rightInfo = self.tree[leftNode], self.tree[rightNode]
        leftInfo.val += lazy * (mid - start + 1)
        rightInfo.val += lazy * (end - mid)
        leftInfo.lazy += lazy
        rightInfo.lazy += lazy
        return

    def _change(self, node: int, start: int, end: int, left: int, right: int, delta: int):
        if left > end or right < start:
            return
        info = self.tree[node]
        if left <= start and right >= end:
            info.val += (end - start + 1) * delta
            info.lazy += delta
            return
        self._pushDown(node, start, end)
        leftNode, rightNode = node << 1, node << 1 ^ 1
        mid = (start + end) >> 1
        leftInfo, rightInfo = self.tree[leftNode], self.tree[rightNode]
        self._change(leftNode, start, mid, left, right, delta)
        self._change(rightNode, mid + 1, end, left, right, delta)
        info.val = leftInfo.val + rightInfo.val
        return

    def _query(self, node: int, start: int, end: int, left: int, right: int) -> int:
        if left > end or right < start:
            return 0
        info = self.tree[node]
        if left <= start and right >= end:
            return info.val
        self._pushDown(node, start, end)
        leftNode, rightNode = node << 1, node << 1 ^ 1
        mid = (start + end) >> 1
        return self._query(leftNode, start, mid, left, right) + self._query(rightNode, mid + 1, end, left, right)

