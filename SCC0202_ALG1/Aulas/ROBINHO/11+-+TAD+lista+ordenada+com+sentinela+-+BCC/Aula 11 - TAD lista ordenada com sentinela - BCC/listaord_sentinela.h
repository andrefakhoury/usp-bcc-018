typedef int elem;

typedef struct no {
    elem info;
    struct no *prox;
} No;

typedef struct {
    No *ini, *sentinela;
} ListaOrd;

int cria(ListaOrd *l);
void destroi(ListaOrd *l);
int insere(ListaOrd *l, elem x);
int remover(ListaOrd *l, elem x);
int busca(ListaOrd l, elem x);
void imprime(ListaOrd l);
int esta_vazia(ListaOrd l);