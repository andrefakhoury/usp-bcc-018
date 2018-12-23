#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

void cria(AVL *a) {
    a->raiz = NULL; // cria uma arvore vazia
    return;
}

void destroiSub(No *p) {
    if (p == NULL)
        return;
    destroiSub(p->esq); // destroi subarvore esquerda
    destroiSub(p->dir); // destroi subarvore direita
    free(p); // apaga o raiz da subarvore
    return;
}

void destroi(AVL *a) {
    destroiSub(a->raiz); // inicia recursao
    a->raiz = NULL;
    return;
}

int vazia(AVL a) {
    return a.raiz == NULL;
}

void imprimeSub(No *p) {
    printf("{");
    if (p != NULL) {
        printf("%d:%d, ", p->info, p->fb);
        imprimeSub(p->esq);
        printf(", ");
        imprimeSub(p->dir);
    }
    printf("}");
    return;
}

void imprime(AVL a) {
    imprimeSub(a.raiz);
    printf("\n");
    return;
}

int alturaSub(No *p) {
    int aesq, adir;
    if (p == NULL)
        return 0; // arvore nula
    aesq = alturaSub(p->esq); // altura da subarvore esquerda
    adir = alturaSub(p->dir); // altura da subarvore direita
    return (aesq > adir)? aesq + 1 : adir + 1;
}

int altura(AVL a) {
    return alturaSub(a.raiz); // inicia recursao
}

void preOrdemSub(No *p) {
    if (p != NULL) {
        printf("%d ", p->info); // processa antes de varrer subarvores
        preOrdemSub(p->esq); // varre lado esquerdo
        preOrdemSub(p->dir); // varre lado direito
    }
    return;
}

void preOrdem(AVL a) {
    preOrdemSub(a.raiz); // inicia recursao
    printf("\n");
    return;
}

void emOrdemSub(No *p) {
    if (p != NULL) {
        emOrdemSub(p->esq); // varre lado esquerdo
        printf("%d ", p->info); // processa entre uma subarvore e a outra
        emOrdemSub(p->dir); // varre lado direito
    }
    return;
}

void emOrdem(AVL a) {
    emOrdemSub(a.raiz); // inicia recursao
    printf("\n");
    return;
}

void posOrdemSub(No *p) {
    if (p != NULL) {
        posOrdemSub(p->esq); // varre lado esquerdo
        posOrdemSub(p->dir); // varre lado direito
        printf("%d ", p->info); // processa apos subarvores
    }
    return;
}

void posOrdem(AVL a) {
    posOrdemSub(a.raiz); // inicia recursao
    printf("\n");
    return;
}

int buscaSub(No *p, elem x) {
    if (p == NULL)
        return 0; // nao achou
    if (p->info == x)
        return 1; // achou
    return (x < p->info) ? buscaSub(p->esq, x) : buscaSub(p->dir, x);
}

int busca(AVL a, elem x) {
    return buscaSub(a.raiz, x); // inicia recursao
}

// rotacao simples a esquerda
void E(No **p) {
    No *novoRaiz, *realocar;

    novoRaiz = (*p)->dir;
    realocar = novoRaiz->esq;
    novoRaiz->esq = *p;
    (*p)->dir = realocar;
    *p = novoRaiz;
}

// rotacao simples a direita
void D(No **p) {
    No *novoRaiz, *realocar;
    novoRaiz = (*p)->esq;
    realocar = novoRaiz->dir;
    novoRaiz->dir = *p;
    (*p)->esq = realocar;
    *p = novoRaiz;
}

void ED(No **p) {
    E(&((*p)->esq));
    D(p);
}

void DE(No **p) {
    D(&((*p)->dir));
    E(p);
}

No *criaNo(elem info, No *esq, No *dir, int fb) {
    No *nova = malloc(sizeof(No));
    if (nova != NULL) {
        nova->info = info;
        nova->esq = esq;
        nova->dir = dir;
        nova->fb = fb;
    }
    return nova;
}

// atualiza fatores de balanceamento apos a rotacao dupla
void atualizaFB(No *p) {
    switch (p->fb) {
        case 1:
            p->dir->fb = 0;
            p->esq->fb = -1;
            break;
        case -1:
            p->dir->fb = 1;
            p->esq->fb = 0;
            break;
        case 0:
            p->dir->fb = 0;
            p->esq->fb = 0;
            break;
    }
    p->fb = 0;
}

int insercaoSub(No **p, elem x, int *cresceu) {
    int retorno;
    if (*p == NULL) {
        *p = criaNo(x, NULL, NULL, 0); // insere
        *cresceu = 1; // subarvore cresceu; era nula e agora tem o raiz
        return *p == NULL; // erro de memoria ou sucesso
    }
    if ((*p)->info == x)
        return 1; // erro, achou
    retorno = insercaoSub((x < (*p)->info) ? &((*p)->esq) : &((*p)->dir), x, cresceu);
    if (!retorno && *cresceu) {
        (*p)->fb += (x < (*p)->info) ? -1 : 1; // atualiza fator de balanceamento
        if ((*p)->fb == 0 || (*p)->fb == 2 || (*p)->fb == -2) {
            *cresceu = 0; // arvore parou de crescer: 0 => melhorou o balanceamento; 2 ou -2 => sera feito o rebalanceamento
            switch ((*p)->fb) {
                case 2: // arvore muito alta a direita
                    if ((*p)->dir->fb == 1) { // mesmo sinal
                        E(p); // rotacao simples a esquerda
                        // atualiza fatores de balanceamento
                        (*p)->fb = 0;
                        (*p)->esq->fb = 0;
                    } else { // sinais opostos
                        DE(p); // rotacao dupla direita-esquerda
                        atualizaFB(*p); // atualiza fatores de balanceamento
                    }
                    break;
                case -2: // arvore muito alta a esquerda
                    if ((*p)->esq->fb == -1) { // mesmo sinal
                        D(p); // rotacao simples a direita
                        // atualiza fatores de balanceamento
                        (*p)->fb = 0;
                        (*p)->dir->fb = 0;
                    } else { // sinais opostos
                        ED(p); // rotacao dupla esquerda-direita
                        atualizaFB(*p); // atualiza fatores de balanceamento
                    }
                    break;
            }
        }
    }
    return retorno;
}

int insercao(AVL *a, elem x) {
    int cresceu;
    return insercaoSub(&(a->raiz), x, &cresceu); // inicia recursao
}
