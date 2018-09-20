#ifndef STACK_H
#define STACK_H

typedef int var;
typedef struct stack stack;

stack* stack_create();
int stack_insert(stack*, var);
void stack_destroy(stack*);
void stack_print(stack*);
int stack_size(stack*);
int stack_isEmpty(stack*);
var stack_top(stack*);
int stack_remove(stack*, var*);

#endif