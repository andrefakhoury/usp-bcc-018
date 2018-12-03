#include <stdlib.h>
#include <stdio.h>
#include "listaord.h"

void cria(ListaOrd *l) {
    l->ini = NULL;
    return;
}

void busca_interna(ListaOrd *l, elem x, No **ant, No **p) {
    // ant, p => No **
    // *ant, *p => No *
    // **ant, **p => No
    *ant = NULL;
    *p = l->ini;
    while (*p != NULL && (*p)->info < x) {
        *ant = *p;
        *p = (*p)->prox;
    }
    return;
}

int insere(ListaOrd *l, elem x) {
    No *novo, *ant, *p;
    busca_interna(l, x, &ant, &p); // busca primeiro maior ou igual a x
    if (p != NULL && p->info == x)
        return 1; // erro, elemento repetido
    novo = (No *) malloc(sizeof(No));
    if (novo == NULL)
        return 1; // erro, memoria insuficiente
    novo->info = x; // copia informacao
    // atualiza ponteiros
    novo->prox = p;
    if (ant == NULL)
        l->ini = novo; // insere no inicio
    else
        ant->prox = novo; // insere no meio ou fim
    return 0; // sucesso
}

int remover(ListaOrd *l, elem x) {
    No *ant, *p;
    busca_interna(l, x, &ant, &p);
    if (p == NULL || p->info != x)
        return 1; // erro
    if (l->ini == p)
        l->ini = l->ini->prox; // remove do inicio
    else
        ant->prox = p->prox; // remove do meio ou do final
    free(p);
    return 0; // sucesso
}

void imprime(ListaOrd l) {
    while (l.ini != NULL) {
        printf("%c", l.ini->info);
        l.ini = l.ini->prox;
    }
    printf("\n");
    return;
}

int busca(ListaOrd l, elem x) {
    while(l.ini != NULL && l.ini->info < x)
        l.ini = l.ini->prox;
    return (l.ini != NULL && l.ini->info == x);
}

int esta_vazia(ListaOrd l) {
    return (l.ini == NULL);
}
