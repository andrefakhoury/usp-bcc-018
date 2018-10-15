#include <stdio.h>
#include <stdlib.h>

typedef struct reg {
	int key;
	float val;
} Reg;

int radixSort(Reg* v, int n) {
	//8 em 8 bits
	//chaves de 8 bits a cada passada
	//minimo = 0; maximo = 255

	int i, j, shift;
	int C[256] = {0};
	int pos[256];
	Reg* copy = (Reg*) malloc(n * sizeof(Reg));

	for (shift = 0; shift <= 24; shift += 8) {

		///1. Counting sort
		for (j = 0; j < n; j++) {
			i = (v[j].key >> shift) & 255;
			C[i]++;
			copy[j] = v[j];
		}

		pos[0] = 0; //contagem acumulada
		for (int i = 1; i < 256; i++) {
			pos[i] = pos[i-1] + C[i-1];
			C[i-1] = 0;
		}

		//atribui
		for (j = 0; j < n; j++) {
			i = (copy[j].key >> shift) & 255;
			v[pos[i]] = copy[j];
			pos[i]++;
		}
	}

	free(copy);
}

int main() {
	Reg A[] = { {255, 8.3}, {256, 1.3}, {0, 9.2}, {257, 8.3},
				{1, 10.0}, {2, 8.111}, {259, 2.1} };

	int N = 7;

	for (int i = 0; i < N; i++)
		printf("[%03d %.2f] ", A[i].key, A[i].val);

	radixSort(A, N);

	printf("\n");
	for (int i = 0; i < N; i++)
		printf("[%03d %.2f] ", A[i].key, A[i].val);
	printf("\n");

	return 0;
}


/*

---8 em 8 bits
FOR(shift)
	FOR(j) N
	FOR(i) 255
	FOR(j) N

4*(2N + 255)

---16 em 16
2*(2N + 65535)

---4 em 4
8*(2N + 15)


//em que b eh qts bits
.: O(n + 32/b(2**b-1))  */