#include <math.h>
#include <stdlib.h>
#include "circulo.h"
#define PI 3.14159

struct circulo_ {
	PONTO* ponto_c;
	float raio;
};

CIRCULO* circulo_criar(float x, float y, float raio) {
	CIRCULO* c = malloc(sizeof(CIRCULO));
	c->ponto_c = ponto_criar(x, y);
	c->raio = raio;
	return c;
}

void circulo_apagar(CIRCULO* circulo) {
	if (circulo != NULL) {
		ponto_apagar(circulo->ponto_c);
		free(circulo);
	}
}

float circulo_area(CIRCULO* circulo) {
	return PI * circulo->raio * circulo->raio;
}

float distancia(PONTO* p, CIRCULO* r) {
	float x1 = ponto_x(p);
	float y1 = ponto_y(p);
	float x2 = ponto_x(r->ponto_c);
	float y2 = ponto_y(r->ponto_c);
	return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}