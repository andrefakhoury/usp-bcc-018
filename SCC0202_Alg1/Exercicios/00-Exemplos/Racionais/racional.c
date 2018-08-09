#include <stdlib.h>
#include "racional.h"

struct racional {
	int num, den;
};

Racional* le(int numerador, int denominador) {
	if (denominador == 0) return NULL;

	Racional* rac = (Racional*) malloc(sizeof(Racional));
	if (rac != NULL) {
		rac->num = numerador;
		rac->den = denominador;
	}
	return rac;
}

void apagar(Racional* rac) {
	if (rac != NULL) free(rac);
}

float mediaRacionais(Racional** vracs, int tamanho, char* erro) {
	if (tamanho < 1) return *erro = 1;
	*erro = 0;
	float soma = 0;
	for (int i = 0; i < tamanho; i++) {
		soma += vracs[i]->num/(float)vracs[i]->den;
	} return soma/tamanho;
}

float converteReal(Racional* rac) {
	return (float)rac->num/rac->den;
}