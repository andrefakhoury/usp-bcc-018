#include "queue.h"

/* Function that creates a queue. */
Queue* createQueue(void) {
	Queue* q = (Queue*) malloc(sizeof(Queue));
	q->begin = q->end = 0;
	return q;
} 

/* Auxiliary function that performs an increment in a given number.*/
int incr(int i) {
	return (i+1)%1000;
}

/* Function that pushes elements in the queue. */
void pushQueue(Queue* q, int x, int y) {
	if (incr(q->end) == q->begin) exit (1); // capacidade esgotada
	
	q->x[q->end] = x;
	q->y[q->end] = y;
	
	q->end = incr(q->end); 
}

/* Function that pops elements in the queue. */
void popQueue(Queue* q) {
	q->begin = incr(q->begin);
}

/* Function that checks if the queue is empty. */
int emptyQueue(Queue* q) {
	return (q->begin == q->end);
}

int frontQueue(Queue* q) {
	return q->x[q->begin];
}

/* Funtion that frees the allocated memory for the queue. */
void freeQueue(Queue* q) {
	free(q);
}
