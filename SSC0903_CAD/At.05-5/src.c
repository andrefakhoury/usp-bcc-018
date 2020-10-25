/**
------------------------------------------------------
--- SSC0903 - Computação de Alto Desempenho (2020) ---
------------------------------------------------------

Atividade 05-5: Operações em retângulos

Desenvolvida por:
- Grupo 1
-- André Luís Mendes Fakhoury
-- Debora Buzon da Silva
-- Gustavo Vinicius Vieira Silva Soares
-- Thiago Preischadt Pinheiro
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

// numero de threads
#define T 16

// calcula a area
int calc_area(int base, int alt) {
	return base * alt;
}

// calcula o perimetro
int calc_perimetro(int base, int alt) {
	return 2 * base + 2 * alt;
}

// calcula a diagonal
double calc_diag(int base, int alt) {
	return sqrt(base * base + alt * alt);
}

int main(int argc, char* argv[]) {
	// ler dados de entrada
	int n;
	scanf("%d", &n);

	int* base = malloc(n * sizeof(int));
	int* alt = malloc(n * sizeof(int));

	for (int i = 0; i < n; i++) {
		scanf("%d", &base[i]);
	}
	for (int i = 0; i < n; i++) {
		scanf("%d", &alt[i]);
	}

	// vetores de resposta
	int* per = malloc(n * sizeof(int));
	int* area = malloc(n * sizeof(int));
	double* diag = malloc(n * sizeof(double));

	#pragma omp parallel for num_threads(T)
	for (int i = 0; i < n; i++) {
		per[i] = calc_perimetro(base[i], alt[i]);
		area[i] = calc_area(base[i], alt[i]);
		diag[i] = calc_diag(base[i], alt[i]);
	}

	// imprime a resposta
	for (int i = 0; i < n; i++) {
		printf("base[%d]=%d, alt[%d]=%d, per[%d]=%d, area[%d]=%d, diag[%d]=%.2lf\n", 
				i, base[i], i, alt[i], i, per[i], i, area[i], i, diag[i]);
	}

	// desaloca na heap
	free(base);
	free(alt);
	free(per);
	free(area);
	free(diag);

	return 0;
}
