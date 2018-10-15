#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct stack stack;

/* Cria uma stack vazia, com o tamanho de cada elemento mandado por parametro */
stack* create_stack(size_t);

/* Desaloca a stack e todos os seus elementos */
void destroy_stack(stack*);

/* Insere um elemento na stack */
void push_stack(stack*, void*);

/* Remove o elemento do topo da stack */
void pop_stack(stack*);

/* Retorna o elemento do topo da stack */
void* top_stack(stack*);

/* Retorna um boolean informando se a stack esta vazia */
bool empty_stack(stack*);

#endif