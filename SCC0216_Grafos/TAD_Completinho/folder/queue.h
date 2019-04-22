#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct queue {
	int begin, end; 
	int x[1000], y[1000];
} Queue;

/* Function that creates a queue. */
Queue* createQueue();

/* Function that pushes elements in the queue. */
void pushQueue (Queue* q, int x, int y);

/* Function that pops elements in the queue. */
void popQueue (Queue* q);

/* Function that checks if the queue is empty. */
int emptyQueue (Queue* q);

int frontQueue(Queue* q); 

/* Funtion that frees the allocated memory for the queue. */
void freeQueue (Queue* q);

#endif
