#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "list.h"

typedef struct node {
	var value;
	struct node* next;
} node;

struct list {
	node *begin, *end;
};

list* list_create() {
	list* l = (list*) malloc(sizeof(list));
	l->begin = l->end = NULL;
	return l;
}

int list_insert(list* l, var x) {
	node* p = (node*) malloc(sizeof(node));
	if (!p) return ERROR;

	p->value = x;
	p->next = NULL;

	if (l->begin)
		l->end->next = p;
	else
		l->begin = p;

	l->end = p;

	return 0;
}

void list_destroy(list* l) {
	if (l) {
		node* n;
		while (l->begin) {
			n = l->begin;
			l->begin = l->begin->next;
			free(n);
		}
		l->end = NULL;
		free(l);
	}
}

void list_print(list* l) {
	node* n = l->begin;
	while(n) {
		printf("%d ", n->value);
		n = n->next;
	} printf("\n");
}

int list_recSize(node* n) {
	return n ? 1 + list_recSize(n->next) : 0;

}

int list_size(list* l) {
	return list_recSize(l->begin);
	// int size = 0;
	// node* n = l->begin;
	// while(n) {
	// 	size++;
	// 	n = n->next;
	// }

	// return size;
}

int list_isEmpty(list* l) {
	return l->begin == NULL;
}

int list_recFind(node* n, var x) {
	return !n ? 0 : n->value == x ? 1 : list_recFind(n->next, x);
}

int list_find(list* l, var x) {
	return list_recFind(l->begin, x);
}

int list_recRemove(list* l, node* next, node* prev, var x) {
	if (!next) return ERROR;

	if (next->value == x) {
		if (next == l->begin) l->begin = l->begin->next;
		else prev->next = next->next;

		if (next == l->end) l->end = prev;
		free(next);
		return 0;
	}

	return list_recRemove(l, next->next, next, x);
}

int list_remove(list* l, var x) {
	return list_recRemove(l, l->begin, NULL, x);

	// node *next, *prev;
	// if (list_isEmpty(l))
	// 	return ERROR;

	// next = l->begin;
	// prev = NULL;

	// while(next) {
	// 	if (next->value == x) {
	// 		if (next == l->begin) l->begin = l->begin->next;
	// 		else prev->next = next->next;

	// 		if (next == l->end) l->end = prev;

	// 		free(next);
	// 		return 0;
	// 	}
	// 	prev = next;
	// 	next = next->next;
	// }
	// return ERROR;
}