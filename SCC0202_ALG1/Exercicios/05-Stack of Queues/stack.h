#include "queue.h"

typedef Queue stackType;
typedef struct stack Stack;
//Pra fazer estatico, so colocar a definicao da struct aqui no .h

Stack* stackCreate();
int stackPush(Stack* P, stackType X);
int stackPop(Stack* P, stackType* X);
stackType stackTop(Stack* P);
int stackIsEmpty(Stack* P);
void stackEmpty(Stack* P);
int stackSize(Stack* P);