#include "stack.h"
#include <stdlib.h>
#include <string.h>

typedef struct node {
	void* value;
	struct node* next;
} node;

struct stack {
	node* top;
	size_t elem_size;
};

stack* create_stack(size_t elem_size) {
	stack* s = (stack*) malloc(sizeof(stack));
	s->top = NULL;
	s->elem_size = elem_size;
	return s;
}

void destroy_stack(stack* s) {
	if (s != NULL) {
		node* n;
		while(s->top != NULL) {
			n = s->top;
			s->top = s->top->next;
			free(n->value);
			free(n);
		}
		s->top = NULL;
		free(s);
	}
}

void push_stack(stack* s, void* x) {
	node* n = (node*) malloc(sizeof(node));

	n->value = (void*) malloc(s->elem_size);
	memcpy(n->value, x, s->elem_size);
	n->next = s->top;
	s->top = n;
}

void pop_stack(stack* s) {
	node* aux = s->top->next;
	free(s->top->value);
	free(s->top);
	s->top = aux;
}

void* top_stack(stack* s) {
	return s->top == NULL ? NULL : s->top->value;
}

int stack_size(node* n) {
	if (n == NULL)
		return 0;
	return 1 + stack_size(n->next);
}

bool full_stack(stack* s, int p) {
	return stack_size(s->top) == p;
}

bool empty_stack(stack* s) {
	return s->top == NULL;
}