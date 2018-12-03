#define TAM 20000
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "listaord_sentinela.h"

int main(void) {
    ListaOrd l;
    elem x;
    int total;
    clock_t clock_inicio, clock_insere, clock_busca, clock_remove;
    
    clock_inicio = clock();
    
    cria(&l);
    
    clock_insere = clock();
    total = 0;
    while (total < TAM) {
        x = rand() % TAM;
        if (!insere(&l, x))
            total++;
    }
    printf("Tempo insercao: %f segundos.\n", ((float) clock()-clock_insere)/CLOCKS_PER_SEC);
    
    //imprime(l);
    
    clock_busca = clock();
    for (total=0; total < TAM; total++) {
        x = rand() % (2*TAM);
        busca(l, x);
    }
    printf("Tempo busca: %f segundos.\n", ((float) clock()-clock_busca)/CLOCKS_PER_SEC);
    
    clock_remove = clock();
    total = TAM;
    while(total) {
        x = rand() % (2*TAM);
        if (!remover(&l, x)) {
            total--;
            //imprime(l);
        }
    }
    printf("Tempo remove: %f segundos.\n", ((float) clock()-clock_remove)/CLOCKS_PER_SEC);
    
    destroi(&l);
    
    printf("Tempo total: %f segundos.\n", ((float) clock()-clock_inicio)/CLOCKS_PER_SEC);
    
    return 0;
}
