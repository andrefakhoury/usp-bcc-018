#ifndef LIST_H
#define LIST_H

#include "tab.h"

typedef struct lista lista;

lista* crea_lista();
void limpa_lista(lista* l);
void nueva_tab(lista* l, tab* t);
void actualiza_tab(lista* l, char* titulo, int posicion);
void ordena_lista(lista* l);
void muestra_lista(lista* l);

#endif