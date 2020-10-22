/**
------------------------------------------------------
--- SSC0903 - Computação de Alto Desempenho (2020) ---
------------------------------------------------------

Atividade 05 - 3: Calculo de varias metricas em matriz de double utilizando tasks

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

#define QT_METRICAS 7
#define T 16

// retorna a media do vetor vet, com n elementos
double media(double* vet, int n) {
	double soma = 0;
	for (int i = 0; i < n; i++) {
		soma += vet[i];
	}
	return soma / n;
}

// retorna a media harmonica do vetor vet, com n elementos
double harmonica(double* vet, int n) {
	double soma = 0;
	for (int i = 0; i < n; i++) {
		soma += 1.0 / vet[i];
	}
	return n / soma;
}

// retorna a mediana do vetor vet (deve estar ordenado)
double mediana(double* vet, int n) {
	if (n % 2 == 0) {
		return (vet[n/2] + vet[n/2-1]) / 2.0;
	} else {
		return vet[n/2];
	}
}

// retorna a media do vetor (deve estar ordenado)
double moda(double* vet, int n) {
	int f = 1;
	int res = 1;
	double val = -1;
	for (int i = 1; i < n; i++) {
		if (vet[i] == vet[i-1]) {
			f++;
		} else {
			f = 1;
		}

		if (f > res) {
			val = vet[i-1];
			res = f;
		}
	}

	return val;
}

// retorna a variancia do vetor, passando a media como parametro
double variancia(double* vet, double med, int n) {
	double soma = 0;
	for (int i = 0; i < n; i++) {
		soma += (vet[i] - med) * (vet[i] - med);
	}
	return soma / (n - 1);
}

// retorna o desvio padrao, dada a variancia
double desvio_padrao(double var) {
	return sqrt(var);
}

// retorna o coeficiente de variacao, dado o desvio padrao e a media
double coef_variacao(double dp, double med) {
	return dp / med;
}

// funcao de comparacao para ordenacao de double
int comp(const void* x, const void* y) {
	double dif = (*(double*)x) - (*(double*)y);
	return dif < 0 ? -1 : dif == 0 ? 0 : 1;
}

// ordena o vetor vet
void ordena(double* vet, int n) {
	qsort(vet, n, sizeof(double), comp);
}

int main(int argc, char* argv[]) {
	// ler matriz de entrada
	int n, m;
	scanf("%d%d", &n, &m);

	// lendo como matriz transposta para facilitar os calculos
	double** mat = malloc(m * sizeof(double*));
	for (int i = 0; i < m; i++) {
		mat[i] = malloc(n * sizeof(double));
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%lf", &mat[j][i]);
		}
	}

	// criacao do vetor resposta
	double** res = malloc(QT_METRICAS * sizeof(double*));
	for (int i = 0; i < QT_METRICAS; i++)
		res[i] = malloc(m * sizeof(double));

	// calculo das metricas
	#pragma omp parallel num_threads(T)
	{

		#pragma omp single
		{
			// ordena as linhas
			for (int i = 0; i < m; i++) {
				#pragma omp task
				ordena(mat[i], n);
			}
		}

		// calcula as metricas independentes
		#pragma omp barrier
		#pragma omp single
		{

			for (int i = 0; i < m; i++) {
				#pragma omp task
				res[0][i] = media(mat[i], n);

				#pragma omp task
				res[1][i] = harmonica(mat[i], n);

				#pragma omp task
				res[2][i] = mediana(mat[i], n);

				#pragma omp task
				res[3][i] = moda(mat[i], n);
			}
		}

		// calcula as metricas que dependem das outras
		#pragma omp barrier
		#pragma omp single
		for (int i = 0; i < m; i++) {
			#pragma omp task
			{
				res[4][i] = variancia(mat[i], res[0][i], n);
				res[5][i] = desvio_padrao(res[4][i]);
				res[6][i] = coef_variacao(res[5][i], res[0][i]);
			}
		}
	}

	// imprime a resposta
	for (int i = 0; i < QT_METRICAS; i++) {
		for (int j = 0; j < m; j++) {
			printf("%.1lf ", res[i][j]);
		}
		printf("\n");
		free(res[i]);
	}

	// limpa as matrizes
	for (int i = 0; i < m; i++)
		free(mat[i]);
	free(mat);
	free(res);

	return 0;
}
