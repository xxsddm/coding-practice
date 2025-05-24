// https://www.acwing.com/problem/content/1886/

#include "iostream"

using namespace std;

int main() {
	int N, hash = (1 << ('C' - 'A')) ^ (1 << ('O' - 'A')) ^ (1 << ('W' - 'A'));
	int letter2idx[26];
	long long counter[4];
	string target = "ACOW";
	scanf("%d", &N);
	char container[N];
	scanf("%s", container);
	for (int i = 0; i < 4; i++) {
		letter2idx[target[i] - 'A'] = i;
		counter[i] = 0;
	}
	counter[0] = 1;
	for (int i = 0; i < N; i++) {
		char &temp = container[i];
		if ((hash & (1 << (temp - 'A'))) == 0) {
			continue;
		}
		int idx = letter2idx[container[i] - 'A'];
		counter[idx] += counter[idx - 1];
	}
	printf("%lld", counter[3]);
	return 0;
}
