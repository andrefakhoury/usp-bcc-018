#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "list.h"

struct node {
	var value;
	struct node* next;
};

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
	}
}

void list_print(list* l) {
	node* n = l->begin;
	while(n) {
		printf("%d\n", n->value);
		n = n->next;
	}
}