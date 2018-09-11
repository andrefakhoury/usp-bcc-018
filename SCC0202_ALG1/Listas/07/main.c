#include <stdio.h>
#include "pilha.h"

int main(int argc, char* argv[]){
    char v[TamPilha];
    printf("Digite a string: ");
    scanf("%s", v);
    
    Pilha p;
    cria_pilha(&p);
    char x;
    
    int i = 0;
    while(v[i] != '\0') {
		if (v[i] == 'a')
			push(&p, v[i]);
		else {
			int erro = pop(&p, &x);
			if (erro) {
				printf("Não é do formato.\n");
				return 0;
			}
		}
		i++;
	}
	
	if (isEmpty(p)) {
		printf("É do formato.\n");
	} else {
		printf("Não é do formato.\n");
	}
    
    return 0;
}
