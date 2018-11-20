#include <stdio.h>
#include <stdlib.h>


int main() {
	int n = 10;
	int* vet = calloc(n, sizeof(int));
	for (int i = 0; i < n; i++) vet[i] = rand()%10;

	int gaps[] = {701, 301, 132, 57, 23, 10, 4, 1};
	
	for (int i = 0; i < 8; i++) {
		int gap = gaps[i];

		for (int j = gap; j < n; j++) {
			int temp = vet[j];
			int k;
			for (k = j; k >= gap && vet[k-gap] > temp; k -= gap)
				vet[k] = vet[k-gap];
			vet[k] = temp;
		}
	}

	for (int i = 0; i < n; i++) printf("%d ", vet[i]);
	printf("\n");


	return 0;
}
