typedef int elem;

typedef struct bloco {
	elem value;
	struct bloco *prev, *next;
} no;

typedef struct {
	no *begin, *end;
} list;

void create(list*);
void apaga(list*);
void imprime(list);
int include(list*, elem, int);