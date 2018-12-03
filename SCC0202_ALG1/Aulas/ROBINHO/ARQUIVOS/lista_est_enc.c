#include "lista_est_enc.h"

void cria(Lista *l) {
    // cria lista de vazios
    for (int i=0; i < TAM-1; i++)
        l->vet[i].prox = i+1;
    l->vet[TAM-1].prox = -1;
    l->vazios = 0;
    l->ini = -1; // lista de elementos esta vazia
    return;
}

int getnode(Lista *l) {
    int p;
    if (l->vazios == -1)
        return -1; // erro
    p = l->vazios; // cria cópia do primeiro vazio
    l->vazios = l->vet[l->vazios].prox; // atualiza primeiro vazio
    return p; // sucesso
}

void freenode(Lista *l, int pos) {
    l->vet[pos].prox = l->vazios; // próximo do bloco liberado é o inicio atual da lista
    l->vazios = pos; // novo bloco passa a ser o início
    return;
}

int isEmpty(Lista *l) {
    return (l->ini == -1);
}

int isFull(Lista *l) {
    return (l->vazios == -1);
}

int insere_comeco(Lista *l, elem x) {
    int aux = getnode(l); // malloc simulado
    if (aux == -1)
        return 1; // erro
    l->vet[aux].info = x; // copia info
    // atualiza encadeamento
    l->vet[aux].prox = l->ini;
    l->ini = aux;
    return 0; // sucesso
}

int retira_comeco(Lista *l, elem *x) {
    int aux;
    if (isEmpty(l))
        return 1; // erro
    *x = l->vet[l->ini].info; // copia informacao
    // atualiza encadeamento
    aux = l->ini;
    l->ini = l->vet[l->ini].prox;
    freenode(l,aux); // libera memoria
    return 0; // sucesso
}

int insere_final(Lista *l, elem x) {
    int atual, ant;
    int aux = getnode(l); // malloc simulado
    if (aux == -1)
        return 1; // erro
    l->vet[aux].info = x; // copia info
    // atualiza encadeamento
    l->vet[aux].prox = -1;
    atual = l->ini;
    ant = -1;
    while (atual != -1) {
        ant = atual;
        atual = l->vet[atual].prox;
    }
    if (ant == -1)
        l->ini = aux; // insere primeiro
    else
        l->vet[ant].prox = aux;
    return 0; // sucesso
}
