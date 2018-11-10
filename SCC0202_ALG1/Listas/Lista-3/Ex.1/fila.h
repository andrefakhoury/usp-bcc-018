#ifndef FILA_H
#define FILA_H

#include "lista.h"
#include "pessoa.h"

typedef struct fila {
	pessoa* vec;
	int sz;
} fila;

//cria uma fila
fila create_fila();

//insere uma pessoa na fila
void insert_pessoa(fila* f, pessoa p);

//destroi a fila
void destroi_fila(fila* f);

//imprime a fila
void imprime_fila(fila f);

#endif
