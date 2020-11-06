/**
------------------------------------------------------
--- SSC0903 - Computação de Alto Desempenho (2020) ---
------------------------------------------------------

Atividade 06-1: Números maiores que Limiar

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

// retorna a qtd de vet[i] maiores que limiar, e armazena em res caso vet[i] > limiar
int conta_maiores(int* vet, int n, int limiar, int** res) {
	int cont = 0;
	for (int i = 0; i < n; i++) {
		if (vet[i] > limiar) {
			cont++;
			*res = realloc(*res, cont * sizeof(int));
			(*res)[cont-1] = i;
		}
	}
	return cont;
}

int main(int argc, char* argv[]) {
	// inicializa MPI
	int n_proc, rank;

	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &n_proc);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	if (rank == 0) { // processo principal

		// le dados da entrada
		int n, k;
		scanf("%d%d", &n, &k);
		
		int* vet = malloc(n * sizeof(int));
		for (int i = 0; i < n; i++) {
			scanf("%d", &vet[i]);
		}

		// divide em blocos
		int tam_bloco = n / n_proc;
		int somatorio = tam_bloco;
		if (n % n_proc > 0) {
			somatorio++;
		}

		int tam_bloco_0 = somatorio;

		for (int i = 1; i < n_proc; i++) {
			int bloco_at = tam_bloco;
			if (i < n % n_proc) {
				bloco_at++;
			}

			MPI_Send((void*) &bloco_at, 1, MPI_INT, i, 1, MPI_COMM_WORLD); // envia o tamanho do bloco
			MPI_Send((void*) &vet[k], 1, MPI_INT, i, 2, MPI_COMM_WORLD); // envia o limiar
			MPI_Send((void*) (vet + somatorio), bloco_at, MPI_INT, i, 3, MPI_COMM_WORLD); // envia o bloco

			somatorio += bloco_at;
		}

		// processa os valores do processo principal
		int* maiores = NULL;
		int cont = conta_maiores(vet, tam_bloco_0, vet[k], &maiores);

		somatorio = tam_bloco_0;
		
		// recebe os valores dos outros processos, ajeitando os indices
		for (int i = 1; i < n_proc; i++) {
			int cont_i;
			MPI_Recv(&cont_i, 1, MPI_INT, i, 4, MPI_COMM_WORLD, &status);
			maiores = realloc(maiores, (cont + cont_i) * sizeof(int));
			MPI_Recv(maiores + cont, cont_i, MPI_INT, i, 5, MPI_COMM_WORLD, &status);

			for (int j = 0; j < cont_i; j++) {
				maiores[cont + j] += somatorio;
			}
			
			cont += cont_i;

			somatorio += tam_bloco;
			if (i < n % n_proc) {
				somatorio++;
			}
		}
		

		// imprime a resposta esperada
		printf("%d\n", cont);
		for (int i = 0; i < cont; i++) {
			printf("%d ", maiores[i]);
		}
		printf("\n");

		free(vet);
		free(maiores);
	} else { // recebe
		int n, limiar;
		MPI_Recv(&n, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
		MPI_Recv(&limiar, 1, MPI_INT, 0, 2, MPI_COMM_WORLD, &status);

		int* vet = malloc(n * sizeof(int));
		MPI_Recv(vet, n, MPI_INT, 0, 3, MPI_COMM_WORLD, &status);
		
		int* maiores = NULL;
		int cont = conta_maiores(vet, n, limiar, &maiores);

		MPI_Send((void*) &cont, 1, MPI_INT, 0, 4, MPI_COMM_WORLD);
		MPI_Send((void*) maiores, cont, MPI_INT, 0, 5, MPI_COMM_WORLD);
		
		free(vet);
		free(maiores);
	}

	// encerra MPI
	MPI_Finalize();

	return 0;
}