// https://www.acwing.com/problem/content/description/134/

#include "queue"
#include "cstring"
#include "unordered_map"
#include "iostream"

using namespace std;

int main() {
	int n, count = 1;
	char command[8];
	while (cin >> n && n) {
		bool used[n];
		memset(used, false, sizeof(used));
		unordered_map<int, int> id2q;
		queue<int> container[n], q;	// 各编号相应队列, 队伍编号的队列
		for (int i = 0; i < n; i++) {
			int length;
			scanf("%d", &length);
			for (int j = 0; j < length; j++) {
				int id;
				scanf("%d", &id);
				id2q[id] = i;
			}
		}
		printf("Scenario #%d\n", count++);
		while (true) {
			scanf("%s", command);
			if (command[0] == 'S') {
				printf("\n");
				break;
			}
			if (command[0] == 'E') {
				int id;
				scanf("%d", &id);
				int idxQ = id2q[id];
				container[idxQ].push(id);
				if (!used[idxQ]) {
					used[idxQ] = true;
					q.push(idxQ);
				}
			} else {
				int idxQ = q.front(), id = container[idxQ].front();
				container[idxQ].pop();
				if (container[idxQ].empty()) {
					used[idxQ] = false;
					q.pop();
				}
				printf("%d\n", id);
			}
		}
	}
	return 0;
}
