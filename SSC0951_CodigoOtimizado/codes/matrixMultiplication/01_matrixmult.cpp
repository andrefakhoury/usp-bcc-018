#include <bits/stdc++.h>
using namespace std;
const int MAX = 10;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// multiplicacao de matriz, simples
inline void mat_mult(vector<vector<int> >& A, vector<vector<int> >& B, vector<vector<int> >& C, int n1, int m1, int n2, int m2) {
	for (int i = 0; i < n1; i++)
		for (int j = 0; j < m2; j++)
			for (int k = 0; k < m1; k++)
				C[i][j] += A[i][k] * B[k][j];
}

// trocar a linha do k pelo j, pq ai o indice i fica fixo -> loop interchange
inline void mat_mult_interchange(vector<vector<int> >& A, vector<vector<int> >& B, vector<vector<int> >& C, int n1, int m1, int n2, int m2) {
	for (int i = 0; i < n1; i++)
		for (int k = 0; k < m1; k++)
			for (int j = 0; j < m2; j++)
				C[i][j] += A[i][k] * B[k][j];
}

// tirar o loop -> loop unrolling
inline void mat_mult_unrolling(vector<vector<int> >& A, vector<vector<int> >& B, vector<vector<int> >& C, int n1, int m1, int n2, int m2) {
	for (int i = 0; i < n1; i++)
		for (int k = 0; k < m1; k++)
			for (int j = 0; j < m2; j += 4) {
				C[i][j+0] += A[i][k] * B[k][j+0];
				C[i][j+1] += A[i][k] * B[k][j+1];
				C[i][j+2] += A[i][k] * B[k][j+2];
				C[i][j+3] += A[i][k] * B[k][j+3];
			}
}

int main(int argc, char* argv[]) {
	assert(argc >= 3);
	int n, m;
	sscanf(argv[1], "%d", &n);
	sscanf(argv[2], "%d", &m);

	int n1, m1, n2, m2;
	n1 = m2 = n;
	m1 = n2 = m;

	vector<vector<int> > A(n1, vector<int>(m1));
	vector<vector<int> > B(n2, vector<int>(m2));
	vector<vector<int> > C(n1, vector<int>(m2));

	for (int i = 0; i < n1; i++) for (int j = 0; j < m1; j++) A[i][j] = rng()%MAX;
	for (int i = 0; i < n2; i++) for (int j = 0; j < m2; j++) B[i][j] = rng()%MAX;

	// mat_mult_interchange(A, B, C, n1, m1, n2, m2);
	mat_mult_unrolling(A, B, C, n1, m1, n2, m2);	

	// certifica que o compilador nao tire tudo
	for (auto v : C) for (auto x : v) if (x%100000 == 0) printf("%d ", x);

	return 0;
}