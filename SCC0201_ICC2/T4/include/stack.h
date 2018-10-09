#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct stack stack;

stack* create_stack(size_t);
void destroy_stack(stack*);
void push_stack(stack*, void*);
void* top_stack(stack*);
bool full_stack(stack*, int);
bool empty_stack(stack*);
void pop_stack(stack*);

#endif