// http://oj.daimayuan.top/course/10/problem/609

#include "cstring"
#include "iostream"

int *root, *size;

int find(int idx) {
	while (idx != root[idx]) {
		root[idx] = root[root[idx]];
		idx = root[idx];
	}
	return idx;
}

void merge(int node1, int node2) {
	int idx1 = find(node1), idx2 = find(node2);
	if (idx1 == idx2) {
		return;
	}
	if (size[idx1] >= size[idx2]) {
		size[idx1] += size[idx2];
		root[idx2] = idx1;
	} else {
		size[idx2] += size[idx1];
		root[idx1] = idx2;
	}
}

int main() {
	int N, Q;
	scanf("%d %d", &N, &Q);
	root = new int[N + 1], size = new int[N + 1];
	for (int i = 0; i <= N; i++) {
		root[i] = i;
		size[i] = 1;
	}
	for (int i = 0; i < Q; i++) {
		int L, R;
		scanf("%d %d", &L, &R);
		merge(L - 1, R);
	}
	printf(find(0) == find(N) ? "Yes" : "No");
	return 0;
}

/*
#include "queue"
#include "vector"
#include "cstring"
#include "iostream"

int main() {	// BFS
	int N, Q;
	scanf("%d %d", &N, &Q);
	bool visited[N + 1];
	memset(visited, false, sizeof(visited));
	std::vector<int> next[N + 1];
	for (int i = 0; i < Q; i++) {
		int L, R;
		scanf("%d %d", &L, &R);
		next[L - 1].push_back(R);
		next[R].push_back(L - 1);
	}
	if (next[0].empty() || next[N].empty()) {
		printf("No");
		return 0;
	}
	std::queue<int> q;
	q.push(0);
	visited[0] = true;
	while (!q.empty() && !visited[N]) {
		int node = q.front();
		q.pop();
		for (int &nextNode : next[node]) {
			if (!visited[nextNode]) {
				visited[nextNode] = true;
				q.push(nextNode);
			}
		}
	}
	printf(visited[N] ? "Yes" : "No");
	return 0;
}

 */