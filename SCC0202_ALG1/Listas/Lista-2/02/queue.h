#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <string.h>

typedef struct p {
	char nome[20];
	bool preferencial;
	int itens;
} Pessoa;

typedef struct queue queue;
typedef Pessoa var;

queue* queue_create();
int queue_insert(queue*, var);
void queue_destroy(queue*);
int queue_size(queue*);
void queue_print(queue*);
int queue_isEmpty(queue*);
int queue_isFull(queue*);
int queue_remove(queue*, var*);
var queue_vbegin(queue*);

#endif