// http://oj.daimayuan.top/course/10/problem/504

#include "unordered_map"
#include "vector"
#include "iostream"

int *next, *nums, *length;
std::unordered_map<int, std::vector<int>> container;

bool lessThan(int start1, int start2, int size) {
	for (int i = start1, j = start2, k = 0; k < size; i = next[i], j = next[j], k++) {
		if (nums[i] < nums[j]) {
			return true;
		}
		if (nums[i] > nums[j]) {
			return false;
		}
	}
	return false;
}

int main() {
	int n;
	scanf("%d", &n);
	nums = new int[n], next = new int[n], length = new int[n];
	int maxLength = 1, start = n - 1;
	for (int i = 0; i < n; i++) {
		scanf("%d", &nums[i]);
		container[nums[i]].push_back(i);
		length[i] = 1;
	}
	for (int i = n - 1; i >= 0; i--) {
		if (!container.count(nums[i] - 1)) {
			continue;
		}
		std::vector<int> &prevNodes = container[nums[i] - 1];
		while (!prevNodes.empty() && i < prevNodes.back()) {
			prevNodes.pop_back();
		}
		if (prevNodes.empty()) {
			container.erase(nums[i] - 1);
			continue;
		}
		int prevNode = prevNodes.back();
		if (length[prevNode] - 1 < length[i]) {
			length[prevNode] = length[i] + 1;
			next[prevNode] = i;
			if (length[prevNode] > maxLength) {
				start = prevNode;
				maxLength = length[prevNode];
			} else if (length[prevNode] == maxLength && lessThan(prevNode, start, maxLength)) {
				start = prevNode;
			}
		} else if (length[prevNode] - 1 == length[i] && lessThan(i, next[prevNode], length[i])) {
			next[prevNode] = i;
		}
	}
	printf("%d\n", maxLength);
	for (int i = start, j = 0; j < maxLength; i = next[i], j++) {
		printf("%d ", nums[i]);
	}
	return 0;
}
