/*
  Trabalho 3 - Segmentação de Imagens

  Paulo Matana da Rocha  Numero_Usp: 10892676
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//função que aloca as matrizes usadas na heap
void aloca_mat(int n, int m, int ***imagem){
  *imagem = malloc(sizeof(int*)*m);
  for(int i=0; i<m; i++){
    //printf("|%d|\n", i);
    (*imagem)[i] = calloc(sizeof(int),n);
  }
}

//função que da free nas matrizes alocadas pela função aloc_mat
void free_mat(int m, int ***imagem){
  for(int i=0; i<m; i++){
    free((*imagem)[i]);
  }
  free(*imagem);
}

//funçao recursiva que segmenta a imagem
void segmenta(int ***imagem, int ***matriz, int set, int x, int y, int criterio, int *tam, int **soma){
  if((*matriz)[x][y] == 0){
    (*matriz)[x][y] = set;
    (*soma)[0] += (*imagem)[x][y];
    (*soma)[1]++;

    if(x-1 >= 0){
      if(fabs((float)(*imagem)[x-1][y] - ((float)(*soma)[0]/(float)(*soma)[1])) <= (float)criterio){
        segmenta(imagem, matriz, set, (x-1), y, criterio, tam, soma);
      }
    }
    if(y+1 < tam[0]){
      if(fabs((float)(*imagem)[x][y+1] - ((float)(*soma)[0]/(float)(*soma)[1])) <= (float)criterio){
        segmenta(imagem, matriz, set, x, (y+1), criterio, tam, soma);
      }
    }
    if(x+1 < tam[1]){
      if(fabs((float)(*imagem)[x+1][y] - ((float)(*soma)[0]/(float)(*soma)[1])) <= (float)criterio){
        segmenta(imagem, matriz, set, (x+1), y, criterio, tam, soma);
      }
    }
    if(y-1 >= 0){
      if(fabs((float)(*imagem)[x][y-1] - ((float)(*soma)[0]/(float)(*soma)[1])) <= (float)criterio){
        segmenta(imagem, matriz, set, x, (y-1), criterio, tam, soma);
      }
    }
  }
  return;
}

//função que printa as coordenadas dos pxels de borda
void print_front(int n, int m, int ***matriz){
  int flag;
  for(int i=0; i < m; i++){
    for (int j=0; j < n; j++){
      flag = 0;
      if((j+1 < n) && (*matriz)[i][j+1] != (*matriz)[i][j]){
        flag = 1;
      }else{
        if((j-1 >=0) && (*matriz)[i][j-1] != (*matriz)[i][j]){
          flag = 1;
        }else{
          if((i+1 < m) && (*matriz)[i+1][j] != (*matriz)[i][j]){
            flag = 1;
          }else{
            if((i-1 >= 0) && (*matriz)[i-1][j] != (*matriz)[i][j]){
              flag = 1;
            }
          }
        }
      }
      if(flag > 0) printf("(%d, %d)\n", i , j);
    }
  }

}

int main(void){
  char *nome_arq;
  FILE* arq;
  int n, m, n_click, criterio, *pt_click, *tam, *soma;
  int **imagem, **matriz;

  //iniciando arrays dinamicamente
  nome_arq = malloc(sizeof(char)*20);
  tam = malloc(sizeof(int)*2); //tamano da matriz
  pt_click = malloc(sizeof(int)*2); //coordenadas de click
  soma = malloc(sizeof(int)*2); //soma[0]=soma dos valores dos espaços conquistados, soma[1]=quantidade de espaços conquistados;

  //pega o nome do arquivo e abre ele
  scanf("%s", nome_arq);
  arq = fopen(nome_arq, "r");

  //mensagem de erro caso o arquivo nao seja encontado
  if(arq==NULL){
    printf("erro na abertura do arquivo\n");
    return 1;
  }

  fscanf(arq, "%*s %d %d %*s", &n, &m);
  //transferindo as variáveis para um array de forma que seja mais facil passar para a função
  tam[0] = n;
  tam[1] = m;


  aloca_mat(n, m, &imagem);
  aloca_mat(n, m, &matriz);

  //estruturas de repetição que copiam a matriz do arquivo para a matriz imagem na heap
  for(int i=0; i<m; i++){
    for(int j=0; j<n; j++){
      fscanf(arq, "%d", &imagem[i][j]);
    }
  }

  scanf("%d", &n_click);

  //for que lê cada uma das entradas de clique e em seguida executa a função segmenta no ponto
  for(int i=0; i<n_click; i++){
    scanf("%d %d %d", &pt_click[0], &pt_click[1], &criterio);

    //reseta as variaveis de soma antes de cada chamada da função segmenta
    soma[0] = 0;
    soma[1] = 0;

    segmenta(&imagem, &matriz, i+1, pt_click[0], pt_click[1], criterio, tam, &soma);

  }

  print_front(n, m, &matriz);

  // fechamento do arquivo
  fclose(arq);

  //liberando arrays
  free(nome_arq);
  free(tam);
  free(pt_click);
  free(soma);

  //liberando as matrizes da heap
  free_mat(m, &imagem);
  free_mat(m, &matriz);
return 0;
}
