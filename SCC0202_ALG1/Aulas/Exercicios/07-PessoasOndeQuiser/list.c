#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void create(list* l) {
	l->begin = l->end = NULL;
}

void apaga(list* l) {
	if (!l) return;

	while(l->begin) {
		no* aux = l->begin->next;
		free(l->begin);
		l->begin = aux;
	}
	l->end = NULL;
}

void imprime(list l) {
	while (l.begin) {
		printf("%d ", l.begin->value);
		l.begin = l.begin->next;
	} printf("\n");
}

int include(list* l, elem x, int pos) {
	if (l == NULL) return 1;

	no* atual;
	no* p = (no*) malloc(sizeof(no));
	if (p == NULL) return 1;

	p->value = x;

	//atualiza encadeamento
	if (l->begin == NULL) { //lista vazia
		p->next = p->prev = NULL;
		l->begin = l->end = p;
	} else {
		atual = l->begin;

		while (atual != NULL && pos-1 > 0) {
			atual = atual->next;
			pos--;
		}

		if (atual == l->begin) { //insercao no inicio
			p->prev = NULL;
			p->next = l->begin;
			l->begin->prev = p;
			l->begin = p;
		} else if (atual == NULL) { //insere no final
			p->prev = l->end;
			p->next = NULL;
			l->end->next = p;
			l->end = p;
		} else { //insere no meio
			p->prev = atual->prev;
			p->next = atual;
			atual->prev->next = p;
			atual->prev = p;
		}
	}
	return 0;
}

//10    20