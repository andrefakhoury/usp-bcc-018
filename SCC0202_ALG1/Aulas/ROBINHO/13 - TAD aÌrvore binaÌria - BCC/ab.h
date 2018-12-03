typedef char elem;

typedef struct no {
    elem info;
    struct no *esq, *dir;
} No;

typedef struct {
    No *raiz;
} AB;

void cria(AB *a);
void destroi(AB *a);
int vazia(AB a);
No *busca(AB a, elem x);
No *buscaPai(AB a, elem x);
int insereRaiz(AB *a, elem x);
int insereEsq(AB a, elem x, elem infoPai);
int insereDir(AB a, elem x, elem infoPai);
void imprime(AB a);
int altura(AB a);
void preOrdem(AB a);
void emOrdem(AB a);
void posOrdem(AB a);

