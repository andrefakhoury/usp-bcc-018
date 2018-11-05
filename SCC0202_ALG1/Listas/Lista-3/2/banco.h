#define TAM 50 /* num maximo de processos */

typedef struct {
    int codProcesso;
    int prox;
} Bloco;

typedef struct {
    int vazios;
    Bloco vet[TAM];
} Banco;

void format(Banco *b);
int isFullBanco(Banco *b);
int getnode(Banco *b);
void freenode(Banco *b, int pos);
int getcodProcesso(Banco *b, int pos);
int getProx(Banco *b, int pos);
void setInfo(Banco *b, int pos, int x);
void setProx(Banco *b, int pos, int prox);
