#ifndef PESSOA_H
#define PESSOA_H

#include "lista.h"

//struct de uma pessoa, com nome e sua lista de compras
typedef struct pessoa {
	char nome[100];
	lista lista_compras;
} pessoa;

#endif
