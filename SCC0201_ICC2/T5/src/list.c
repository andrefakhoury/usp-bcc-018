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

void actualiza_tab(lista* l, char* titulo, int posicion) {
	if (l == NULL || l->principio == NULL)
		return;

	nodo* elegido = l->principio;
	while(elegido != NULL && strcmp(elegido->valor->titulo, titulo))
		elegido = elegido->hijo;
	if (elegido == NULL)
		return;

	nodo* viejo = l->principio;
	while(viejo != l->final && --posicion)
		viejo = viejo->hijo;

	if (elegido == viejo)
		return;

	printf("elegido: %p: %s [%s/%s]\n", elegido, tituloPonteiro(elegido), tituloPonteiro(elegido->padre), tituloPonteiro(elegido->hijo));
	printf("viejo: %p: %s [%s/%s]\n", viejo, tituloPonteiro(viejo), tituloPonteiro(viejo->padre), tituloPonteiro(viejo->hijo));

	// if (elegido == l->final)
	// 	l->final = elegido->padre;

	nodo *antEle = elegido->padre;
	nodo *antViejo = viejo->padre;

	antEle->hijo = elegido->hijo;
	
	elegido->hijo = viejo;
	elegido->padre = viejo->padre;

	viejo->padre = elegido;
	
	if (viejo != l->principio)
		antViejo->hijo = elegido;
	else
		l->principio = elegido;





	// if (elegido == l->final) {
	// 	l->final = elegido->padre;
	// } else if (elegido == l->principio) {
	// 	l->principio = elegido->hijo;
	// } else if (viejo == l->final) {
	// 	l->final = elegido;
	// } else if (viejo == l->principio) {
	// 	l->principio = elegido;
	// }

	// nodo* ayuda = viejo->padre;

	// viejo->padre = elegido;
	// elegido->padre->hijo = elegido->hijo;
	// if (elegido->hijo != NULL)
	// 	elegido->hijo->padre = elegido->padre;
	// elegido->padre = ayuda;

}

void ordena_lista(lista* l) {
	printf("hola\n");
}

void muestra_lista(lista* l) {	
	nodo* aux = l->principio;
	while(aux != NULL) {
		printf("%s %s %d/%d %d:%d\n", aux->valor->titulo, aux->valor->sitio, aux->valor->dia, aux->valor->mes, aux->valor->hora, aux->valor->min);
		aux = aux->hijo;
	}
	printf("\n");	
}
