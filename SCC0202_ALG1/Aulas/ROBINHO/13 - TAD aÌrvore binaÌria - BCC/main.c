#include <stdio.h>
#include "ab.h"

int main(void) {
    AB a;
    
    cria(&a);
    
    insereRaiz(&a, 'D');
    insereEsq(a, 'B', 'D');
    insereDir(a, 'F', 'D');
    insereEsq(a, 'A', 'B');
    insereDir(a, 'C', 'B');
    insereDir(a, 'G', 'F');
    insereDir(a, 'H', 'G');
    
    printf("Pai de D: %p\n", buscaPai(a, 'D'));
    printf("Pai de B: %c\n", (buscaPai(a, 'B'))->info);
    printf("Pai de F: %c\n", (buscaPai(a, 'F'))->info);
    printf("Pai de A: %c\n", (buscaPai(a, 'A'))->info);
    printf("Pai de C: %c\n", (buscaPai(a, 'C'))->info);
    printf("Pai de G: %c\n", (buscaPai(a, 'G'))->info);
    
    imprime(a);
    
    printf("Altura: %d\n", altura(a));
    
    printf("Pre-ordem: ");
    preOrdem(a);
    
    printf("Em-ordem: ");
    emOrdem(a);
    
    printf("Pos-ordem: ");
    posOrdem(a);
    
    destroi(&a);
    
    return 0;
}
