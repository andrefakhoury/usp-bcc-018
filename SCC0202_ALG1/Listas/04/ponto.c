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

float ponto_x(PONTO* p) {
	return p->x;
}

float ponto_y(PONTO* p) {
	return p->y;
}