#include <stdio.h>
#include "stack.h"

int main(void) {
    elem x[16];

    //inicializa as variaveis
    Bank b = create_bank();
    stack s = create_stack(&b);

    //insere os processos
    push_stack(&s, "001ABC");
    push_stack(&s, "002DEF");
    push_stack(&s, "003GHI");
    
    //retira os processos e imprime
    pop_stack(&s, x);
    printf("%s\n", x);
    pop_stack(&s, x);
    printf("%s\n", x);
    pop_stack(&s, x);
    printf("%s\n", x);

    return 0;
}
