#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

int main(int argc, char *argv[]) {
    
    if (argc > 2) {
        printf("Uso inválido! Tente \"exec\" ou \"exec x\", em que x é o valor inicial\n");
        return 1;
    }
    
    Banco b;
    Pilha p1, p2;
    elem x;
    
    format(&b);
    cria(&p1, &b);
    cria(&p2, &b);

    if (argc == 2)
        x = atoi(argv[1]);
    else
        x = 1;
    while (!isFull(&p1)) {
        push(&p1, x);
        push(&p2, -1*x);
        x++;
    }
    
    while (!pop(&p1, &x))
        printf("%d\n", x);
    
    while (!pop(&p2, &x))
        printf("%d\n", x);
    
    return 0;
}
