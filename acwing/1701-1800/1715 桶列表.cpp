// https://www.acwing.com/problem/content/1717/

#include "queue"
#include "algorithm"
#include "iostream"

using namespace std;

struct Cow {
	int start, end, num;

	bool operator > (Cow &other) {
		return end > other.end;
	}
};

int main() {
	int N, ans = 0;
	scanf("%d", &N);
	Cow container[N];
	priority_queue<Cow, vector<Cow>, greater<>> pq;
	for (int i = 0; i < N; i++) {
		scanf("%d %d %d", &container[i].start, &container[i].end, &container[i].num);
	}
	sort(container, container + N, [](auto & p1, auto & p2) -> bool {
		return p1.start < p2.start;
	});
	for (int i = 0, need = 0; i < N; i++) {
		int time = container[i].start;
		while (!pq.empty() && pq.top().end <= time) {
			need -= pq.top().num;
			pq.pop();
		}
		need += container[i].num;
		pq.push(container[i]);
		ans = max(ans, need);
	}
	printf("%d", ans);
	return 0;
}