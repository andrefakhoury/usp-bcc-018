#include <stdio.h>
#include <stdlib.h>
#include "listaord.h"

int main(void) {
    ListaOrd l;
    elem x;
    int total;
    
    cria(&l);
    
    total = 0;
    while (total < 26) {
        x = (rand() % 26) + 'a'; // letra minuscula aleatoria
        if (!insere(&l, x))
            total++;
    }
    imprime(l);
    
    while(total) {
        x = (rand() % 26) + 'a'; // letra minuscula aleatoria
        if (!remover(&l, x)) {
            total--;
            imprime(l);
        }
    }
    
    return 0;
}
