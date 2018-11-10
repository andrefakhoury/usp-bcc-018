#include <string.h>

#define tamMax 50
typedef char elem;

typedef struct { //blocos do banco de memoria: valor e "ponteiro" pro proximo
    elem info[16];
    int next;
} Block;

typedef struct { //struct do banco: vetor de blocos e posicao do primeiro vazio
    Block vet[tamMax];
    int empty;
} Bank;

//cria um banco vazio e retorna
Bank create_bank();

//seta as informações do nó
void set_info(Bank *b, int pos, elem* x);

//seta o próximo nó
void set_next(Bank *b, int pos, int next);

//pega as informações do nó
elem* get_info(Bank *b, int pos);

//pega o próximo nó
int get_next(Bank *b, int pos);

//pega o proximo vazio
int get_node(Bank *b);

//retorna se está cheio
int isFull_bank(Bank *b);

//limpa o banco
void free_bank(Bank *b, int pos);