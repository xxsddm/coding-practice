// https://www.acwing.com/problem/content/2016/

#include "algorithm"
#include "utility"
#include "iostream"

using namespace std;

int main() {
	int N, count = 1, idx = 0, ans = 1;
	cin >> N;
	int heights[N];
	pair<int, int> nums[N];
	for (int i = 0; i < N; i++) {
		scanf("%d", &nums[i].first);
		heights[i] = nums[i].first;
		nums[i].second = i;
	}
	sort(nums, nums + N, [&] (const auto & p1, const auto & p2) {
		if (p1.first != p2.first) {
			return p1.first < p2.first;
		}
		// 相同高度按照位置排序
		return p1.second < p2.second;
	});
	if (nums[0].first == nums[N - 1].first) {
		cout << ans;
		return 0;
	}
	while (idx < N) {
		// 查找连通块(等高且连续)
		int height = nums[idx].first;
		while (nums[idx].first == height) {	// 等高
			int left = nums[idx].second, right = left;
			while (idx + 1 < N && nums[idx + 1].first == height && nums[idx + 1].second == right + 1) {	// 连续
				idx++;
				right++;
			}
			idx++;
			// 该点低于左右水平则+1, 高于左右水平则-1
			// 边缘情况单独考虑
			if (left - 1 == - 1) {
				if (heights[right + 1] < height) {
					count--;
				}
			} else if (right + 1 == N) {
				if (heights[left - 1] < height) {
					count--;
				}
			} else {
				if (heights[left - 1] > height && heights[right + 1] > height) {
					count++;
				} else if (heights[left - 1] < height && heights[right + 1] < height) {
					count--;
				}
			}
		}
		ans = max(ans, count);
	}
	printf("%d", ans);
	return 0;
}
