#include <stdio.h>
#include <stdlib.h>

#include "list.h"

struct node {
	var value;
	struct node* next;
};

void list_create(list* l) {
	l->front = l->back = NULL;
}

void list_include(list* l, var x) {
	node* p = (node*) malloc(sizeof(node));
	if (!p) return ERROR;
}