#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct p {
	float a, b, c;
} Polinomio;

typedef struct f {
	float x, y;
} Funcao;

void lePolinomio(Polinomio* pol) {
	scanf("%f %f %f", &(*pol).a, &(*pol).b, &(*pol).c);
	printf("f(x) = %.2f x^2 + %.2f x + %.2f\n", pol->a, pol->b, pol->c);
}

int leIntervalo(Polinomio p, Funcao** f) {
	float ini, fin; scanf("%f %f", &ini, &fin);
	int size = (fin-ini + 0.5) * 2;
	(*f) = malloc(size * sizeof(Funcao));
	int v = 0;
	for (float i = ini; i <= fin; i += 0.5, v++) {
		(*f)[v].x = i;
		(*f)[v].y = p.a*(i*i) + p.b*i + p.c;
	}
	
	return size;
}

void imprimeValores(Funcao* f, int sz) {
	for (int i = 0; i < sz; i++) {
		printf("f(%.2f) = %.2f\n", f[i].x, f[i].y);
	}
}

void testaValores(Polinomio p) {
	float x, y; scanf("%f %f", &x, &y);
	float res = p.a * x*x + p.b * x + p.c;
	if (res == y) {
		printf("Ponto (%.2f, %.2f) pertence ao grafico da funcao\n", x, y);
		return;
	}
	
	double distT = 0x3f3f3f3f, distA;
	float mX, mY;
	
	for (float i = x; i <= x+10; i+=0.5) {
		res = p.a*(i*i) + p.b*(i) + p.c;
		distA = (float)sqrt((x-i)*(x-i) + (y-res)*(y-res));
		if (distA < distT) {
			distT = distA;
			mX = i;
			mY = res;
		}
	}
	
	for (float i = x; i >= x-10; i-=0.5) {
		res = p.a * i*i + p.b * i + p.c;
		distA = (float)sqrt((x-i)*(x-i) + (y-res)*(y-res));
		if (distA < distT) {
			distT = distA;
			mX = i;
			mY = res;
		}
	}
	
	printf("Ponto (%.2f, %.2f) nao pertence ao grafico da funcao\n", x, y);
	printf("Ponto mais proximo = (%.2f, %.2f)\n", mX, mY);
	
}

int main() {
	int op, sz;
	Polinomio pol;
	Funcao* f;
	
	while (scanf("%d", &op), op) {
		switch(op) {
			case 1: lePolinomio(&pol);
					break;
			case 2: sz = leIntervalo(pol, &f);
					break;
			case 3: imprimeValores(f, sz);
					break;
			case 4: testaValores(pol);
					break;
		}
	}
	
	free(f);
}
