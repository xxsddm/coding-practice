// https://www.acwing.com/problem/content/1462/

#include "cstring"
#include "iostream"

using namespace std;

int mod = 99997, base = 131, N;
bool visited[99997];

int quickPower(int power) {
	int temp = base, ans = 1;
	while (power) {
		if (power & 1) {
			ans = (long long) ans * temp % mod;
		}
		temp = (long long) temp * temp % mod;
		power >>= 1;
	}
	return ans;
}

bool check(int length, char *word) {
	memset(visited, false, sizeof(visited));
	int minus = quickPower(length - 1), temp = 0;
	for (int i = 0; i < length; i++) {
		temp = ((temp * base) % mod + (word[i] - 'A')) % mod;
	}
	visited[temp] = true;
	for (int i = length; i < N; i++) {
		temp = (temp + mod - (word[i - length] - 'A') * minus % mod) % mod;
		temp = ((temp * base) % mod + (word[i] - 'A')) % mod;
		if (visited[temp]) {
			return false;
		}
		visited[temp] = true;
	}
	return true;
}

int main() {
	scanf("%d", &N);
	char word[N];
	scanf("%s", word);
	int left = 1, right = N;
	while (left <= right) {
		int mid = (left + right) >> 1;
		if (check(mid, word)) {
			right = mid - 1;
		} else {
			left = mid + 1;
		}
	}
	printf("%d", left);
	return 0;
}
