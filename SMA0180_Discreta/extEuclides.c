#include <stdio.h>

//GCD(n, d) = i*n + j*d
int GCD(int n, int d, int* i, int* j) { 
	if (n < d) {
		int a = n;
		n = d;
		d = a;
	}

	if(n%d == 0) {
		*i = 0;
		*j = 1;
		return d;
	} else {
		int tM = GCD(d, n%d, i, j);
		int tI = *i;
		*i = *j;
		*j = tI - (*j)*(n/d);

		return tM;
	}
}

int main() {
	int n, d, i, j;
	scanf("%d%d", &n, &d);
	int g = GCD(n, d, &i, &j);
	printf("%d = %d*%d + %d*%d\n", g, i, n, j, d);
	return 0;
}