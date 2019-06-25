#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "stack.h"

typedef struct node {
	var value;
	struct node* prev;
} node;

struct stack {
	node *top;
};

stack* stack_create() {
	stack* s = (stack*) malloc(sizeof(stack));
	s->top = NULL;
	return s;
}

int stack_insert(stack* s, var x) {
	node* n = (node*) malloc(sizeof(node));
	if (!n) return ERROR;

	n->value = x;
	n->prev = s->top;
	s->top = n;

	return 0;
}

int stack_remove(stack* s, var* v) {
	if (stack_isEmpty(s)) return ERROR;

	*v = s->top->value;
	node* prev = s->top->prev;
	
	free(s->top);
	s->top = prev;
	return 0;
}

void stack_destroy(stack* s) {
	if (s) {
		node* n;
		while (s->top) {
			n = s->top;
			s->top = s->top->prev;
			free(n);
		}
		s->top = NULL;
		free(s);
	}
}

void stack_print(stack* s) {
	node* n = s->top;
	while(n) {
		printf("%d ", n->value);
		n = n->prev;
	} printf("\n");
}

int stack_recSize(node* n) {
	return n ? 1 + stack_recSize(n->prev) : 0;

}

int stack_size(stack* s) {
	return stack_recSize(s->top);
	// int size = 0;
	// node* n = s->top;
	// while(n) {
	// 	size++;
	// 	n = n->prev;
	// }

	// return size;
}

int stack_isEmpty(stack* s) {
	return s->top == NULL;
}


var stack_top(stack* s) {
	if (stack_isEmpty(s))
		return ERROR;
	return s->top->value;
}
