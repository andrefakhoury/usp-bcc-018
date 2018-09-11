#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"

int main(int argc, char* argv[]){
    char exp[TamPilha];
    elem x, y;
    Pilha p;
    int i;
    
    printf("Digite a expressao: ");
    scanf("%s", exp);
    
    cria_pilha(&p);
    
    i = strlen(exp);
    
    while (--i >= 0) {
        if (exp[i] != '/' && exp[i] != '*' &&
            exp[i] != '+' && exp[i] != '-')
            push(&p, (float) exp[i]-'0');
        else {
            pop(&p, &y);
            pop(&p, &x);
            switch (exp[i]) {
                case '+':
                    push(&p,x+y);
                    break;
                case '-':
                    push(&p,x-y);
                    break;
                case '*':
                    push(&p,x*y);
                    break;
                case '/':
                    push(&p,x/y);
                    break;
            }
        }
    }
    
    pop(&p, &x);
    printf("Resultado: %d\n", x);
    
    return 0;
}
