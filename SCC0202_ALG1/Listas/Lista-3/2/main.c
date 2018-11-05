#include <stdio.h>
#include "pilha.h"

int main() {
	Banco b;
	Pilha p1;

	format(&b);
	cria(&p1, &b);

	int cod = 1;
	while (!isFull(&p1)) {
		push(&p1, cod);
		cod++;
	}

	printf("%d\n", topo(&p1));

	return 0;

	while (!pop(&p1, &cod))
		printf("%d\n", cod);

	return 0;
}
