#ifndef LIST_H
#define LIST_H

#include <string.h>
#include <stdbool.h>

#define RECEPCAO 0
#define CERIMONIA 1
#define BANQUETE 2

typedef struct list list;

typedef struct c {
	char nome[20];
	bool evento[3];
} Convidado;
typedef Convidado var;

list* list_create();
int list_insert(list*, var);
void list_destroy(list*);
int list_size(list*);
//int list_find(list*, var);
//int list_remove(list*, var);
var list_vbegin(list*);
void list_print_byName(list* l, char name[20]);
void list_print_byOption(list* l, int op);
void list_print_names(list* l);
#endif