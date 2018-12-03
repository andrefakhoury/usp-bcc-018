typedef int elem;

typedef struct no {
    elem info;
    struct no *esq, *dir;
    int fb;
} No;

typedef struct {
    No *raiz;
} AVL;

void cria(AVL *a);
void destroi(AVL *a);
int vazia(AVL a);
void imprime(AVL a);
int altura(AVL a);
void preOrdem(AVL a);
void emOrdem(AVL a);
void posOrdem(AVL a);
int busca(AVL a, elem x);
int insercao(AVL *a, elem x);
