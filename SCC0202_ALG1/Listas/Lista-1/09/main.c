#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"

int main(int argc, char* argv[]){
    char str[TamPilha], x;
    Pilha p;
    int ind = 0;
    
    printf("Digite um texto: ");
    while(scanf("%c", &str[ind]), str[ind++] != '\n');

    cria_pilha(&p);
    
    for (int i = 0; str[i] != '\n' && str[i] != '\0'; i++) {
		if (str[i] != ' ')
			push(&p, str[i]);
		else {
			while(!pop(&p, &x))
				printf("%c", x);
			printf(" ");
		}
	}
	
	while(!pop(&p, &x))
		printf("%c", x);
		
	printf("\n");
    return 0;
}
