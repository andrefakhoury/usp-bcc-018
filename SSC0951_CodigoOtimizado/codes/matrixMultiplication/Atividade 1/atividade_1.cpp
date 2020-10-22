#include <bits/stdc++.h>
using namespace std;

using Matrix = vector<vector<int>>;

// loop interchange trick
inline void mat_mult_interchange(Matrix const& A, Matrix const& B, Matrix& C, int const n) {
	for (int i = 0; i < n; i++)
		for (int k = 0; k < n; k++)
			for (int j = 0; j < n; j++)
				C[i][j] += A[i][k] * B[k][j];
}

// loop unrolling trick
inline void mat_mult_unrolling(Matrix const& A, Matrix const& B, Matrix& C, int const n) {
	for (int i = 0; i < n; i++)
		for (int k = 0; k < n; k++)
			for (int j = 0; j < n; j += 5) {
				C[i][j+0] += A[i][k] * B[k][j+0];
				C[i][j+1] += A[i][k] * B[k][j+1];
				C[i][j+2] += A[i][k] * B[k][j+2];
				C[i][j+3] += A[i][k] * B[k][j+3];
			}
}

int main(int argc, char* argv[]) {
	if (argc < 3) {
		printf("Use %s <method> <n>\n", argv[0]);
		printf("method is i or u");
		return 0;
	}

	int n;
	sscanf(argv[2], "%d", &n);

	Matrix a(n, vector<int>(n));
	Matrix b(n, vector<int>(n));
	Matrix c(n, vector<int>(n));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			a[i][j] = rand()%1000;
			b[i][j] = rand()%1000;
		}
	}

	if (argv[2][0] == 'i') {
		mat_mult_interchange(a, b, c, n);
	} else {
		mat_mult_unrolling(a, b, c, n);
	}
}