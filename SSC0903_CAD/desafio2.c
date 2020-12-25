/**
------------------------------------------------------
--- SSC0903 - Computação de Alto Desempenho (2020) ---
------------------------------------------------------

Atividade 08-1: Elementos menores que média (em matriz)

Desenvolvida por:
- Grupo 1
-- André Luís Mendes Fakhoury
-- Debora Buzon da Silva
-- Gustavo Vinicius Vieira Silva Soares
-- Thiago Preischadt Pinheiro
*/

#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <omp.h>

// aloca um vetor zerado de tamanho n
int* alloc_vector(int n) {
	int* mat = (int*) calloc(n, sizeof(int));
	return mat;
}

int main(int argc, char* argv[]) {
	// inicia o ambiente MPI
	int provided, nproc, rank;
	MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED, &provided);
	MPI_Comm_size(MPI_COMM_WORLD, &nproc);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int n; // tamanho da matriz
	int* a = NULL; // matriz entrada

	if (rank == 0) { // le a matriz de entrada
		FILE* input = fopen(argv[1], "r");
		if (input == NULL) {
			printf("Erro: arquivo inválido.\n");
			return -1;		
		}

		// le entrada
		fscanf(input, "%d", &n);
		a = alloc_vector(n * n);

		// le a matriz transposta
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				fscanf(input, "%d", &a[j * n + i]);
			}
		}
	}

	// transmissao do tamanho da matriz
	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

	// quantidade de elementos que cada processo recebe 
	int *qtt = alloc_vector(nproc);
	for (int i = 0; i < nproc; i++) {
		qtt[i] = n / nproc;
		if (n % nproc > i) {
			qtt[i]++;
		}
		qtt[i] *= n;
	}

	int *displacement = alloc_vector(nproc);
	displacement[0] = 0;
	for (int i = 1; i < nproc; i++) {
		displacement[i] = qtt[i - 1] + displacement[i - 1];
	}

	// matriz que o rank atual eh responsavel
	int *mat = alloc_vector(qtt[rank]);

	// espalha a matriz a
	MPI_Scatterv(a, qtt, displacement, MPI_INT, mat, qtt[rank], MPI_INT, 0, MPI_COMM_WORLD);

	// calculo da media
	int sum = 0;

	#pragma omp parallel for reduction(+: sum)
	for (int i = 0; i < qtt[rank]; i++) {
		sum += mat[i];
	}

	// transmissao da soma
	int* sums = NULL;
	if (rank == 0) {
		sums = alloc_vector(nproc);
	}

	MPI_Gather(&sum, 1, MPI_INT, sums, 1, MPI_INT, 0, MPI_COMM_WORLD);

	// calculo da media
	int media = 0;
	if (rank == 0) {
		#pragma omp parallel for reduction(+: media)
		for (int i = 0; i < nproc; i++) {
			media += sums[i];
		}

		// media = ceil(media / (n*n))
		media = (media + n * n - 1) / (n * n);
	}

	MPI_Bcast(&media, 1, MPI_INT, 0, MPI_COMM_WORLD);

	// calculo da resposta individual
	int* num_less = alloc_vector(qtt[rank] / n);

	#pragma omp parallel for collapse(2)
	for (int i = 0; i < qtt[rank] / n; i++) {
		for (int j = 0; j < n; j++) {
			if (mat[i * n + j] < media) {
				num_less[i]++;
			}
		}
	}

	// transmissao das respostas individuais
	int* num_less_global = NULL;
	if (rank == 0) {
		num_less_global = alloc_vector(n);
	}

	// a quantidade agora é o número de linhas
	for (int i = 0; i < nproc; i++) {
		qtt[i] /= n;
	}

	// recalcula o displacement
	for (int i = 1; i < nproc; i++) {
		displacement[i] = qtt[i - 1] + displacement[i - 1];
	}

	MPI_Gatherv(num_less, qtt[rank], MPI_INT, num_less_global, qtt, displacement, MPI_INT, 0, MPI_COMM_WORLD);

	// imprime a resposta
	if (rank == 0) {
		for (int i = 0; i < n; i++) {
			printf("%d ", num_less_global[i]);
		}
		printf("\n");
	}

	// limpa a memoria na heap
	if (rank == 0) {
		free(a);
		free(sums);
		free(num_less_global);
	}
	free(qtt);
	free(displacement);
	free(mat);
	free(num_less);

	// encerra MPI
	MPI_Finalize();

	return 0;
}
