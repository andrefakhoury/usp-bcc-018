#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "queue.h"

typedef struct node {
	var value;
	struct node* next;
} node;

struct queue {
	node *begin, *end;
};

queue* queue_create() {
	queue* q = (queue*) malloc(sizeof(queue));
	q->begin = q->end = NULL;
	return q;
}

int queue_insert(queue* q, var x) {
	node* n = (node*) malloc(sizeof(node));
	if (!n) return ERROR;

	n->value = x;

	if (!q->begin)
		q->begin = n;
	else
		q->end->next = n;
	
	q->end = n;

	return 0;
}

void queue_destroy(queue* q) {
	if (q) {
		node* n;
		while (q->begin) {
			n = q->begin;
			q->begin = q->begin->next;
			free(n);
		}
		q->end = NULL;
	}
	free(q);
}

void queue_print(queue* q) {
	node* n = q->begin;
	while(n) {
		printf("%d ", n->value);
		n = n->next;
	} printf("\n");
}

int queue_recSize(node* n) {
	return n ? 1 + queue_recSize(n->next) : 0;
}

int queue_size(queue* q) {
	return queue_recSize(q->begin);
	// int size = 0;
	// node* n = q->begin;
	// while(n) {
	// 	size++;
	// 	n = n->next;
	// }

	// return size;
}

int queue_isEmpty(queue* q) {
	return q->begin == NULL;
}

int queue_isFull(queue* q) {
	node* n = (node*) malloc(sizeof(node));
	if (n) {
		free(n);
		return 0;
	}
	return 1;
}

int queue_remove(queue* q, var* v) {
	if (queue_isEmpty(q))
		return ERROR;

	*v = q->begin->value;

	node* next = q->begin->next;
	free(q->begin);
	q->begin = next;
	return 0;
}