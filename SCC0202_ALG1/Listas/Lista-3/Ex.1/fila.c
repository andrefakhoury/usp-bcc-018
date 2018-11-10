#include "fila.h"
#include <stdlib.h>
#include <stdio.h>

fila create_fila() {
	fila f;
	f.vec = NULL;
	f.sz = 0;
	return f;
}

void insert_pessoa(fila* f, pessoa p) {
	f->sz++;
	f->vec = (pessoa*) realloc(f->vec, sizeof(pessoa) * f->sz);
	f->vec[f->sz-1] = p;
}

void destroi_fila(fila* f) {
	for (int i = 0; i < f->sz; i++)
		destroy_lista(&f->vec[i].lista_compras);
	free(f->vec);
}

void imprime_fila(fila f) {
	for (int i = 0; i < f.sz; i++) {
		printf("---%s---\n", f.vec[i].nome);
		print_lista(f.vec[i].lista_compras);		
		printf("\n");
	}
}
