// https://www.acwing.com/problem/content/95/

#include "queue"
#include "iostream"

using namespace std;

int n, m;
deque<int> nums;

void dfs(int start) {
	int size = (int) nums.size();
	if (size == m) {
		for (int &num : nums) {
			cout << num << " ";
		}
		cout << endl;
		return;
	}
	for (int num = start; num <= n + 1 - m + size; num++) {
		nums.push_back(num);
		dfs(num + 1);
		nums.pop_back();
	}
}

int main() {
	cin >> n >> m;
	dfs(1);
	return 0;
}
