#include <stdio.h>
#include "list.h"

int main() {
	int n, k;
	scanf("%d%d", &n, &k);

	list* l = list_create();
	for (int i = 1; i <= n; i++)
		list_insert(l, i);

	list_remove_k(l, k);

	printf("%d\n", list_vbegin(l));

	list_destroy(l);
	return 0;
}