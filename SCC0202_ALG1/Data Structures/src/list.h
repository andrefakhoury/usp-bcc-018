#ifndef LIST_H
#define LIST_H


typedef int var;

typedef struct node node;
typedef struct list list;

list* list_create();
int list_insert(list*, var);
void list_destroy(list*);
void list_print(list*);

#endif