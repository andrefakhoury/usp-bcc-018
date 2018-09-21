#include <stdio.h>

void torre(int n, char orig, char dest, char aux) {
	if (n == 1) {
		printf("%d: %c to %c\n", n, orig, dest);
		return;
	}

	torre(n-1, orig, aux, dest);
	printf("%d: %c to %c\n", n, orig, dest);
	torre(n-1, aux, dest, orig);
}

void hanoi(int n, char orig, char inter, char dest, int* k) {
	if (n == 1) { printf("%d: %c to %c\n", *k, orig, dest); return; }
	
	hanoi(n-1, orig, dest, inter, k);
	hanoi(1, orig, inter, dest, k);
	hanoi(n-1, inter, orig, dest, k);
}

int main() {
	int n, cont = 0; scanf("%d", &n);
	hanoi(n, 'A', 'B', 'C', &cont);
	printf("\n>>%d\n", cont);
	return 0;
}