#include <stdio.h>
#include <stdlib.h>
#include "matrizE.h"

int cria(MatrizE *m, int nlinhas, int ncolunas) {
    m->vlinhas = calloc(nlinhas, sizeof(No *));
    if (m->vlinhas == NULL)
        return 1; // erro, memoria insuficiente
    
    m->vcolunas = calloc(ncolunas, sizeof(No *));
    if (m->vcolunas == NULL) {
        free(m->vlinhas);
        return 1; // erro, memoria insuficiente
    }
    
    m->nlinhas = nlinhas;
    m->ncolunas = ncolunas;
    
    return 0;
}

void destroi(MatrizE *m) {
    No *aux;
    for (int l=0; l < m->nlinhas; l++) {
        // varre uma linha, apagando cada no
        while (m->vlinhas[l] != NULL) {
            aux = m->vlinhas[l];
            m->vlinhas[l] = m->vlinhas[l]->proximacol;
            free(aux);
        }
    }
    free(m->vlinhas); // apaga vetor de linhas
    free(m->vcolunas); // apaga vetor de colunas
    return;
}

void busca_interna(No *no, int valorOrd, No **ant, No **p, int ehLinha) {
    // ant, p => No **
    // *ant, *p => No *
    // **ant, **p => No
    *ant = NULL;
    *p = no;
    while (*p != NULL &&
           ( ( ehLinha && (*p)->col < valorOrd) ||
             (!ehLinha && (*p)->lin < valorOrd) )  ) {
        *ant = *p;
        *p = (ehLinha) ? (*p)->proximacol : (*p)->proximalin;
    }
    return;
}

int insere(MatrizE m, int lin, int col, elem x) {
    No *novo, *ant, *p;
    
    if (lin > m.nlinhas || col > m.ncolunas)
        return 1; // erro, linha ou coluna invalida
    
    novo = malloc(sizeof(No));
    if (novo == NULL)
        return 1; // erro, mem insuficiente
    
    // busca na linha
    busca_interna(m.vlinhas[lin-1], col, &ant, &p, 1);
    if (p != NULL && p->col == col) {
        free(novo);
        return 1;
    }
    
    // copia valor, linha e coluna
    novo->info = x;
    novo->lin = lin;
    novo->col = col;
    
    // insere na lista da linha
    novo->proximacol = p;
    if (ant == NULL)
        m.vlinhas[lin-1] = novo; // insere no inicio
    else
        ant->proximacol = novo; // insere no meio ou fim
    
    // insere na lista da coluna
    busca_interna(m.vcolunas[col-1], lin, &ant, &p, 0);
    novo->proximalin = p;
    if (ant == NULL)
        m.vcolunas[col-1] = novo; // insere no inicio
    else
        ant->proximalin = novo; // insere no meio ou fim
    
    //printf("inseriu %d\n", novo->info);
    
    return 0;
}

int remover(MatrizE m, int lin, int col) {
    No *ant, *p;
    if (lin > m.nlinhas || col > m.ncolunas)
        return 1; // linha ou coluna invalida
    
    busca_interna(m.vlinhas[lin-1], col, &ant, &p, 1);
    if (p == NULL || p->col != col)
        return 1; // erro, caixa nao existe
    
    // retira p da lista da linha
    if (ant == NULL)
        m.vlinhas[lin-1] = p->proximacol;
    else
        ant->proximacol = p->proximacol;
    
    // retira da lista da coluna
    busca_interna(m.vcolunas[col-1], lin, &ant, &p, 0);
    if (ant == NULL)
        m.vcolunas[col-1] = p->proximalin;
    else
        ant->proximalin = p->proximalin;

    //printf("removeu %d\n", p->info);
    
    free(p); // apaga caixa
    
    return 0; // sucesso
}

void imprime(MatrizE m) {
    No *aux;
    int col;
    for (int l = 0; l < m.nlinhas; l++) {
        col = 1;
        aux = m.vlinhas[l];
        while (aux != NULL) {
            for (;col < aux->col; col++)
                printf("0 ");
            printf("%d ", aux->info);
            col++;
            aux = aux->proximacol;
        }
        for (;col <= m.ncolunas; col++)
            printf("0 ");
        printf("\n");
    }
    return;
}

int somaLinha(MatrizE m, int lin, elem x) {
    int col = 1;
    No *aux;
    
    if (lin > m.nlinhas)
        return 1; // erro, linha invalida
    
    if (x == 0)
        return 0; // sucesso, soma zero

    aux = m.vlinhas[lin-1];
    while (aux != NULL) {
        // processa colunas entre col e aux->col
        for (; col < aux->col; col++)
            insere(m, lin, col, x); // insere nova caixa
        // processa coluna aux->col
        aux->info += x;
        if (aux->info == 0) {
            aux = aux->proximacol;
            remover(m, lin, col);
        } else
            aux = aux->proximacol;
        col++;
    }
    // processa colunas entre col e o numero total de colunas
    for (; col <= m.ncolunas; col++)
        insere(m, lin, col, x); // insere nova caixa
    
    return 0; // sucesso
}
