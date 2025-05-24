// https://www.luogu.com.cn/problem/P5041

#include "queue"
#include "cstring"
#include "iostream"

using namespace std;

int *nums, *aux;
deque<int> container[26];
char word[1000002];

long long mergeSort(int start, int end) {
	if (start == end) {
		return 0;
	}
	int mid = (start + end) >> 1;
	long long ans = mergeSort(start, mid) + mergeSort(mid + 1, end);
	for (int i = start; i <= end; i++) {
		aux[i] = nums[i];
	}
	int idx = start, left = start, right = mid + 1;
	while (true) {
		if (left == mid + 1) {
			while (idx <= end) {
				nums[idx++] = aux[right++];
			}
			return ans;
		}
		if (right == end + 1) {
			while (idx <= end) {
				nums[idx++] = aux[left++];
			}
			return ans;
		}
		if (aux[left] <= aux[right]) {
			nums[idx++] = aux[left++];
		} else {
			nums[idx++] = aux[right++];
			ans += mid - left + 1;
		}
	}
}

int main() {	// 贪心分配位置, 归并排序
	scanf("%s", word);
	int length = strlen(word), counter[26];
	memset(counter, 0, sizeof(counter));
	for (int i = 0; i < length; i++) {
		counter[word[i] - 'A']++;
	}
	for (int i = 0, j = 0; i < 26; i++) {
		if (counter[i] & 1) {
			if (++j == 2) {
				printf("-1");
				return 0;
			}
			if (j && (length & 1) == 0) {
				printf("-1");
				return 0;
			}
		}
	}
	nums = new int[length], aux = new int[length];
	for (int i = 0; i < length; i++) {
		container[word[i] - 'A'].push_back(i);
	}
	memset(nums, -1, sizeof(int) * (length));
	priority_queue<int, vector<int>, greater<>> pq;
	for (int i = 0, mid = length >> 1; i < length; i++) {
		if (nums[i] != -1) {
			continue;
		}
		int idx = word[i] - 'A';
		// 分配该类字符每对前后位置
		// 要求左侧元素尽量靠左
		if (container[idx].size() == 1) {
			nums[i] = mid;
			container[idx].pop_front();
			if (i < mid) {
				pq.push(i);
			}
		} else {
			int idx1 = container[idx].front(), idx2 = container[idx].back();
			container[idx].pop_front(), container[idx].pop_back();
			if (!pq.empty() && i > pq.top()) {
				idx1 = pq.top();
				pq.pop();
				if (i < mid) {
					pq.push(i);
				}
			}
			nums[i] = idx1;
			nums[idx2] = length - 1 - idx1;
			if (idx2 < mid) {
				pq.push(idx2);
			}
		}
	}
	printf("%lld", mergeSort(0, length - 1));
	return 0;
}
