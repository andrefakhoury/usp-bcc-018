#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "tab.h"

void nueva(lista* l) {
	tab* t = malloc(sizeof(tab));
	scanf(" %[^\n] %s %d %d %d %d", t->titulo, t->sitio, &(t->dia), &(t->mes), &(t->hora), &(t->min));
	nueva_tab(l, t);	
}

void actualiza(lista* l) {
	char titulo[32];
	int pos;
	
	scanf(" %[^\n] %d", titulo, &pos);

	actualiza_tab(l, titulo, pos);
}

int main() {
	lista* l = crea_lista();
	
	int op;
	
	while(scanf("%d", &op), op < 5) {
		switch(op) {
			case 1: nueva(l); 			
					break;
			case 2: actualiza(l);
					break;
			case 3: ordena_lista(l);
					break;
			case 4: muestra_lista(l);
					break;
			default: break;
		}
	}
	
	limpa_lista(l);
	return 0;
}