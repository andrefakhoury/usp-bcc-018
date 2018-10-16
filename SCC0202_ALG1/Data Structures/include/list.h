#ifndef LIST_H
#define LIST_H


typedef int var;
typedef struct list list;

list* list_create();
int list_insert(list*, var);
void list_destroy(list*);
void list_print(list*);
int list_size(list*);
int list_find(list*, var);
int list_remove(list*, var);
void list_sort(list*);

#endif