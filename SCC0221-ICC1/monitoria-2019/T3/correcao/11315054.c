#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int **alok (int altura, int largura);
void liberar (int **matriz, int testes);
void conquista (int **matriz, int **imagem, int x, int y, int c, int altura, int largura, int *media, int numero);
void borda (int **matriz, int largura, int altura, int i, int j);

int **alok (int altura, int largura){ // função dedicada a alocar dinamicamente as matrizes

    int **matriz = (int**) calloc (altura, sizeof (int*));
    for (int i = 0; i<altura; i++){
        matriz[i] = (int*) calloc (largura, sizeof (int));
    }

    return (matriz);
}

void liberar (int **matriz, int altura){ // e de suma importancia sempre liberar toda a memora alocada no programa

    for (int i = 0; i<altura; i++){
        free (matriz[i]);
    }
    free (matriz);

    return;
}

void conquista (int **matriz, int **imagem, int x, int y, int c, int altura, int largura, int *media, int numero){

    if (matriz[x][y] > 0){ // porção crucial do programa
        return;            // esta funçao verifica o caminho feito a partir das coordenadas que o usuario insere
    }                      // primeira restriçao, se a coordenada ja foi verificada em outros casos, ela nao deve ser novamente adicionada a trilha

    media[0] += imagem[x][y]; // a media a ser comparada com o criterio e um vetor de duas posiçoes
    matriz[x][y] = numero;    // a primeira [0] guarda o valor dos pixels ja avaliados
    media[1]++;               // ja a segunda e um acumulador, guarda quantos pixels foram conquistados

    if ((x - 1) >= 0){
        if (fabs(imagem[x-1][y] - (media[0]/(float)media[1])) <= c){                         // segundo as instruçoes verifica-se:
            conquista (matriz, imagem, x-1, y, c, altura, largura, media, numero);    // cima
        }
    }

    if ((y + 1) < largura){
        if (fabs(imagem[x][y+1] - (media[0]/(float)media[1])) <= c){                         // direita
            conquista (matriz, imagem, x, y+1, c, altura, largura, media, numero);
        }
    }

    if ((x + 1) < altura){
        if (fabs(imagem[x+1][y] - (media[0]/(float)media[1])) <= c){                        // baixo
            conquista (matriz, imagem, x+1, y, c, altura, largura, media, numero);
        }
    }

    if ((y - 1) >= 0) {
        if (fabs(imagem[x][y-1] - (media[0]/(float)media[1])) <= c){                        // esquerda
            conquista (matriz, imagem, x, y-1, c, altura, largura, media, numero);
        }
    }
        
    return;                                                                          // a funçao uma vez iniciada, apenas encerra a recursao quando:
                                                                                     // cada avaliaçao for verificada, estas sao:
                                                                                     // pertencer a matriz
                                                                                     // estar dentro do criteiro indicado na entrada
                                                                                     // nao exceder os limites laterais da matriz
}

void borda (int **matriz, int largura, int altura, int x, int y){      // retornando a imagem seguimentada e as bordas
                                                                       // o criterio para verificar se pertence a borda ou nao e
                                                                       // no redor do pixel ha outros conquistados ou nao, se ocorrer, logo, este pertence a borda
    if ((x - 1) >= 0){
        if (matriz[x][y] != matriz[x-1][y]){                           // semelhante a conquista, verifica-se cima, baixo e lado, pixel a pixel
            printf ("(%d, %d)\n", x, y);
            return;
        }
    }

    if ((y + 1) < largura){
        if (matriz[x][y] != matriz[x][y+1]){
            printf ("(%d, %d)\n", x, y);
            return;
        }
    }

    if ((x + 1) < altura){
        if (matriz[x][y] != matriz[x+1][y]){
            printf ("(%d, %d)\n", x, y);
            return;
        }
    }

    if ((y - 1) >= 0){
        if (matriz[x][y] != matriz[x][y-1]){
            printf ("(%d, %d)\n", x, y);
            return;
        }
    }

    return;
}

int main (void){
    
    char entrada[12];
    char lixo[20];
    int testes, altura, largura, x, y, c;

    int *media = (int*) calloc (2, sizeof(int)); //declaraçao do vetor que guarda a media
    FILE *fp;

    scanf ("%s", entrada);
    scanf ("%d", &testes);

    if ((fp = fopen (entrada, "r")) == NULL){                   // abertura do arquivo (e necessario fecha-lo tambem)
        printf ("Erro na abertura do arquivo.\n");
        exit(1);
    }

    fscanf (fp, "%s", lixo);                                   // verificaçoes iniciais, como consta na descriçao do trabalho
    fscanf (fp, "%d %d", &largura, &altura);                   // as linhas 1 e 3 nao sao uteis ao trabalho
    fscanf (fp, "%s", lixo);

    int **imagem = alok (altura, largura);
    if (imagem == NULL){
        printf ("Falha na alocação.");
        exit (1);
    }

    for (int i = 0; i<altura; i++){                            // para melhor manuseio do conteudo do arquivo, foi definida uma matriz que guarda seus pixels
        for (int j = 0; j<largura; j++){
            fscanf (fp, "%d", &imagem[i][j]);
        }
    }

    int **matriz = alok (altura, largura);                    // essa matriz possui as mesmas dimensoes da imagem, porem, diferente da outra
                                                              // guarda com numeros as trilhas que cada verificaçao formou
                                                              // exemplo: verificaçao 1, preenche a trilha com '1', e a segunda com '2'
    if (matriz == NULL){
        printf ("Falha na alocação.");
        exit (1);
    }

    do {
        scanf ("%d %d %d", &x, &y, &c);
        media[0] = 0;                                                         // a cada volta o vetor da media deve ser zerado, pois a cada volta, a uma nova a ser formada
        media[1] = 0;
        conquista (matriz, imagem, x, y, c, altura, largura, media, testes);  // chamada da funçao, foi desenvolvido com uma estrutura de repetiçao
        testes --;                                                            // pois ha muitas entradas possiveis, a serem definidas pelo usuario: verificaçao < 100

    } while (testes != 0);

    for (int i = 0; i<altura; i++){                                           // impressao da borda
        for (int j =0; j<largura; j++){
            borda (matriz, largura, altura, i, j);
        }
    }

    fclose (fp);                                                              // fechar o arquivo
    liberar (matriz, altura);                                                 // liberar as matrizes
    liberar (imagem, altura);                                                 // liberar o vetor tambem e de suma importancia
    free (media);

    return 0;
}