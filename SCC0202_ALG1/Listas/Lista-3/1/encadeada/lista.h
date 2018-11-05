
typedef struct produto_ {
	char nome[100];
	float preco;
	int quantidade;
} Produto;

typedef struct no {
	Produto valor;
	struct no* prox;
} No;

typedef struct {
	no *ini, *fim;
} Lista;

void criaLista(Lista*);
void destroiLista(Lista*);
void insereLista