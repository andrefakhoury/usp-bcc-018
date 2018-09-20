#include <stdio.h>
#include "list.h"

int main() {
	list l;
	list_create(&l);

	list_include(&list, 2);
}