#include <stdio.h>
#include "listagen.h"

int main(void) {
    ListaGen l1, l2, l3;
    
    cria(&l1);
    cria(&l2);
    cria(&l3);
    
    insereAtomo(&l1, 'a');
    insereAtomo(&l2, 'b');
    insereAtomo(&l3, 'c');
    insereLista(&l2, &l3);
    insereLista(&l1, &l2);
    insereAtomo(&l1, 'd');
    
    imprime(l1);
    
    if (busca(l1, 'c'))
        printf("c estah na lista\n");
    else
        printf("c NAO estah na lista\n");
    
    if (busca(l1, 'e'))
        printf("e estah na lista\n");
    else
        printf("e NAO estah na lista\n");
    
    printf("Profundidade de l1: %d\n", profundidade(l1));
    
/*** nao feito em aula; inserido atendendo a pedidos ***/
    ListaGen l4, l5, l6;
    
    cria(&l4);
    cria(&l5);
    cria(&l6);
    
    insereAtomo(&l4, 'w');
    
    insereAtomo(&l5, 'x');
    
    insereAtomo(&l6, 'y');
    
    insereLista(&l5, &l6);
    
    insereLista(&l4, &l5);
    
    insereAtomo(&l4, 'z');
    
    imprime(l4);
    
    if (iguais(l1, l4))
        printf("l1 e l4 sao iguais\n");
    else
        printf("l1 e l4 NAO sao iguais\n");
    
    if (iguaisEst(l1, l4))
        printf("l1 e l4 sao iguais estruturalmente\n");
    else
        printf("l1 e l4 NAO sao iguais estruturalmente\n");
    
    destroi(&l4);
    destroi(&l5);
    destroi(&l6);
/*******************************************************/
    
    destroi(&l1);
    destroi(&l2);
    destroi(&l3);
    
    return 0;
}
