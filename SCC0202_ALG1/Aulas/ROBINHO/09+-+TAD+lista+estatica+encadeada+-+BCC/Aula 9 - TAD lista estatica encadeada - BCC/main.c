#include <stdio.h>
#include "lista_est_enc.h"

int main(void) {
    Lista l;
    elem x;
    
    cria(&l);

    printf("Digite um elemento (0 para sair): ");
    scanf("%d", &x);
    while(x != 0) {
        if (x % 2)
            insere_final(&l,x); // impar, insere no final
        else
            insere_comeco(&l,x); // par, insere no inicio
        printf("Digite outro elemento (0 para sair): ");
        scanf("%d", &x);
    }
    
    while (!retira_comeco(&l,&x))
        printf("%d\n", x);
    
    return 0;
}
