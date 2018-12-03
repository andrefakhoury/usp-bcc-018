#define TAM 100

typedef int elem;

typedef struct {
    elem info;
    int prox;
} Bloco;

typedef struct {
    int ini, vazios;
    Bloco vet[TAM];
} Lista;

void cria(Lista *l);
int isEmpty(Lista *l);
int isFull(Lista *l);
int insere_comeco(Lista *l, elem x);
int retira_comeco(Lista *l, elem *x);
int insere_final(Lista *l, elem x);
