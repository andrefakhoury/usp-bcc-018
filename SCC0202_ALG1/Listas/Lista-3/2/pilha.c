#include "pilha.h"

void cria(Pilha *p, Banco *b) {
    p->topo = -1; // pilha vazia
    p->banco = b; // copia ponteiro do banco
    return;
}

int isEmpty(Pilha *p) {
    return (p->topo == -1);
}

int isFull(Pilha *p) {
    return isFullBanco(p->banco);
}

int push(Pilha *p, int x) {
    int aux = getnode(p->banco); // malloc simulado
    if (aux == -1)
        return 1; // erro
    setInfo(p->banco, aux, x); // copia info
    // atualiza encadeamento
    setProx(p->banco, aux, p->topo);
    p->topo = aux;
    return 0; // sucesso
}

int pop(Pilha *p, int *x) {
    int aux;
    if (isEmpty(p))
        return 1; // erro
    *x = getcodProcesso(p->banco, p->topo); // copia informacao
    // atualiza encadeamento
    aux = p->topo;
    p->topo = getProx(p->banco, p->topo);
    freenode(p->banco, aux); // libera memoria
    return 0; // sucesso
}

int topo(Pilha* p) {
	return getcodProcesso(p->banco, p->topo);
}