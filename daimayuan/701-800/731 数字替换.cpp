// http://oj.daimayuan.top/course/10/problem/731

#include "cstring"
#include "iostream"

int length = 0, num2root[500001], size[500001], root[500001], *nums;

int find(int idx) {
	while (idx != root[idx]) {
		root[idx] = root[root[idx]];
		idx = root[idx];
	}
	return idx;
}

void merge(int idx1, int idx2) {
	int num = nums[idx1];
	if (size[idx1] > size[idx2]) {
		num2root[num] = idx1;
		size[idx1] += size[idx2];
		root[idx2] = idx1;
	} else {
		num2root[num] = idx2;
		size[idx2] += size[idx1];
		root[idx1] = idx2;
	}
}

int main() {
	int q;
	scanf("%d", &q);
	memset(num2root, -1, sizeof(num2root));
	nums = new int[q];
	for (int i = 0, op, x, y; i < q; i++) {
		scanf("%d", &op);
		if (op == 1) {
			scanf("%d", &x);
			nums[length] = x;
			size[length] = 1;
			root[length] = length;
			if (num2root[x] != -1) {
				merge(length, num2root[x]);
			} else {
				num2root[x] = length;
			}
			length++;
		} else {
			scanf("%d %d", &x, &y);
			if (x != y && num2root[x] != -1) {
				nums[num2root[x]] = y;
				if (num2root[y] != -1) {
					merge(num2root[x], num2root[y]);
				} else {
					num2root[y] = num2root[x];
				}
				num2root[x] = -1;
			}
		}
	}
	for (int i = 0; i < length; i++) {
		printf("%d ", nums[find(i)]);
	}
	return 0;
}