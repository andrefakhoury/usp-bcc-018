#define TAM 10 // aumentar e ver tempo, removendo impressao
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "avl.h"

int main(void) {
    AVL a;
    elem x;
    int total, sucesso;
    clock_t c_inicial, c_insercao, c_busca, c_remocao;
    
    c_inicial = clock();
    
    cria(&a);
    
    c_insercao = clock();
    for (x = 0; x < TAM; x++) { // insere em ordem; pior caso
        insercao(&a, x);
        emOrdem(a);
    }
    printf("Insercao: %0.3lf segundos.\n",(double)(clock()-c_insercao)/CLOCKS_PER_SEC);
    
    printf("Altura após inserir %d elementos: %d\n", TAM, altura(a));
    printf("Arvore resultante: ");
    imprime(a);
    
    c_busca = clock();
    for (total = 0; total < TAM; total++) {
        x = rand() % (2*TAM);
        sucesso = busca(a, x);
        printf("Buscando %d: %s\n", x, (sucesso) ? "encontrado" : "nao encontrado");
    }
    printf("Busca: %0.3lf segundos.\n",(double)(clock()-c_busca)/CLOCKS_PER_SEC);
    
    //c_remocao = clock();
    //for (x = TAM-1; x >= 0; x--) { // remove em ordem decrescente; pior caso
    //    remover(&a, x);
    //    emOrdem(a);
    //    if (x == TAM/2) {
    //        printf("Altura após remover %d elementos: %d\n", TAM-x, altura(a));
    //        printf("Arvore resultante: ");
    //        imprime(a);
    //    }
    //}
    //printf("Remocao: %0.3lf segundos.\n",(double)(clock()-c_remocao)/CLOCKS_PER_SEC);
    
    destroi(&a);
    
    printf("Total: %0.3lf segundos.\n",(double)(clock()-c_inicial)/CLOCKS_PER_SEC);
    
    return 0;
}
