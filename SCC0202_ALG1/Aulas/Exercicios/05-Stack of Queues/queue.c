#include <string.h>


Queue queueCreate(types t) {
	Queue q;
	q.start = q.end = q.size = 0;
	q.t = t;
	return q;
}

void queueEmpty(Queue* q) {
	*q = queueCreate(q->t);
}

int queueIsFull(Queue q) {
	return q.size == qSize-1;
}

int queueIsEmpty(Queue q) {
	return !q.size;
}

int queueSize(Queue q) {
	return q.size;
}

int queuePush(Queue* q, type x) {
	if (queueIsFull(*q)) return 1;

	if (q->t == integer) q->vec[q->end].i = x.i;
	else if (q->t == real) q->vec[q->end].f = x.f;
	else if (q->t == string) strcpy(q->vec[q->end].s, x.s);
	
	q->size++;
	q->end = (q->end+1)%qSize;
}

int queuePop(Queue* q, type* x) {
	if (queueIsEmpty(*q)) return 1;

	switch(q->t) {
		case integer:	x->i = q->vec[q->start].i;
						break;
		case real:		x->f = q->vec[q->start].f;
						break;
		case string:	strcpy(x->s, q->vec[q->start].s);
						break;
	}

	q->size--;
	q->start = (q->start+1)%qSize;
}