#include "banco.h"

typedef struct {
    int topo;
    Banco *banco;
} Pilha;

void cria(Pilha *p, Banco *b);
int isEmpty(Pilha *p);
int isFull(Pilha *p);
int push(Pilha *p, int x);
int pop(Pilha *p, int *x);
int topo(Pilha* p);