typedef struct racional Racional;

Racional* le(int numerador, int denominador);
void apagar(Racional* rac);
float mediaRacionais(Racional** vracs, int tamanho, char* erro);
float converteReal(Racional* rac);