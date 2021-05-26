#include <stdio.h>
#include <stdlib.h>

// Estrutura de Posicao
typedef struct position{
    int x, y;
} Position;

// Estrutura de Lista
typedef struct lista{
    Position *pos; // Vetor de Posicoes
    int tam; // Tamanho da lista
} Lista;

// Estrutura de Matriz
typedef struct matriz{
    int **matriz, altura, largura;
} Matriz;


// Verifica se uma posicao esta na lista
int isPosInList(Lista lista, Position pos)
{
    for(int i=0;i<lista.tam;i++)
        if(pos.x == lista.pos[i].x && pos.y == lista.pos[i].y) return 1;


    return 0;
}


// Retorna o modulo da diferenca entre dois numeros
int difference(int x, int y)
{
    if(x-y>0) return x-y;
    else return y-x;
}

// Retorna a media de todos os pontos na lista
float getMedia(Lista lista, Matriz matriz)
{
    int soma = 0, count =0;
    for(int i=0;i<lista.tam;i++)
    {
        soma += matriz.matriz[lista.pos[i].y][lista.pos[i].x];
        count++;
    }
    if(count>0) return (float)soma/(float)count;
    else return 0;
}

// Imprime a lista
void printLista(Lista lista)
{
    for(int i=0;i<lista.tam;i++)
    {
        printf("(%d, %d)\n", lista.pos[i].y, lista.pos[i].x);
    }
}

// Verifica se a posicao encontra-se dentro dos limites da matriz
int checkLimits(Position pos, Matriz matriz)
{
    return pos.x >= 0 && pos.x < matriz.largura && pos.y >= 0 && pos.y < matriz.altura;
}

// Insere uma posicao na lista
void inserirLista(Lista *lista, Position pos)
{
    lista->pos = (Position *)realloc(lista->pos, (lista->tam + 1) * sizeof(Position));
    lista->pos[lista->tam] = pos;
    lista->tam++;
}

// Funcao Principal Recursiva
void filter(Matriz matriz, Lista *lista, Position pos, int criterio)
{
    float media = getMedia(*lista, matriz);
    Position cima, direita, baixo, esquerda;

    cima.x = pos.x;
    cima.y = pos.y-1;

    direita.x = pos.x+1;
    direita.y = pos.y;

    baixo.x = pos.x;
    baixo.y = pos.y+1;

    esquerda.x = pos.x-1;
    esquerda.y = pos.y;

    // Realiza na ordem: cima, direita, baixo, esquerda
    // 1. Verifica se encontra-se dentro dos limites
    // 2. Verifica se ja nao esta na lista
    // 3. Verifica se a diferenca do valor e a media sao menores que o criterio
    // 4. Entao adiciona na lista e a funcao recursiva eh chamada novamente

    if(checkLimits(cima, matriz))
    {
        if(!isPosInList(*lista, cima) && difference(matriz.matriz[cima.y][cima.x], media)<=criterio)
        {
            inserirLista(lista, cima);
            filter(matriz, lista, cima, criterio);
        }
    }
    if(checkLimits(direita, matriz))
    {
        if(!isPosInList(*lista, direita) && difference(matriz.matriz[direita.y][direita.x], media)<=criterio)
        {
            inserirLista(lista, direita);
            filter(matriz, lista, direita, criterio);
        }
    }
    if(checkLimits(baixo, matriz))
    {
        if(!isPosInList(*lista, baixo) && difference(matriz.matriz[baixo.y][baixo.x], media)<=criterio)
        {
            inserirLista(lista, baixo);
            filter(matriz, lista, baixo, criterio);
        }
    }
    if(checkLimits(esquerda, matriz))
    {
        if(!isPosInList(*lista, esquerda) && difference(matriz.matriz[esquerda.y][esquerda.x], media)<=criterio)
        {
            inserirLista(lista, esquerda);
            filter(matriz, lista, esquerda, criterio);
        }
    }
}


int main()
{
    char file_name[30], temp;
    scanf("%s", file_name);  // Scan para o nome do arquivo

    FILE *arq = fopen(file_name, "r");

    //char linha[256];
    fscanf(arq, "%s", file_name); // ignorar primeira linha
    int largura, altura;
    fscanf(arq, "%d %d", &largura, &altura); // ler altura e largura
    fscanf(arq, " %s", file_name); // ignorar terceira linhas

    Matriz matriz;
    matriz.matriz = (int **)malloc(altura*sizeof(int *)); // aloca a primeira dimensao da matriz

    for(int i=0;i<altura;i++)
    {
        matriz.matriz[i] = (int *)malloc(largura*sizeof(int)); // aloca a segunda dimensao da matriz
        for(int j=0;j<largura;j++)
        {
            fscanf(arq, " %d", &matriz.matriz[i][j]);
            // printf("%d ", matriz.matriz[i][j]);
        }
    }
    matriz.altura = altura;
    matriz.largura = largura;


    int qtd_consultas, criterio;
    Position pos;
    Lista lista; // inicializa lista
    lista.tam = 0;
    scanf("%d", &qtd_consultas); // le quantidade de consultas
    for(int i=0; i<qtd_consultas;i++)
    {
        scanf("%d %d %d", &pos.y, &pos.x, &criterio); // le posicao y, x e o criterio
        if(isPosInList(lista, pos)) continue; // se a posicao desejada ja esta na lista, continuar pra proxima consulta

        if(lista.tam == 0) // caso a lista esteja vazia, alocar primeiro espaco
        {
            lista.pos = (Position *)malloc(sizeof(Position));
            lista.pos[0] = pos;
            lista.tam++;
        }
        else // se nao, realocar espaco
        {
            lista.pos = (Position *)realloc(lista.pos, (lista.tam + 1) * sizeof(Position));
            lista.pos[lista.tam] = pos;
            lista.tam++;
        }
        filter(matriz, &lista, pos, criterio); // chamar funcao recursiva
    }
    printLista(lista); // Printar lista

    fclose(arq);
    return 0;
}
