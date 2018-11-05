#include "banco.h"

void format(Banco *b) {
    // cria lista de vazios
    for (int i=0; i < TAM-1; i++)
        b->vet[i].prox = i+1;
    b->vet[TAM-1].prox = -1;
    b->vazios = 0;
    return;
}

int getnode(Banco *b) {
    int p;
    if (b->vazios == -1)
        return -1; // erro
    p = b->vazios; // cria cópia do primeiro vazio
    b->vazios = b->vet[b->vazios].prox; // atualiza primeiro vazio
    return p; // sucesso
}

void freenode(Banco *b, int pos) {
    b->vet[pos].prox = b->vazios; // próximo do bloco liberado é o inicio atual da lista
    b->vazios = pos; // novo bloco passa a ser o início
    return;
}

int isFullBanco(Banco *b) {
    return (b->vazios == -1);
}

int getcodProcesso(Banco *b, int pos) {
    return b->vet[pos].codProcesso;
}

int getProx(Banco *b, int pos) {
    return b->vet[pos].prox;
}

void setInfo(Banco *b, int pos, int x) {
    b->vet[pos].codProcesso = x;
    return;
}

void setProx(Banco *b, int pos, int prox) {
    b->vet[pos].prox = prox;
    return;
}
