#include "bank.h"

typedef struct _stack{
    int top;
    Bank *bank;
} stack;

//cria a pilha
stack create_stack(Bank *b);

//insere na pilha
int push_stack(stack *s, elem* x);

//tira da pilha
int pop_stack(stack *s, elem* x);

//retorna se a pilha esta vazia
int isEmpty_stack(stack *s);