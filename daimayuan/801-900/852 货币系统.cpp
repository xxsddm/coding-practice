// http://oj.daimayuan.top/course/10/problem/852

#include "queue"
#include "cstring"
#include "iostream"

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

int N, nums[1000], counter[20000];

bool check(int num) {
	int ans = 0;
	for (int i = N - 1, temp = num, count; i >= 0 && temp; i--) {
		if (temp >= nums[i]) {
			count = temp / nums[i];
			temp -= count * nums[i];
			ans += count;
		}
	}
	return ans == counter[num];
}

void bfs(int limit) {
	std::queue<int> q;
	q.push(0);
	int count = 0;
	while (!q.empty()) {
		count++;
		for (int i = 0, num, size = (int) q.size(); i < size; i++) {
			num = q.front();
			q.pop();
			for (int j = 0; j < N && num + nums[j] <= limit; j++) {
				if (!counter[num + nums[j]]) {
					counter[num + nums[j]] = count;
					q.push(num + nums[j]);
				}
			}
		}
	}
}

int main() {
	int T;
	read(T);
	while (T--) {
		read(N);
		memset(counter, 0, sizeof(counter));
		for (int i = 0; i < N; i++) {
			read(nums[i]);
		}
		bfs(nums[N - 1] * 2 - 1);
		bool judge = true;
		for (int i = nums[N - 1] * 2 - 1; i > 1; i--) {
			if (counter[i] != 1 && !check(i)) {
				judge = false;
				break;
			}
		}
		printf(judge ? "Yes\n" : "No\n");
	}
	return 0;
}
