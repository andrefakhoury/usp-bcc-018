#include <stdio.h>
#include "agenda.h"

void imprimeTudo(Agenda a) {
	for (int i = 0; i < 200; i++)
		printf("%d: %s %s\n", i, a.pessoa[i].nome, a.pessoa[i].endereco);
}

int main( ){
	Agenda a;
	insere(&a, "Jorginho", "Rua rua");
	insere(&a, "Fakhoury", "Rua 2");
	printf("%s\n", buscaEndereco(a, "Jorginho"));
	tiraDaAgenda(&a, "Fakhoury");
	imprimeTudo(a);
	return 0;
}