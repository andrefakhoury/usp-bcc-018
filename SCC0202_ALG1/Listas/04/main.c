#include <stdio.h>
#include "ponto.h"
#include "circulo.h"

int main() {
	PONTO* p;
	CIRCULO* c;
	float pX, pY;
	float cX, cY, cRaio;

	printf("Digite x e y do ponto: ");
	scanf("%f%f", &pX, &pY);
	p = ponto_criar(pX, pY);

	printf("Digite x, y e raio do circulo: ");
	scanf("%f%f%f", &cX, &cY, &cRaio);
	c = circulo_criar(cX, cY, cRaio);

	if (distancia(p, c) < cRaio) {
		printf("Ponto interno.\n");
	} else {
		printf("Ponto nao interno.\n");
	}

	ponto_apagar(p);
	circulo_apagar(c);
	return 0;
}