#include "stack.h"

stack create_stack(Bank *b) {
    stack s;
    s.top = -1; 
    s.bank = b; 
    return s;
}

int push_stack(stack *s, elem* x) {
    int aux = get_node(s->bank);
    if (aux == -1) return 1;

    set_info(s->bank, aux, x);
    set_next(s->bank, aux, s->top);
    
    s->top = aux;
    return 0;
}

int pop_stack(stack *s, elem* x) {
    if (isEmpty_stack(s)) return 1;
    int aux = s->top;
    
    strcpy(x, get_info(s->bank, s->top));
    s->top = get_next(s->bank, s->top);
    
    free_bank(s->bank, aux);
    return 0;
}

int isEmpty_stack(stack *s) {
    return s->top == -1;
}