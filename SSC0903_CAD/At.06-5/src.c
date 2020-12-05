/**
------------------------------------------------------
--- SSC0903 - Computação de Alto Desempenho (2020) ---
------------------------------------------------------

Atividade 06-5: Multiplicação de Matrizes

Desenvolvida por:
- Grupo 1
-- André Luís Mendes Fakhoury
-- Debora Buzon da Silva
-- Gustavo Vinicius Vieira Silva Soares
-- Thiago Preischadt Pinheiro

===========================================================
Projeto do algoritmo paralelo utilizando a metodologia PCAM:
===========================================================

=================== - Particionamento - ===================
A multiplicação das matrizes A e B, ambas de ordem N, é di-
vidida em NxN tarefas, cada uma é responsável pela combina-
ção de uma linha da matriz A com uma coluna da matriz B, e
realiza o produto entre a linha e a coluna. Para finalizar,
ocorre uma sincronização, e apenas a tarefa principal impri-
me a matriz resultante C.

=================== -   Comunicação   - ===================
Inicialmente cada tarefa é inicializada com a linha e coluna
pela qual é responsável. Após realizar a multiplicação, cada
tarefa envia o valor resultado para a tarefa principal. Por
fim, ocorre uma sincronização global e a tarefa principal im-
prime a matriz resultante C.

=================== -   Aglomeração   - ===================
O número de processos P e o número de threads por processo
T é definido com base na quantidade de processadores dispo-
níveis. Para isso, podemos escolher o valor de P como o nú-
mero de processadores disponíveis e T como o número de threads
que cada processador pode executar simultaneamente.

A multiplicação será dividida em K = PxT blocos, e cada
thread será responsável por um bloco. Cada bloco irá conter
floor(NxN/K) tarefas. As R tarefas restantes podem ser divi-
didas, atribuindo uma tarefa adicional para os R primeiros
blocos. Ou seja, cada thread será responsável por floor(NxN/K)
tarefas, podendo receber uma tarefa adicional caso haja resto.
Já cada processo será responsável por floor(NxN/K)xT tarefas,
podendo receber até T tarefas adicionais caso haja resto.

=================== -   Mapeamento    - ===================
Caso o desempenho dos nós seja homogêneo, o mapeamento de
cada um dos P processos em PROC elementos de processamento
pode ocorrer por meio de uma fila circular, tendo em vista
que cada processo possui a mesma carga de trabalho. Caso o
desempenho dos nós seja diferente, o mapeamento pode deixar
de ser estático e ser dinâmico, atribuindo cada processo ao
nó com menor carga de trabalho (definida por alguma métrica
de desempenho).
*/

#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <omp.h>

// numero fixo de threads
#define NUMTHREADS 8

// numero fixo de linhas/colunas das matrizes quadradas
#define N 16

// aloca um vetor de tamanho n
int* alloc_vector(int n) {
	int* mat = malloc(n * sizeof(int));
	return mat;
}

// gera um vetor de n valores pseudo-aleatorios
void generate_random(int* m, int n) {
	for (int i = 0; i < n; i++) {
		m[i] = rand() % 10;
	}
}

int main(int argc, char* argv[]) {

	// matrizes a, b, c
	int *a, *b, *c;

	// inicia o ambiente MPI
	int provided, nproc, rank;
	MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED, &provided);
	MPI_Comm_size(MPI_COMM_WORLD, &nproc);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	// inicializa as matrizes a, b, c
	if (rank == 0) {
		// gera as matrizes
		a = alloc_vector(N * N);
		generate_random(a, N * N);
		b = alloc_vector(N * N);
		generate_random(b, N * N);
		c = alloc_vector(N * N);
	} else {
		a = NULL;
		b = alloc_vector(N * N);
		c = NULL;
	}

	// quantidade de elementos que cada processo recebe 
	int *qtt = alloc_vector(nproc);
	for (int i = 0; i < nproc; i++) {
		qtt[i] = N / nproc;
		if (N % nproc > i) {
			qtt[i]++;
		}
		qtt[i] *= N; // todas as colunas de cada linha
	}
	int *displacement = alloc_vector(nproc);
	displacement[0] = 0;
	for (int i = 1; i < nproc; i++) {
		displacement[i] = qtt[i - 1] + displacement[i - 1];
	}

	// matriz que o rank atual eh responsavel
	int *mat = alloc_vector(qtt[rank]);
	int *prod = alloc_vector(qtt[rank]);

	// espalha a matriz A
	MPI_Scatterv(a, qtt, displacement, MPI_INT, mat, qtt[rank], MPI_INT, 0, MPI_COMM_WORLD);

	// manda a matriz B
	MPI_Bcast(b, N * N, MPI_INT, 0, MPI_COMM_WORLD);

	// realiza mat * b, salvando o resultado em prod
	#pragma omp parallel for num_threads(NUMTHREADS) collapse(2)
	for (int i = 0; i < qtt[rank] / N; i++) {
		for (int j = 0; j < N; j++) {
			prod[i * N + j] = 0;
			for (int k = 0; k < N; k++) {
				prod[i * N + j] += mat[i * N + k] * b[k * N + j];
			}
		}
	}

	// manda de volta e salva todo o resultado na matriz c
	MPI_Gatherv(prod, qtt[rank], MPI_INT, c, qtt, displacement, MPI_INT, 0, MPI_COMM_WORLD);

	// imprime a matriz de resultado
	if (rank == 0) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				printf("%d ", c[i * N + j]);
			}
			printf("\n");
		}
	}

	// limpa a memoria na heap
	if (rank == 0) {
		free(a);
		free(c);
	}
	free(b);
	free(qtt);
	free(displacement);
	free(mat);
	free(prod);

	// encerra MPI
	MPI_Finalize();

	return 0;
}
