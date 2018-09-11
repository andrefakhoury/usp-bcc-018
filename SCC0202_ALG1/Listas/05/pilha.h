#include <stdlib.h>

#define TamPilha 100
typedef char* elem;
typedef struct pilha {
    elem vet[TamPilha];
    int topo;
} Pilha;

void cria_pilha(Pilha* p);

int push(Pilha* p, elem x);

int isEmpty(Pilha p);

int pop(Pilha* p, elem* x);

elem top(Pilha p, int* erro);

void empty(Pilha* p);

int tamanho(Pilha p);

int iguais(Pilha p1, Pilha p2);
