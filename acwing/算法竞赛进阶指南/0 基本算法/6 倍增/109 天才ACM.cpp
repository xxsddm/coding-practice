// https://www.acwing.com/problem/content/111/

#include "algorithm"
#include "iostream"

using namespace std;

typedef long long ll;

int N, M;
ll T;

bool check(int start, int left, int right, int *nums, int *aux, int *container) {
	int l = start, r = left, mid = left - 1, k = 0;
	int idx = start, end = right;
	ll cumsum = 0;
	// aux[start~left-1]部分已填入nums元素, 排序且检验通过
	for (int i = left; i <= right; i++) {
		aux[i] = nums[i];
	}

	// 新加入的left~right部分排序后与start~left-1部分归并
	sort(aux + left, aux + right + 1);
	while (true) {
		if (l == mid + 1) {
			while (idx <= end) {
				container[idx++] = aux[r++];
			}
			break;
		}
		if (r == end + 1) {
			while (idx <= end) {
				container[idx++] = aux[l++];
			}
			break;
		}
		if (aux[l] <= aux[r]) {
			container[idx++] = aux[l++];
		} else {
			container[idx++] = aux[r++];
		}
	}

	// 计算校验值
	l = start, r = end;
	while (l < r && k++ < M && cumsum <= T) {
		ll temp = (container[l++] - container[r--]);
		cumsum += temp * temp;
	}

	if (cumsum <= T) {
		// 检验通过则填入aux, 后续可作为已排序部分
		for (int i = start; i <= right; i++) {
			aux[i] = container[i];
		}
	}
	return cumsum <= T;
}

int main() {	// 倍增+归并, 重复利用检验通过部分的排序
	int K;
	cin >> K;
	for (int k = 0; k < K; k++) {
		scanf("%d %d %lld", &N, &M, &T);
		int ans = 0, start = 0, nums[N], aux[N], container[N];
		for (int i = 0; i < N; i++) {
			scanf("%d", &nums[i]);
		}
		while (start < N) {
			ans++;
			// 倍增新加入区间[left, left+subLen-1]长度, 限制条件下最大化当前区域长度(start为当前区间首端)
			int subLen = 1, left = start;
			while (subLen) {
				if (left + subLen - 1 < N && check(start, left, left + subLen - 1, nums, aux, container)) {
					left += subLen;
					subLen <<= 1;
				} else {
					subLen >>= 1;
				}
			}
			start = left;
		}
		printf("%d\n", ans);
	}
	return 0;
}
