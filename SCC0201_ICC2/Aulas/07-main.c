#include <time.h>
#include "stdall.h"

int menu(int* op) {
	printf("\n1: Gera outro vetor\n");
	printf("2: Insertion Sort\n");
	printf("3: Merge Sort\n");
	printf("4: Busca Sequencial\n");
	printf("5: Busca Sequencial Recursiva\n");
	printf("6: Busca Binaria \n");
	printf("7: Busca Binaria Recursiva\n");
	printf("8: Quick Sort\n");
	printf("0: Sair\n");
	scanf("%d", op); printf("\n\n");
	return *op;
}

void chamaBusca(int* vet, int N, int min, int max, int op) {
	if (op < 4 || op > 7) return;
	int chave = min;
	printf(">Digite o valor para ser encontrado dentro do intervalo\n [%d, %d] ou fora do intervalo para sair\n", min, max);
	while (scanf("%d", &chave), chave >= min && chave <= max) {
		int pos;
		if (op == 4) pos = buscaSequencial(vet, N, chave);
		else if (op == 5) pos = buscaSequencialRec(vet, N, 0, chave);
		else if (op == 6) pos = buscaBinaria(vet, N, chave);
		else if (op == 7) pos = buscaBinariaRec(vet, 0, N, chave);

		if (pos == FAIL) printf("Chave nao encontrada\n\n");
		else printf("Chave encontrada na pos %d\n\n", pos);
	}
}

int pivoInicial(int l, int r) {
	return l;
}

int pivoCentral(int l, int r) {
	return (l+r)/2;
}

int pivoRand(int l, int r) {
	return (rand()%(r-l)+l);
}

int main(int argc, char* argv[]) {
	int N, min, max;	
	printf("Digite N, MIN e MAX: ");
	scanf("%d%d%d", &N, &min, &max);
	srand(time(NULL));

	int* vet = geraVetor(N, min, max);
	if (DEBUG) imprimeVetor(vet, N);

	int op;
	while(menu(&op)) {
		switch(op) {
			case 1:	if (vet != NULL) free(vet);
					vet = geraVetor(N, min, max);
					if (DEBUG) imprimeVetor(vet, N);
					break;
			case 2: insertionSort(vet, N);
					if (DEBUG) imprimeVetor(vet, N);
					break;
			case 3: mergeSort(vet, 1, N);
					if (DEBUG) imprimeVetor(vet, N);
					break;
			case 8: quickSort(vet, 0, N-1, pivoCentral);
					if (DEBUG) imprimeVetor(vet, N);
					break;
			default: chamaBusca(vet, N, min, max, op);
		}
	}

	free(vet);
	return 0;
}