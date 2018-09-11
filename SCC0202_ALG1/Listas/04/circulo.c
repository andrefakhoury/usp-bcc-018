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

//Funcao que calcula a distancia de um Ponto p a um Circulo r
/* Foi declarada em circulo.c pois o circulo ja utiliza o tipo Ponto em sua implementacao.
 * A unica mudanca necessaria foi adicionar funcoes no ponto que retornam o X e Y, pois fora
 * de ponto.c nao é permitido o acesso desses dados. */
float distancia(PONTO* p, CIRCULO* r) {
	if (p == NULL || r == NULL)
		return -1;
	
	float x1 = ponto_x(p);
	float y1 = ponto_y(p);
	float x2 = ponto_x(r->ponto_c);
	float y2 = ponto_y(r->ponto_c);
	return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}
