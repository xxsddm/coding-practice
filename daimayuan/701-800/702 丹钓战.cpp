// http://oj.daimayuan.top/course/10/problem/702

#include "stack"
#include "algorithm"
#include "iostream"

int n, *prev, *nums1, *nums2, *ans, *container;
struct Comb {
	int left, right, idx;
} *question;

void change(int idx) {
	if (idx == 0) {
		container[0]++;
		return;
	}
	while (idx <= n) {
		container[idx]++;
		idx += idx & -idx;
	}
}

int query(int idx) {
	int temp = container[0];
	while (idx) {
		temp += container[idx];
		idx ^= idx & -idx;
	}
	return temp;
}

int main() {
	int q;
	scanf("%d %d", &n, &q);
	prev = new int[n + 1];
	nums1 = new int[n + 1];
	nums2 = new int[n + 1];
	container = new int[n + 1];
	ans = new int[q];
	question = new Comb[q];
	container[0] = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &nums1[i]);
		container[i] = 0;
	}
	for (int i = 1; i <= n; i++) {
		scanf("%d", &nums2[i]);
	}
	std::stack<int> stk;
	for (int i = 1; i <= n; i++) {
		int &a = nums1[i], &b = nums2[i];
		while (!stk.empty() && (a == nums1[stk.top()] || b >= nums2[stk.top()])) {
			stk.pop();
		}
		// 保存每个元素无法抵消的位置
		prev[i] = stk.empty() ? 0 : stk.top();
		stk.push(i);
	}
	for (int i = 0; i < q; i++) {
		scanf("%d %d", &question[i].left, &question[i].right);
		question[i].idx = i;
	}
	std::sort(question, question + q, [] (auto & p1, auto & p2) -> bool {
		return p1.right < p2.right;
	});
	// i <= right && prev[i] < left
	for (int i = 0, j = 1; i < q; i++) {
		int &right = question[i].right;
		while (j <= right) {
			change(prev[j++]);
		}
		// 还需考虑i<left情况
		ans[question[i].idx] = query(question[i].left - 1) - question[i].left + 1;
	}
	for (int i = 0; i < q; i++) {
		printf("%d\n", ans[i]);
	}
	return 0;
}
