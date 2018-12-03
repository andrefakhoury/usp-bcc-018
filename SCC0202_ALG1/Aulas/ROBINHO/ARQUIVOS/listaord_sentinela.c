#include <stdlib.h>
#include <stdio.h>
#include "listaord_sentinela.h"

int cria(ListaOrd *l) {
    l->sentinela = malloc(sizeof(No));
    if (l->sentinela == NULL)
        return 1; // erro
    l->sentinela->prox = NULL;
    l->ini = l->sentinela;
    return 0; // sucesso
}

void destroi(ListaOrd *l) {
    No *aux;
    while (l->ini != NULL) {
        aux = l->ini;
        l->ini = l->ini->prox;
        free(aux);
    }
    l->sentinela = NULL;
}

void busca_interna(ListaOrd *l, elem x, No **ant, No **p) {
    l->sentinela->info = x;
    *ant = NULL;
    *p = l->ini;
    while ((*p)->info < x) {
        *ant = *p;
        *p = (*p)->prox;
    }
}

int insere(ListaOrd *l, elem x) {
    No *novo, *ant, *p;
    busca_interna(l, x, &ant, &p); // busca primeiro maior ou igual a x
    if (p != l->sentinela && p->info == x) return 1; // erro, elemento repetido
    novo = (No *) malloc(sizeof(No));
    if (novo == NULL) return 1; // erro, memoria insuficiente
    novo->info = x; // copia informacao
    
    // atualiza ponteiros
    novo->prox = p;
    if (ant == NULL) l->ini = novo; // insere no inicio
    else ant->prox = novo; // insere no meio ou fim
    return 0; // sucesso
}

int remover(ListaOrd *l, elem x) {
    No *ant, *p;
    busca_interna(l, x, &ant, &p);
    if (p == l->sentinela || p->info != x)
        return 1; // erro
    if (l->ini == p)
        l->ini = l->ini->prox; // remove do inicio
    else
        ant->prox = p->prox; // remove do meio ou do final
    free(p);
    return 0; // sucesso
}

void imprime(ListaOrd l) {
    while (l.ini != l.sentinela) {
        printf("%d", l.ini->info);
        l.ini = l.ini->prox;
    }
    printf("\n");
    return;
}

int busca(ListaOrd l, elem x) {
    l.sentinela->info = x;
    while(l.ini->info < x)
        l.ini = l.ini->prox;
    return (l.ini != l.sentinela && l.ini->info == x);
}

int esta_vazia(ListaOrd l) {
    return (l.ini == l.sentinela);
}
