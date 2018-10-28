#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//estructura de un nodo
typedef struct nodo {
	tab* valor;
	struct nodo *hijo, *padre;
} nodo;

//struct para la lista
struct lista {
	nodo *principio, *final;
	int tamano;
};

//crea una lista y la devuelve
lista* crea_lista() {
	lista* l = malloc(sizeof(lista));
	l->principio = l->final = NULL;
	l->tamano = 0;
	return l;
}

//limpa una lista y sus valores
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

//limpa una lista, pero no limpa sus valores
void limpa_lista_notab(lista* l) {
	if (l != NULL) {
		while(l->principio != NULL) {
			nodo* aux = l->principio->hijo;
			free(l->principio);
			l->principio = aux;
		}
		free(l);
	}
}

//crea una nueva tab en la lista
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

//inserta una tab en la posición deseada
void insere_pos(lista* l, tab* x, int pos) {
	nodo *actual, *viejo;
	nodo *p = malloc(sizeof(nodo));

	p->valor = x;

	//procura la posicion deseada
	actual = l->principio;
	while(actual != NULL && pos > 1) {
		actual = actual->hijo;
		pos--;
	}

	//cambia sus punteros
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

//actualiza la posicion de una tab, la retirando y inserindo nuevamente
void actualiza_tab(lista* l, char* titulo, int posicion) {
	if (l == NULL || l->principio == NULL || l->tamano == 1)
		return;

	//procura la tab con el titulo deseado
	nodo* elegido = l->principio;
	while(elegido != NULL && strcmp(elegido->valor->titulo, titulo))
		elegido = elegido->hijo;
	if (elegido == NULL)
		return;

	tab* valor = elegido->valor;

	//limpa elegido y actualiza principio y final de la lista
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

//devuelve un entero concatenado
int junta(nodo* n) {
	if (n == NULL) return 0;
	return n->valor->mes*1000000 + n->valor->dia*10000 + n->valor->hora*100 + n->valor->min;
}

//devuelve lo maximo en un intervalo
int maximo_intervalo(lista* l) {
	nodo *n = l->principio;
	int max;
	max = junta(n);
	
	while(n != NULL) {
		if (max < junta(n)) max = junta(n);		
		n = n->hijo;
	}
	
	return max;
}

//struct de un bucket
typedef struct cubo {
	tab* val;
	struct cubo* padre;
} cubo;

//ordena una lista por BucketSort
lista* ordena_lista(lista* l) {
	if (l == NULL || l->principio == NULL)
		return NULL;

	int max = maximo_intervalo(l);
	
	nodo* i = l->principio;
	cubo **vec = malloc(sizeof(cubo*) * (max+1));
	
	for (int i = 0; i < max+1; i++)
		vec[i] = NULL;
	
	//crea listas encadeadas para cada valor
	while(i != NULL) {
		cubo* aux = malloc(sizeof(cubo));
		aux->val = i->valor;
		aux->padre = vec[junta(i)];
		vec[junta(i)] = aux;		
		i = i->hijo;
	}
	
	//nueva lista ordenada
	lista* ret = crea_lista();
	for (int i = 0; i < max+1; i++) {
		while(vec[i] != NULL) {
			nueva_tab(ret, vec[i]->val);
			cubo* aux = vec[i]->padre;
			free(vec[i]);
			vec[i] = aux;
		}
	}
	
	free(vec);
	limpa_lista_notab(l);
	return ret;		
}

//imprime la lista
void muestra_lista(lista* l) {	
	nodo* aux = l->principio;
	while(aux != NULL) {
		printf("%s %s %02d/%02d %02d:%02d\n", aux->valor->titulo, aux->valor->sitio, aux->valor->dia, aux->valor->mes, aux->valor->hora, aux->valor->min);
		aux = aux->hijo;
	}
	printf("\n");	
}
