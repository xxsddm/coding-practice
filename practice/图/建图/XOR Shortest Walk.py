# https://atcoder.jp/contests/abc410/tasks/abc410_d

from collections import deque

LENGTH = 1 << 10
N, M = map(int, input().split())
nNode = (N + 1) << 10   # 增加状态维度, 表示经过该点时的状态访问情况
adj: list[list[int]] = [[] for _ in range(nNode)]
visited = [False] * nNode


def getNodeIdx(x, offset):
    return x << 10 | offset

for m in range(M):
    a, b, w = map(int, input().split())
    for i in range(LENGTH):
        idx1 = getNodeIdx(a, i)
        idx2 = getNodeIdx(b, i ^ w)
        adj[idx1].append(idx2)

q = deque()
start = getNodeIdx(1, 0)
q.append(start)
visited[start] = True
while q:
    node = q.popleft()
    for nextNode in adj[node]:
        if not visited[nextNode]:
            q.append(nextNode)
            visited[nextNode] = True
ans = -1
for i in range(LENGTH):
    if visited[getNodeIdx(N, i)]:
        ans = i
        break
print(ans)
