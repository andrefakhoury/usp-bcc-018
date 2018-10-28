#ifndef LIST_H
#define LIST_H

#include "tab.h"

typedef struct lista lista;

//crea una lista
lista* crea_lista();

//limpa la lista
void limpa_lista(lista* l);

//crea una tab en la lista a partir de los valores enviados por parámetro
void nueva_tab(lista* l, tab* t);

//actualiza la posicion de una tab con titulo "titulo" para la posicion "posicion"
void actualiza_tab(lista* l, char* titulo, int posicion);

//ordena una lista utilizando BucketSort
lista* ordena_lista(lista* l);

//imprime los valores de una lista
void muestra_lista(lista* l);

#endif
