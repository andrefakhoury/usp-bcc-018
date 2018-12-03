typedef int elem;

typedef struct no {
    int lin, col;
    elem info;
    struct no *proximalin, *proximacol;
} No;

typedef struct {
    No **vlinhas, **vcolunas;
    int nlinhas, ncolunas;
} MatrizE;

int cria(MatrizE *m, int nlinhas, int ncolunas);
void destroi(MatrizE *m);
int insere(MatrizE m, int lin, int col, elem x);
int remover(MatrizE m, int lin, int col);
void imprime(MatrizE m);
int somaLinha(MatrizE m, int lin, elem x);

