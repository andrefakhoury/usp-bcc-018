/**
------------------------------------------------------
--- SSC0903 - Computação de Alto Desempenho (2020) ---
------------------------------------------------------

Atividade 08-2: FindWords

Desenvolvida por:
- Grupo 1
-- André Luís Mendes Fakhoury
-- Debora Buzon da Silva
-- Gustavo Vinicius Vieira Silva Soares
-- Thiago Preischadt Pinheiro
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <mpi.h>
#include <omp.h>

int main(int argc, char* argv[]) {
	// inicia o ambiente MPI
	int provided, nproc, rank;
	MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED, &provided);
	MPI_Comm_size(MPI_COMM_WORLD, &nproc);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int row, col; // tamanho da matriz
	int n_words; // numero de palavras

	char* mat = NULL; // matriz de entrada
	char* queries = NULL; // palavras de cada query

	if (rank == 0) { // le a matriz de entrada
		FILE* input = fopen(argv[1], "r");
		if (input == NULL) {
			printf("Erro: arquivo inválido.\n");
			return -1;
		}

		// le entrada
		fscanf(input, "%d%d", &row, &col);
		mat = (char*) malloc(row * (col + 1) * sizeof(char));

		// le a matriz de entrada
		for (int i = 0; i < row; i++) {
			fscanf(input, " %s", &mat[i * (col + 1)]);
		}

		// le as queries
		fscanf(input, "%d", &n_words);
		queries = (char*) malloc(n_words * (col + 1) * sizeof(char));

		for (int i = 0; i < n_words; i++) {
			fscanf(input, " %s", &queries[i * (col + 1)]);
		}
	}

	// transmissao dos dados de entrada
	MPI_Bcast(&row, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&col, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&n_words, 1, MPI_INT, 0, MPI_COMM_WORLD);

	// aloca o vetor de queries
	if (rank != 0) {
		queries = (char*) malloc(n_words * (col + 1) * sizeof(char));
	}

	// transmissao das queries
	MPI_Bcast(queries, n_words * (col + 1), MPI_CHAR, 0, MPI_COMM_WORLD);

	// quantidade de caracteres que cada processo recebe 
	int *qtt = (int*) malloc(nproc * sizeof(int));
	for (int i = 0; i < nproc; i++) {
		qtt[i] = row / nproc;
		if (row % nproc > i) {
			qtt[i]++;
		}
		qtt[i] *= col + 1;
	}

	// calculo do displacement
	int *displacement = (int*) malloc(nproc * sizeof(int));
	displacement[0] = 0;
	for (int i = 1; i < nproc; i++) {
		displacement[i] = qtt[i - 1] + displacement[i - 1];
	}

	// matriz que o rank atual eh responsavel
	char* mat_local = (char*) malloc(qtt[rank] * sizeof(char));

	// espalha a matriz
	MPI_Scatterv(mat, qtt, displacement, MPI_CHAR, mat_local, qtt[rank], MPI_CHAR, 0, MPI_COMM_WORLD);

	// inicializa o vetor de respostas local
	int* ans_local = (int*) malloc(n_words * sizeof(int));
	for (int i = 0; i < n_words; i++) {
		ans_local[i] = -1;
	}

	// calculo da resposta local
	#pragma omp parallel for collapse(2)
	for (int q = 0; q < n_words; q++) {
		for (int i = 0; i < qtt[rank] / (col + 1); i++) {
			char* pos = strstr(&mat_local[i * (col + 1)], &queries[q * (col + 1)]);
			if (pos != NULL) {
				int j = pos - &mat_local[i * (col + 1)];
				ans_local[q] = displacement[rank] + i * (col + 1) + j;
			}
		}
	}

	// junta todas as respostas
	int* ans_global = NULL;
	if (rank == 0) {
		ans_global = (int*) malloc(n_words * nproc * sizeof(int));
	}

	MPI_Gather(ans_local, n_words, MPI_INT, ans_global, n_words, MPI_INT, 0, MPI_COMM_WORLD);

	if (rank == 0) {
		// calcula todas as respostas
		for (int j = 0; j < n_words; j++) {	
			int answer = -1;
			#pragma omp parallel for reduction(max:answer)
			for (int i = 0; i < nproc; i++) {
				if (ans_global[i * n_words + j] > answer) {	
					answer = ans_global[i * n_words + j];
				}
			}

			// imprime a resposta desta palavra
			printf("%s,", &queries[j * (col + 1)]);
			if (answer == -1) {
				printf("-1,-1\n");
			} else {
				printf("%d,%d\n", answer/(col+1), answer%(col+1));
			}
		}
	}

	// limpa a memoria na heap
	if (rank == 0) {
		free(mat);
		free(ans_global);
	}

	free(qtt);
	free(displacement);
	free(mat_local);
	free(queries);
	free(ans_local);

	// encerra MPI
	MPI_Finalize();

	return 0;
}
