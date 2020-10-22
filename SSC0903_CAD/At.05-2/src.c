/**
------------------------------------------------------
--- SSC0903 - Computação de Alto Desempenho (2020) ---
------------------------------------------------------

Atividade 05 - 2: Encontrar o maior elemento de um vetor

Desenvolvida por:
- Grupo 1
-- André Luís Mendes Fakhoury
-- Debora Buzon da Silva
-- Gustavo Vinicius Vieira Silva Soares
-- Thiago Preischadt Pinheiro
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define T 16
#define min(a, b) ((a) < (b) ? (a) : (b))

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("Invalid arguments. Use %s <size>\n", argv[0]);
		return 1;
	}

	int size = atoi(argv[1]);
	int* vec = malloc(size * sizeof(int));

	int max_total = 0;

	omp_lock_t mylock;
	omp_init_lock(&mylock);

	double wtime = omp_get_wtime();

	#pragma omp parallel num_threads(T) shared(max_total)
	{
		// calculate which block this thread will calculate
		int id_thread = omp_get_thread_num();
		int total_threads = omp_get_num_threads();

		int start_block = size / total_threads * id_thread + min(id_thread, size % total_threads);
		int size_block = size / total_threads + (id_thread < size % total_threads ? 1 : 0);

		// fill vector
		for (int i = start_block; i < start_block + size_block; i++) {
			vec[i] = 1;
		}

		if (size / 2 >= start_block && size / 2 < start_block + size_block)
			vec[size/2] = size;

		#pragma omp barrier
		
		// calculate local maximum
		int max = 0;
		for (int i = start_block; i < start_block + size_block; i++) {
			if (vec[i] > max) {
				max = vec[i];
			}
		}

		// update global maximum
		omp_set_lock(&mylock);
		if (max > max_total)
			max_total = max;
		omp_unset_lock(&mylock);
	}

	/* --- End of parallel block --------------------------------------------------------- */

	wtime = omp_get_wtime() - wtime;

	printf("Size = %d | Maximum element: %d. Elapsed time: %.5lf\n", size, max_total, wtime);

	omp_destroy_lock(&mylock);
	free(vec);

	return 0;
}
