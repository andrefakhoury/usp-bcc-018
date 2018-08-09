#include <stdio.h>
#include "racional.h"

int main() {
	Racional *rac, *vracs[3];
	rac = le(3, 2);
	printf("%.2f\n", converteReal(rac));
	vracs[0] = le(5, 1);
	vracs[1] = le(6, 1);
	vracs[2] = le(4, 1);

	char erro;
	printf("%.2f\n", mediaRacionais(vracs, 3, &erro));
	return 0;
}