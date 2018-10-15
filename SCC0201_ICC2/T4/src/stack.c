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

/* Cria uma stack vazia, com o tamanho de cada elemento mandado por parametro */
stack* create_stack(size_t elem_size) {
	stack* s = (stack*) malloc(sizeof(stack));
	s->top = NULL;
	s->elem_size = elem_size;
	return s;
}

/* Desaloca a stack e todos os seus elementos */
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

/* Insere um elemento na stack */
void push_stack(stack* s, void* x) {
	node* n = (node*) malloc(sizeof(node));

	n->value = (void*) malloc(s->elem_size);
	memcpy(n->value, x, s->elem_size);
	n->next = s->top;
	s->top = n;
}

/* Remove o elemento do topo da stack */
void pop_stack(stack* s) {
	node* aux = s->top->next;
	free(s->top->value);
	free(s->top);
	s->top = aux;
}

/* Retorna o elemento do topo da stack */
void* top_stack(stack* s) {
	return s->top == NULL ? NULL : s->top->value;
}

/* Retorna o tamanho da stack */
int stack_size(node* n) {
	if (n == NULL)
		return 0;
	return 1 + stack_size(n->next);
}

/* Retorna um boolean informando se a stack esta vazia */
bool empty_stack(stack* s) {
	return s->top == NULL;
}