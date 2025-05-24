// https://www.acwing.com/problem/content/1877/

#include "vector"
#include "iostream"

using namespace std;

int main() {	// (B+I)(G+O+E+S)(M)
	int N;
	cin >> N;
	// 计算各部分奇数数量
	int counterOdd[3] = {0, 0, 0}, total = 1;
	string target = "BESIGOM";
	vector<int> nums[26];
	for (int i = 0; i < N; i++) {
		char letter;
		int num;
		scanf("%s %d", &letter, &num);
		nums[letter - 'A'].push_back(num);
	}
	for (char &letter : target) {
		total *= (int) nums[letter - 'A'].size();
	}
	for (int &B : nums['B' - 'A']) {
		for (int &I : nums['I' - 'A']) {
			if (abs(B + I) & 1) {
				counterOdd[0]++;
			}
		}
	}
	for (int &G : nums['G' - 'A']) {
		for (int &E : nums['E' - 'A']) {
			for (int &O : nums['O' - 'A']) {
				for (int &S : nums['S' - 'A']) {
					if (abs(G + E + O + S) & 1) {
						counterOdd[1]++;
					}
				}
			}
		}
	}
	for (int &M : nums['M' - 'A']) {
		if (abs(M) & 1) {
			counterOdd[2]++;
		}
	}
	cout << (total - counterOdd[0] * counterOdd[1] * counterOdd[2]);
	return 0;
}
