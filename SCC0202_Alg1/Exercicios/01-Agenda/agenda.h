typedef struct Pessoa Pessoa;
typedef struct Agenda Agenda;
int estaNaAgenda(Agenda a, char nome[50]);
void insere(Agenda* a, char nome[50], char endereco[300]);
void tiraDaAgenda(Agenda* a, char nome[50]);
char* buscaEndereco(Agenda a, char nome[50]);
