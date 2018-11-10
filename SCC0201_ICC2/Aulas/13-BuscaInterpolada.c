#include <stdio.h>
#include <stdlib.h>

//O(lg(lgN)) se distribuicao uniforme
int interpolation(int* v, int l, int r, int key, int* c) {
	if (l > r) return 0;

	(*c)++;
	int m = l + ((key-v[l])*(r-l))/(v[r]-v[l]);
	if (v[m] == key) return 1;
	if (v[m] > key) return interpolation(v, l, m-1, key, c);
	if (v[m] < key) return interpolation(v, m+1, r, key, c);
}

int binary(int* v, int l, int r, int key, int* c) {
	if (l > r) return 0;

	(*c)++;

	int m = (l+r)/2;
	if (v[m] == key) return 1;
	if (v[m] > key) return binary(v, l, m-1, key, c);
	if (v[m] < key) return binary(v, m+1, r, key, c);
}

int main() {
	int n = 20;
	int *v = malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) scanf("%d", v+i);
	int compI, compB;

	for (int i = 0; i < n; i++) {
		compI = compB = 0;

		int d1 = interpolation(v, 0, n-1, v[i], &compI);
		int d2 = binary(v, 0, n-1, v[i], &compB);

		printf("v[%d] = %d :: bin=%d(%d) vs int=%d(%d)\n", i, v[i], compB, d2, compI, d1);
	}

	return 0;
}