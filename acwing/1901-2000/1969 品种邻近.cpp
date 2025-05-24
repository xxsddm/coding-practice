// https://www.acwing.com/problem/content/1971/

#include "unordered_map"
#include "iostream"

using namespace std;

int main() {
	unordered_map<int, int> prev;
	int maxId = -1, N, K;
	cin >> N >> K;
	for (int i = 0; i < N; i++) {
		int id;
		cin >> id;
		if (prev.count(id)) {
			int temp = i - prev[id];
			if (temp <= K) {
				maxId = max(maxId, id);
			}
		}
		prev[id] = i;
	}
	cout << maxId;
}
