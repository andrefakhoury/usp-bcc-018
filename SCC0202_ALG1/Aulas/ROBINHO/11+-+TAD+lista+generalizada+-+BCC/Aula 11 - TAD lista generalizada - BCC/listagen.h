typedef char elem;

typedef enum {
    atomo, lista
} Tipo;

typedef struct no {
    void *info;
    Tipo tipo;
    struct no *prox;
} No;

typedef struct {
    No *ini;
} ListaGen;

void cria(ListaGen *l);
void destroi(ListaGen *l);
int insereAtomo(ListaGen *l, elem x);
int insereLista(ListaGen *l, ListaGen *x);
void imprime(ListaGen l);
int busca(ListaGen l, elem x);
int profundidade(ListaGen l);

/*** nao feito em aula; inserido atendendo a pedidos ***/
int iguais(ListaGen l1, ListaGen l2);
int iguaisEst(ListaGen l1, ListaGen l2);
/*******************************************************/



