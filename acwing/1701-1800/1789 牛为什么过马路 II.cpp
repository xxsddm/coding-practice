// https://www.acwing.com/problem/content/1791/

#include "queue"
#include "stack"
#include "iostream"

using namespace std;

int main() {
	char letters[52];
	scanf("%s", letters);
	deque<char> container;	// 保存访问一次的元素
	int ans = 0, visited = 0;
	for (char & letter : letters) {
		int temp = 1 << (letter - 'A');
		if (visited & temp) {
			stack<char> subcontainer;
			while (container.back() != letter) {
				subcontainer.push(container.back());
				container.pop_back();
				ans++;
			}
			container.pop_back();
			while (!subcontainer.empty()) {
				container.push_back(subcontainer.top());
				subcontainer.pop();
			}
		} else {
			container.push_back(letter);
		}
		visited ^= temp;
	}
	printf("%d", ans);
	return 0;
}
