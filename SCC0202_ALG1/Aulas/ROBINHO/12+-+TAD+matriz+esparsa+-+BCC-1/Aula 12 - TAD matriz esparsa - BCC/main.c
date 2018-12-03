#include <stdio.h>
#include "matrizE.h"

int main(void) {
    MatrizE m;
    
    cria(&m, 3, 5);
    
    insere(m, 1, 1, 3);
    insere(m, 1, 3, 2);
    insere(m, 2, 1, -1);
    insere(m, 3, 3, 5);
    insere(m, 1, 5, 9);
    insere(m, 3, 4, 7);
    imprime(m);
    
    printf("Remove (1,1)\n");
    remover(m, 1, 1);
    imprime(m);
    
    printf("Remove (3,3)\n");
    remover(m, 3, 3);
    imprime(m);
    
    printf("Remove (2,1)\n");
    remover(m, 2, 1);
    imprime(m);
    
    printf("Remove (1,5)\n");
    remover(m, 1, 5);
    imprime(m);
    
    printf("Remove (3,4)\n");
    remover(m, 3, 4);
    imprime(m);
    
    printf("Remove (1,3)\n");
    remover(m, 1, 3);
    imprime(m);
    
    printf("Monta novamente\n");
    insere(m, 1, 1, 3);
    insere(m, 1, 3, 2);
    insere(m, 2, 1, -1);
    insere(m, 3, 3, 5);
    insere(m, 1, 5, 9);
    insere(m, 3, 4, 7);
    imprime(m);
    
    printf("Soma -9 a linha 1\n");
    somaLinha(m, 1, -9);
    imprime(m);
    
    printf("Soma 1 a linha 2\n");
    somaLinha(m, 2, 1);
    imprime(m);
    
    printf("Soma -7 a linha 3\n");
    somaLinha(m, 3, -7);
    imprime(m);
    
    destroi(&m);
    
    return 0;
}
