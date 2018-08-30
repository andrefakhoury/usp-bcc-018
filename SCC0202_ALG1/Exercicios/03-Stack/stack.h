typedef int elem;
typedef struct stack Stack;
//Pra fazer estatico, so colocar a definicao da struct aqui no .h

Stack* stackCreate();
int stackPush(Stack* P, type X);
int stackPop(Stack* P, type* X);
type stackTop(Stack* P);
int stackIsEmpty(Stack* P);
void stackEmpty(Stack* P);
int stackSize(Stack* P);
int stackCompare(Stack* P, Stack* Q);