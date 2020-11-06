/**
------------------------------------------------------
--- SSC0903 - Computação de Alto Desempenho (2020) ---
------------------------------------------------------

Atividade 06-1: Token Ring

Desenvolvida por:
- Grupo 1
-- André Luís Mendes Fakhoury
-- Debora Buzon da Silva
-- Gustavo Vinicius Vieira Silva Soares
-- Thiago Preischadt Pinheiro
*/

#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
	// n: numero de processos dentro do grupo
	// i: rank atual
	int n, i;

	// inicializa MPI
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &n);
	MPI_Comm_rank(MPI_COMM_WORLD, &i);
	
	if (i == 0) { // envia, recebe, imprime
		MPI_Send((void*) &i, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
		MPI_Recv(&i, 1, MPI_INT, n - 1, 1, MPI_COMM_WORLD, &status);
		printf("%d\n", i);
	} else { // recebe, incrementa, envia
		MPI_Recv(&i, 1, MPI_INT, i - 1, 1, MPI_COMM_WORLD, &status);
		i++;
		MPI_Send((void*) &i, 1, MPI_INT, (i + 1) % n, 1, MPI_COMM_WORLD);
	}

	// encerra MPI
	MPI_Finalize();
	return 0;
}
