#include <stdio.h>
#include "utils.h"
#include "lista.h"
#include "pilha.h"
#include "fila_pilhas.h"

int main(int argc, char* argv[]) {
	if (argc <= 3) return ERROR;
	int n, k, p;
	sscanf(argv[1], "%d", &n);
	sscanf(argv[2], "%d", &k);
	sscanf(argv[3], "%d", &p);

	printf("%d %d %d\n", n, k, p);

	brinquedo teste;
	for (int i = 4; i < n+4 && i < argc; i++) {
		sscanf(argv[i], "%d,%s", &teste.id, teste.nome);
		printf("%d %s\n", teste.id, teste.nome);
	}

}