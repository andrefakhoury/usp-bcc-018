#include "lista.h"
#include <stdlib.h>
#include <stdio.h>

lista create_lista() {
	lista l;
	l.vec = NULL;
	l.sz = 0;
	return l;
}

void insert_produto(lista* l, produto p) {
	l->vec = (produto*) realloc(l->vec, sizeof(produto) * (l->sz + 1));
	l->sz++;
	l->vec[l->sz-1] = p;

	for(int i = l->sz - 1; i >= 1 && l->vec[i-1].preco * l->vec[i-1].quantidade > p.preco * p.quantidade; --i) {
		l->vec[i] = l->vec[i-1];
		l->vec[i-1] = p;
	}
}

void print_lista(lista l) {
	for (int i = 0; i < l.sz; i++) {
		produto p = l.vec[i];
		printf("%s: R$%.02f x %d\n", p.nome, p.preco, p.quantidade);
	}
}

void destroy_lista(lista* l) {
	free(l->vec);
}
