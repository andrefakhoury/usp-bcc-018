#include <stdio.h>
#include "list.h"

int main() {
	list l;
	create(&l);

	include(&l, 10, 1);
	imprime(l);

	include(&l, 20, 2);
	imprime(l);
	
	include(&l, 30, 54);
	imprime(l);

	apaga(&l);
	return 0;
}