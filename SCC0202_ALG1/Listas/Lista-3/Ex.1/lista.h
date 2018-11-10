#ifndef LISTA_H
#define LISTA_H

#include "produto.h"

typedef struct lista {
	produto* vec;
	int sz;
} lista;

//cria uma lista
lista create_lista();

//insere um produto na lista
void insert_produto(lista* l, produto p);

//imprime a lista
void print_lista(lista l);

//destroi a lista
void destroy_lista(lista* l);

#endif
