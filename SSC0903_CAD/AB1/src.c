/**
------------------------------------------------------
--- SSC0903 - Computação de Alto Desempenho (2020) ---
------------------------------------------------------

AB1 - Soma de produtos em matrizes

Desenvolvida por:
- Grupo 1
-- André Luís Mendes Fakhoury
-- Debora Buzon da Silva
-- Gustavo Vinicius Vieira Silva Soares
-- Thiago Preischadt Pinheiro
*/

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

// numero de threads
#define T 16

// aloca uma matriz zerada NxN na heap
double** alloc_matrix(int n) {
	double** mat = malloc(n * sizeof(double*));
	for (int i = 0; i < n; i++) {
		mat[i] = calloc(n, sizeof(double));
	}
	return mat;
}

// aloca e le (pelo stdin, scanf) uma matrix NxN de doubles
double** alloc_read_matrix(int n) {
	double** mat = malloc(n * sizeof(double*));
	for (int i = 0; i < n; i++) {
		mat[i] = malloc(n * sizeof(double));
		for (int j = 0; j < n; j++) {
			scanf("%lf", &mat[i][j]);
		}
	}
	return mat;	
}

// desaloca uma matriz na heap
void free_matrix(double** mat, int n) {
	for (int i = 0; i < n; i++) {
		free(mat[i]);
	}
	free(mat);
}

// multiplica matrizes quadradas NxN: prod = A*B
void multiply(double** A, double** B, double** prod, int n) {
	#pragma omp for collapse(2) nowait
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				prod[i][j] += A[i][k] * B[k][j];
			}
		}
	}
}

// soma matrizes quadradas NxN: A += B. Soma in-place evita uma alocacao de matriz a mais.
void sum(double** A, double** B, int n) {
	#pragma omp for collapse(2)
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			A[i][j] += B[i][j];
		}
	}
}


int main(int argc, char* argv[]) {
	// ler dados de entrada
	int n;
	scanf("%d", &n);

	double** A = alloc_read_matrix(n);
	double** B = alloc_read_matrix(n);
	double** C = alloc_read_matrix(n);
	double** D = alloc_read_matrix(n);

	// matrizes auxiliares para os produtos
	double** prod1 = alloc_matrix(n);
	double** prod2 = alloc_matrix(n);

	// paraleliza em T threads
	#pragma omp parallel num_threads(T)
	{
		multiply(A, B, prod1, n); // prod1 = A*B
		multiply(C, D, prod2, n); // prod2 = C*D

		// barreira explícita para sincronização
		#pragma omp barrier

		sum(prod1, prod2, n);     // prod1 += prod2
	}

	// imprime a resposta
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (j != 0) printf(" ");
			printf("%.1lf", prod1[i][j]);
		}
		printf("\n");
	}

	// desaloca as matrizes na heap
	free_matrix(A, n);
	free_matrix(B, n);
	free_matrix(C, n);
	free_matrix(D, n);
	free_matrix(prod1, n);
	free_matrix(prod2, n);

	return 0;
}
