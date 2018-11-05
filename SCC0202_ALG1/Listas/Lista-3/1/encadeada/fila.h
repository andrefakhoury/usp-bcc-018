#include "lista.h"

typedef struct pessoa_ {
	char nome[100];
	Lista* lista_compras;
} Pessoa;

typedef struct No {
	Pessoa info;
	struct No* prox;
} No;

typedef struct {
	No *ini, *fim;
} Fila;