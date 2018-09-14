#include <stdio.h>
#include "list.h"

int main() {
	list* l = list_create();
	list_insert(l, 20);
	list_insert(l, 60);
	list_print(l);
	list_destroy(l);

	return 0;
}