#include <stdlib.h>

#include "ponto.h"

struct ponto_ {
	float x;
	float y;
};

PONTO* ponto_criar(float x, float y) {
	PONTO* p = malloc(sizeof(PONTO));
	p->x = x;
	p->y = y;
	return p;
}

void ponto_apagar(PONTO* p) {
	if (p != NULL)
		free(p);
}

//funcao que retorna o X do ponto
//foi criada para ser utilizada na distancia do circulo
float ponto_x(PONTO* p) {
	if (p == NULL)
		return 0;
	return p->x;
}

//funcao que retorna o Y do ponto
//foi criada para ser utilizada na distancia do circulo
float ponto_y(PONTO* p) {
	if (p == NULL)
		return 0;
	return p->y;
}

/*
 * Outra ideia que poderia ser utilizada é uma função "distancia_ponto" no arquivo ponto.c, que
 * calcula a distância entre dois pontos. E então, a função "distancia", declarada em circulo.c,
 * chamaria a funcao "distancia_ponto".
 */
