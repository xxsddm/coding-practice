#include "algorithm"
#include "iostream"
#include "cmath"

template <typename T>
inline void read(T &x) {
	x = 0;
	char c = getchar();
	while (c < 48 || c > 57) {
		c = getchar();
	}
	while (c >= 48 && c <= 57) {
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = getchar();
	}
}

struct Node {
	int x, y;
} *container;

long long inf = 0x7fffffffffffffff, ans = inf;
int n, *idx, *left, *right, *leftx, *rightx, *lefty, *righty;

inline long long square(int num) {
	return (long long) num * num;
}

int build(int start, int end) {
	if (start > end) {
		return -1;
	}
	int mid = (start + end) >> 1;
	// 选择方差较大的维度划分节点
	double temp1 = 0, temp2 = 0, subLen = end - start + 1;
	long long sum1 = 0, sum2 = 0;
	for (int i = start; i <= end; i++) {
		temp1 += square(container[idx[i]].x);
		temp2 += square(container[idx[i]].y);
		sum1 += container[idx[i]].x;
		sum2 += container[idx[i]].y;
	}
	if (temp1 - sum1 / subLen * sum1 > temp2 - sum2 / subLen * sum2) {
		std::nth_element(idx + start, idx + mid, idx + end + 1, [&] (int &i, int &j) -> bool {
			return container[i].x < container[j].x;
		});
	} else {
		std::nth_element(idx + start, idx + mid, idx + end + 1, [&] (int &i, int &j) -> bool {
			return container[i].y < container[j].y;
		});
	}
	int node = idx[mid];
	left[node] = build(start, mid - 1);
	right[node] = build(mid + 1, end);
	// 维护各维度左右侧最值
	leftx[node] = container[node].x, rightx[node] = container[node].x;
	lefty[node] = container[node].y, righty[node] = container[node].y;
	if (left[node] != -1) {
		leftx[node] = std::min(leftx[node], leftx[left[node]]);
		lefty[node] = std::min(lefty[node], lefty[left[node]]);
		rightx[node] = std::max(rightx[node], rightx[left[node]]);
		righty[node] = std::max(righty[node], righty[left[node]]);
	}
	if (right[node] != -1) {
		leftx[node] = std::min(leftx[node], leftx[right[node]]);
		lefty[node] = std::min(lefty[node], lefty[right[node]]);
		rightx[node] = std::max(rightx[node], rightx[right[node]]);
		righty[node] = std::max(righty[node], righty[right[node]]);
	}
	return node;
}

long long mindist(int node, int &cur) {
	if (node == -1) {
		return inf;
	}
	long long temp = 0;
	int &x = container[cur].x, y = container[cur].y;
	if (leftx[node] > x) {
		temp += square(leftx[node] - x);
	} else if (rightx[node] < x) {
		temp += square(x - rightx[node]);
	}
	if (lefty[node] > y) {
		temp += square(lefty[node] - y);
	} else if (righty[node] < y) {
		temp += square(y - righty[node]);
	}
	return temp;
}

void query(int node, int &cur) {
	if (node != cur) {
		ans = std::min(ans, square(container[node].x - container[cur].x)
		               + square(container[node].y - container[cur].y));
	}
	long long temp1 = mindist(left[node], cur), temp2 = mindist(right[node], cur);
	if (temp1 < temp2) {
		if (temp1 < ans) {
			query(left[node], cur);
			if (temp2 < ans) {
				query(right[node], cur);
			}
		}
	} else if (temp2 < ans) {
		query(right[node], cur);
		if (temp1 < ans) {
			query(left[node], cur);
		}
	}
}

int main() {	// 洛谷P1429测试通过
	read(n);
	container = new Node[n];
	idx = new int[n];
	left = new int[n], right = new int[n];
	leftx = new int[n], rightx = new int[n];
	lefty = new int[n], righty = new int[n];
	for (int i = 0; i < n; i++) {
		read(container[i].x), read(container[i].y);
		idx[i] = i;
		left[i] = right[i] = -1;
	}
	int root = build(0, n - 1);
	for (int i = 0; i < n; i++) {
		query(root, i);
	}
	printf("%.4lf", sqrt(ans));
	return 0;
}