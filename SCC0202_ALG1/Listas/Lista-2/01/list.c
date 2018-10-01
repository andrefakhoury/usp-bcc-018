#include <stdlib.h>

#include "list.h"

#define ERROR 1

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
	//return list_recRemove(l, l->begin, NULL, x);

	node *next, *prev;
	if (list_isEmpty(l))
		return ERROR;

	next = l->begin;
	prev = NULL;

	while(next) {
		if (next->value == x) {
			if (next == l->begin) l->begin = l->begin->next;
			else prev->next = next->next;

			if (next == l->end) l->end = prev;

			free(next);
			return 0;
		}
		prev = next;
		next = next->next;
	}
	return ERROR;
}

var list_vbegin(list* l) {
	return l->begin->value;
}

int list_remove_k(list* l, int k) {
	if (!l->begin) return ERROR;

	node* toDel = l->end;
	while(list_size(l) > 1) {
		for (int i = 0; i < k; i++) {
			if (toDel->next) toDel = toDel->next;
			else if (l->begin) toDel = l->begin;
			else return 0;
		}

		list_remove(l, toDel->value);
	}
	return 0;
}