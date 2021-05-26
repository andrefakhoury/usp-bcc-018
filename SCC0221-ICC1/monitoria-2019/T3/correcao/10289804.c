#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Aluno: Pedro Henrique Magalhães Cisdeli
    NUSP: 10289804
    Professor: 	Moacir Antonelli Ponti
    Turma: BCC-B
*/

// Struct criada para facilitar o uso das coordenadas e critérios
typedef struct {
  int x;
  int y;
  int c;
} Coords;

// Struct criada para facilitar o cálculo da média
typedef struct {
  int soma;
  int qtd;
} Med;

int nReg = 1;
/*
    Função que realiza a busca na ordem especificada:
        cima, direita, baixo, esquerda.
*/
void busca(int **data, int ***regioes, Coords imgD, int i, int j, int c,
           Med *media) {

  // Verifica se a posição contém um pixel na região segmentada.
  if (*(*(*regioes + i) + j) == 0) { // caso não tenha:
    /*
        Adiciona o pixel na região segmentada, incrementa a quantidade de
       pixeis, realiza a soma dos valores dos pixeis da região e, assim,
       cálcula a média.
  */
    *(*(*regioes + i) + j) = nReg;
    media->qtd++;
    media->soma += data[i][j];
    float res = ((float)media->soma) / media->qtd;
    /*
        Os ifs a seguir verificam os limites das matrizes, caso a coordenada não
       extravaze esse limite é verificado se o valor do pixel menos a média
       calculada anteriormente é menor ou igual ao critério, em caso positivo, é
       realizado uma nova busca para a determinada direção.
        Além disso, devido ao uso da recursão, é necessário inicializar a
       variável res a cada caso condicional.
    */
    if (i - 1 >= 0) { // Cima
      if (fabs(data[i - 1][j] - res) <= c) {
        busca(data, regioes, imgD, i - 1, j, c, media);
      }
    }
    res = ((float)media->soma) / media->qtd;
    if (j + 1 < imgD.y) { // Direita
      if (fabs(data[i][j + 1] - res) <= c) {
        busca(data, regioes, imgD, i, j + 1, c, media);
      }
    }
    res = ((float)media->soma) / media->qtd;
    if (i + 1 < imgD.x) { // Baixo
      if (fabs(data[i + 1][j] - res) <= c) {
        busca(data, regioes, imgD, i + 1, j, c, media);
      }
    }
    res = ((float)media->soma) / media->qtd;
    if (j - 1 >= 0) { // Esquerda
      if (fabs(data[i][j - 1] - res) <= c) {
        busca(data, regioes, imgD, i, j - 1, c, media);
      }
    }
  }
}

int main() {
  /*
    Inicialização de variáveis: lixos armazenados na imagem (lixoInteiro e
    lixoP2), nome da imagem (name), FILE da imagem (img), quantidade de
    coordenadas (qtdK), struct array de coordenadas e critérios (inputCoords) e
    struct para o cálculo da média.
    Leitura dos inputs do usuário: nome da imagem, coordenadas e critérios.
  */
  int qtdK, lixoInteiro;
  char *name, *lixoP2;
  scanf("%ms", &name);
  FILE *img = fopen(name, "r");
  if (img == NULL) {
    printf("Nao foi possivel abrir arquivo %s\n", name);
    free(name);
    return -1;
  }
  scanf("%d", &qtdK);
  Coords *inputCoords = malloc(sizeof(int) * 3 * qtdK), imgDim;
  Med media;
  for (int i = 0; i < qtdK; i++) {
    scanf("%d %d %d", &inputCoords[i].x, &inputCoords[i].y, &inputCoords[i].c);
  }
  /*
    Inicialização de variáveis: matriz para os dados dos pixeis e para a região
    segmentada, imgData e regioes, respectivamente.
    A matriz regioes é inciada zerada para que seja acrescido um a cada nova
    região a fim de facilitar na detecção das bordas.
    Leitura da imagem: string lixo, quantidade de linhas e colunas,
    inteiro lixo e dados dos pixeis.
  */
  fscanf(img,
         "%m[^\r\n]"
         "%d %d[^\r\n]",
         &lixoP2, &imgDim.y, &imgDim.x);
  fscanf(img, "%d[^\r\n]", &lixoInteiro);

  int **imgData = malloc(sizeof(int *) * imgDim.x),
      **regioes = malloc(sizeof(int *) * imgDim.x);
  for (int i = 0; i < imgDim.x; i++) {
    imgData[i] = (int *)malloc(sizeof(int) * imgDim.y);
    regioes[i] = (int *)malloc(sizeof(int) * imgDim.y);
    for (int j = 0; j < imgDim.y; j++) {
      fscanf(img, "%d", &imgData[i][j]);
      regioes[i][j] = 0;
    }
  }
  /*
    Processamento: incialização zeradas das variáveis responsáveis pela média,
    incremento da variável responsável por diferenciar as regiões segmentadas,
    chamada da função da busca e passagem dos inputs para esta
  */
  for (int i = 0; i < qtdK; i++) {
    media.soma = 0;
    media.qtd = 0;
    busca(imgData, &regioes, imgDim, inputCoords[i].x, inputCoords[i].y,
          inputCoords[i].c, &media);
    nReg++;
  }

  /*
     Algoritmo responsável por verificar as bordas.
     Similarmente ao da busca, verifica os limites da matriz e, caso não
     extravaze, verifica se os pixeis em volta (em cima, a direita, em baixo e a
     esquerda) pertecem à regiões diferentes, caso sim, mostra na tela o pixel
     atual e seque para o próximo condicional, visto que se caracteriza como
     pixel de borda.
  */
  for (int i = 0; i < imgDim.x; i++) {
    for (int j = 0; j < imgDim.y; j++) {
      if (i - 1 >= 0) { // cima
        if (regioes[i][j] != regioes[i - 1][j]) {
          printf("(%d, %d)\n", i, j);
          continue;
        }
      }
      if (j + 1 < imgDim.y) { // direita
        if (regioes[i][j] != regioes[i][j + 1]) {
          printf("(%d, %d)\n", i, j);
          continue;
        }
      }
      if (i + 1 < imgDim.x) { // baixo
        if (regioes[i][j] != regioes[i + 1][j]) {
          printf("(%d, %d)\n", i, j);
          continue;
        }
      }
      if (j - 1 >= 0) { // esquerda
        if (regioes[i][j] != regioes[i][j - 1]) {
          printf("(%d, %d)\n", i, j);
          continue;
        }
      }
    }
  }

  // Encerramento: liberação de memória HEAP e fechamento da imagem.
  fclose(img);
  img = NULL;
  free(name);
  free(inputCoords);
  free(lixoP2);
  for (int i = 0; i < imgDim.x; i++) {
    free(imgData[i]);
    free(regioes[i]);
  }
  free(imgData);
  free(regioes);

  return 0;
}
