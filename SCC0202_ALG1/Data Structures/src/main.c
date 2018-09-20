#include <stdio.h>
#include "list.h"
#include "stack.h"
#include "queue.h"

int main() {
	queue* q = NULL;
	q = queue_create();
	int v;

	queue_insert(q, 10);
	queue_print(q);
	
	queue_insert(q, 30);
	queue_print(q);

	queue_remove(q, &v);
	queue_print(q);

	printf("%d\n", queue_size(q));

	queue_destroy(q);
}