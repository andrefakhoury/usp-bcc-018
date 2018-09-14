#include <string.h>
#include "stdall.h"

#define MAX_PRICE 4000

typedef struct _pd {
	int id;
	char desc[256];
	double price;
} Product;

void printProducts(Product* v, int N) {
	printf("Products\n===============================\n");
	for (int i = 0; i < N; i++) {
		printf("%d\t%s\t%.2lf\n", v[i].id, v[i].desc, v[i].price);
	} printf("===============================\n");
}

int compareId(Product* a, Product* b) {
	return b->id - a->id;
}
int comparePrice(Product* a, Product* b) {
	return b->price >= a->price;
}
int compareDesc(Product* a, Product* b) {
	return strcmp(b->desc, a->desc);
}

void productSort(Product* v, int n, int(*compare)(Product*, Product*)) {
	int i = 1;
	while(i < n) {
		Product key = v[i];

		int j = i-1;
		while(j >= 0 && compare(&key, &v[j]) > 0) {
			v[j+1] = v[j];
			j--;
		}

		v[j+1] = key;
		i++;	
	}
}

int main() {
	int N = 6;
	Product v[N];

	for (int k = 0; k < N; k++) {
		v[k].id = rand()%1000+1;
		v[k].price = (rand()/(double)RAND_MAX)*MAX_PRICE;
	}

	printf("%d\n", (int)(-0.4));

	v[1].price = 10.9;
	v[2].price = 10.8;

	strcpy(v[0].desc, "Mouse Gamer");
	strcpy(v[1].desc, "PC Gamer");
	strcpy(v[2].desc, "Teclado Gamer");
	strcpy(v[3].desc, "MousePad Gamer");
	strcpy(v[4].desc, "Desktop Gamer");
	strcpy(v[5].desc, "Caneleira Gamer");

	productSort(v, N, comparePrice);
	printProducts(v, N);

}