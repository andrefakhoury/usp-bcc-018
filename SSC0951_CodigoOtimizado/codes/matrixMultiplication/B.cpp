#include <bits/stdc++.h>
using namespace std;
const int MAX = 100;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int main() {
	const int n = 2e3;
	int n1, m1, n2, m2;
	n1 = m1 = n2 = m2 = n;

	vector<vector<int> > A(n1, vector<int>(m1));
	vector<vector<int> > B(m2, vector<int>(n2));
	vector<vector<int> > C(n1, vector<int>(m2));

	for (int i = 0; i < n1; i++) for (int j = 0; j < m1; j++) A[i][j] = rng()%MAX;
	for (int i = 0; i < n2; i++) for (int j = 0; j < m2; j++) B[j][i] = rng()%MAX;

	for (int i = 0; i < n1; i++) {
		for (int j = 0; j < m2; j++) {
			for (int k = 0; k < m1; k++) {
				C[i][j] += A[i][k] * B[j][k];
			}
		}
	}	

	return 0;
}