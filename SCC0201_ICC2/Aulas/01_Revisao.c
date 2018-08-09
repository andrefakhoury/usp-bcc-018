/*	Aula 01 - Revisao

	Dado um numero N, eh criado um vetor de tamanho N
	com valores aleatorios, e informa, para cada posicao
	do vetor, a quantidade de elementos com valor maior */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG 0

/*	preencheVetor
		Funcao que aloca um vetor dinamicamente
		e preenche seus valores como aleatorios
	Parametros
		int total: tamanho do vetor
	Retorno
		int* ret: endereco na heap com o vetor
*/
int* preencheVetor(int total) {
	int* ret = NULL;
	ret = malloc(total * sizeof(int));

	if (ret == NULL) return NULL;

	int max = total/2+1;

	for (int i = 0; i < total; i++)
		ret[i] = rand()%max;

	return ret;
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("Informe o tamanho\n");
		return 1;
	}

	srand(time(NULL));

	int N;
	sscanf(argv[1], "%d", &N);

	if (N < 1)  {
		printf("Coloca um tamanho maior\n");
		return 2;
	}

	int* vet = NULL;
	vet = preencheVetor(N);

	if (vet == NULL) {
		printf("Erro na alocacao\n");
		return -1;
	}

	if (DEBUG) {
		for (int i = 0; i < N; i++) {
			printf("%d ", vet[i]);
		} printf("\n");
	}

	clock_t c1, c2;
	double tempo;

	c1 = clock();
	int cont;
	for (int i = 0; i < N; i++) {
		cont = 0;
		for (int j = 0; j < N; j++)
			if (vet[j] > vet[i]) cont++;
		if (DEBUG) printf("%d ", cont);
	} if (DEBUG) printf("\n");
	c2 = clock();

	tempo = (c2-c1)/(double)CLOCKS_PER_SEC;
	printf("%.6lf\n", tempo);
	free(vet);
	return 0;
}