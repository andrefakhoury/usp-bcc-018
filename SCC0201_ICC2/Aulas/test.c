#include <stdio.h>
int main() {
	int soma = 0, n = 5;
	for (int i = 1; i <= n; i++) soma+=i;
	printf("%d : %d\n", n*(n+1)/2, soma);
}
