#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo {
	tab* valor;
	struct nodo *hijo, *padre;
} nodo;

struct lista {
	nodo *principio, *final;
	int tamano;
};

lista* crea_lista() {
	lista* l = malloc(sizeof(lista));
	l->principio = l->final = NULL;
	l->tamano = 0;
	return l;
}

void limpa_lista(lista* l) {
	if (l != NULL) {
		while(l->principio != NULL) {
			nodo* aux = l->principio->hijo;
			free(l->principio->valor);
			free(l->principio);
			l->principio = aux;
		}
		free(l);
	}
}

void nueva_tab(lista* l, tab* t) {
	if (l == NULL)
		return;
		
	nodo* n = malloc(sizeof(nodo));
	n->valor = t;
	n->hijo = NULL;
	n->padre = l->final;
	
	if (l->final == NULL) //first element of the lista
		l->principio = l->final = n;
	else {
		l->final->hijo = n;
		l->final = n;
	}

	l->tamano++;
}

char* tituloPonteiro(nodo* n) {
	if (n == NULL) return "NULL";
	return n->valor->titulo;
}

void insere_pos(lista* l, tab* x, int pos) {
	nodo *actual, *viejo;
	nodo *p = malloc(sizeof(nodo));

	p->valor = x;

	actual = l->principio;
	while(actual != NULL && pos > 1) {
		actual = actual->hijo;
		pos--;
	}

	if (l->principio == actual) {
		p->padre = NULL;
		p->hijo = l->principio;
		l->principio->padre = p;
		l->principio = p;
	} else if (actual == NULL) {
		p->hijo = NULL;
		p->padre = l->final;
		l->final->hijo = p;
		l->final = p;
    } else {
        viejo = actual->padre;
        p->hijo = actual;
        p->padre = viejo;
        viejo->hijo = p;
        actual->padre = p;
    }
}

void actualiza_tab(lista* l, char* titulo, int posicion) {
	if (l == NULL || l->principio == NULL || l->tamano == 1)
		return;

	nodo* elegido = l->principio;
	while(elegido != NULL && strcmp(elegido->valor->titulo, titulo))
		elegido = elegido->hijo;
	if (elegido == NULL)
		return;

	// printf("elegido: %p: %s [%s/%s]\n", elegido, tituloPonteiro(elegido), tituloPonteiro(elegido->padre), tituloPonteiro(elegido->hijo));

	tab* valor = elegido->valor;

	//limpa elegido
	if (elegido == l->principio) {
		l->principio = elegido->hijo;
	} else if (elegido == l->final) {
		l->final = elegido->padre;
	}

	if (elegido->hijo != NULL)
		elegido->hijo->padre = elegido->padre;
	if (elegido->padre != NULL)
		elegido->padre->hijo = elegido->hijo;

	free(elegido);

	insere_pos(l, valor, posicion);
}

int tamano_intervalo(lista* l) {
	node *n = l->principio;
	int min = l->principio->
}

void ordena_lista(lista* l) {
	if (l == NULL || l->principio == NULL)
		return;

	int n = l->tamano;
	int k = tamano_intervalo(l);
}

void muestra_lista(lista* l) {	
	nodo* aux = l->principio;
	while(aux != NULL) {
		printf("%s %s %d/%d %d:%d\n", aux->valor->titulo, aux->valor->sitio, aux->valor->dia, aux->valor->mes, aux->valor->hora, aux->valor->min);
		aux = aux->hijo;
	}
	printf("\n");	
}
