#include <stdio.h>
#include "queue.h"

int main() {
	types t = integer;
	type x; x.i = 0;
	Queue q = queueCreate(t);
	while(!queuePush(&q, x)) {++x.i;}
	printf("Size: %d\n", queueSize(q));
	while(!queuePop(&q, &x)) printf("%d\n", x.i);
}