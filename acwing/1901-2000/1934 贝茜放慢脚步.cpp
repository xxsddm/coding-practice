// https://www.acwing.com/problem/content/1936/

#include "vector"
#include "algorithm"
#include "iostream"

using namespace std;

int main() {	// 类似归并排序
	int N;
	scanf("%d", &N);
	double v = 1, s = 0, t = 0, eps = 1e-6;
	vector<double> slowD, slowT;
	for (int i = 0; i < N; i++) {
		char temp1[2];
		double temp2;
		scanf("%s %lf", &temp1, &temp2);
		if (temp1[0] == 'D') {
			slowD.push_back(temp2);
		} else {
			slowT.push_back(temp2);
		}
	}
	sort(slowD.begin(), slowD.end());
	sort(slowT.begin(), slowT.end());
	int idxD = 0, idxT = 0, count = 1;
	int lenD = (int) slowD.size(), lenT = (int) slowT.size();
	while (true) {
		if (idxD == lenD) {
			while (idxT < lenT) {
				s += v * (slowT[idxT] - t);
				t = slowT[idxT++];
				v = 1.0 / ++count;
			}
			break;
		}
		if (idxT == lenT) {
			while (idxD < lenD) {
				t += (slowD[idxD] - s) / v;
				s = slowD[idxD++];
				v = 1.0 / ++count;
			}
			break;
		}
		double timeD = t + (slowD[idxD] - s) / v, timeT = slowT[idxT];
		if (timeT + eps < timeD) {
			s += v * (slowT[idxT] - t);
			t = slowT[idxT++];
			v = 1.0 / ++count;
		} else if (timeD + eps < timeT) {
			t += (slowD[idxD] - s) / v;
			s = slowD[idxD++];
			v = 1.0 / ++count;
		} else {
			s = slowD[idxD++];
			t = slowT[idxT++];
			count += 2;
			v = 1.0 / count;
		}
	}
	t += (1000.0 - s) / v;
	printf("%.0lf", t);
	return 0;
}
