#include <stdlib.h>
#include <stdio.h>
#include "listagen.h"

void cria(ListaGen *l) {
    l->ini = NULL;
    return;
}

void destroiNo(No *no) {
    if (no != NULL) {
        if (no->tipo == lista)
            destroiNo((No *) no->info); // apaga sublista
        destroiNo(no->prox); // apaga resto
        free(no); // apaga no
    }
    return;
}

void destroi(ListaGen *l) {
    destroiNo(l->ini);
    l->ini = NULL;
    return;
}

int insereAtomo(ListaGen *l, elem x) {
    No *novo = malloc(sizeof(No));
    if (novo == NULL)
        return 1; // erro, nao criou no
    novo->info = malloc(sizeof(elem));
    if (novo->info == NULL) {
        free(novo);
        return 1; // erro, nao criou espaco para info
    }
    novo->tipo = atomo;
    *((elem *) novo->info) = x;
    novo->prox = l->ini;
    l->ini = novo;
    return 0;
}

// inutiliza lista de origem
int insereLista(ListaGen *l, ListaGen *x) {
    No *novo = malloc(sizeof(No));
    if (novo == NULL)
        return 1; // erro, nao criou no
    novo->tipo = lista;
    novo->info = x->ini;
    cria(x); // inutiliza lista de origem
    novo->prox = l->ini;
    l->ini = novo;
    return 0;
}

void imprimeNo(No *no) {
    if (no != NULL) {
        if (no->tipo == atomo)
            printf("%c ", *((elem *)no->info)); // imprime atomo
        else {
            printf("( ");
            imprimeNo(((No *) no->info)); // imprime sublista
            printf(") ");
        }
        imprimeNo(no->prox); // imprime resto
    }
    return;
}

void imprime(ListaGen l) {
    printf("( ");
    imprimeNo(l.ini);
    printf(")\n");
    return;
}

int buscaNo(No *no, elem x) {
    if (no != NULL) {
        if (no->tipo == atomo)
            return (*((elem *) no->info) == x) || buscaNo(no->prox,x);
        else
            return buscaNo(((No *) no->info),x) || buscaNo(no->prox,x);
    }
    return 0;
}

int busca(ListaGen l, elem x) {
    return buscaNo(l.ini, x);
}

void profundidadeNo(No *no, int prof, int *pprofMax) {
    if (no != NULL) {
        if (no->tipo == lista && no->info != NULL)
            profundidadeNo(((No *) no->info), prof + 1, pprofMax);
        profundidadeNo(no->prox, prof, pprofMax);
    }
    if (prof > *pprofMax)
        *pprofMax = prof;
    return;
}

int profundidade(ListaGen l) {
    int prof = 0, profMax = 0;
    if (l.ini != NULL)
        profundidadeNo(l.ini, prof + 1, &profMax);
    return profMax;
}

/*** nao feito em aula; inserido atendendo a pedidos ***/
int iguaisNo(No *no1, No *no2) {
    if ((no1 == NULL && no2 != NULL) || (no1 != NULL && no2 == NULL))
        return 0; // um nulo e um nao nulo
    else {
        if (no1 == NULL)
            return 1; // dois nulos
        else { // dois nao nulos
            if (no1->tipo != no2->tipo)
                return 0; // tipos distintos
            else { // tipos iguais
                if (no1->tipo == atomo)
                    return ( *((elem *) no1->info) == *((elem *) no2->info) && iguaisNo(no1->prox, no2->prox)); // dois atomos
                else
                    return ( iguaisNo(((No *) no1->info), ((No *) no2->info)) && iguaisNo(no1->prox, no2->prox)); // duas sublistas
            }
        }
    }
}

int iguais(ListaGen l1, ListaGen l2) {
    return iguaisNo(l1.ini, l2.ini);
}

int iguaisEstNo(No *no1, No *no2) {
    if ((no1 == NULL && no2 != NULL) || (no1 != NULL && no2 == NULL))
        return 0; // um nulo e um nao nulo
    else {
        if (no1 == NULL)
            return 1; // dois nulos
        else { // dois nao nulos
            if (no1->tipo != no2->tipo)
                return 0; // tipos distintos
            else { // tipos iguais
                if (no1->tipo == atomo)
                    return iguaisEstNo(no1->prox, no2->prox); // dois atomos
                else
                    return ( iguaisEstNo(((No *) no1->info), ((No *) no2->info)) && iguaisEstNo(no1->prox, no2->prox)); // duas sublistas
            }
        }
    }
}

int iguaisEst(ListaGen l1, ListaGen l2) {
    return iguaisEstNo(l1.ini, l2.ini);
}
/*******************************************************/
