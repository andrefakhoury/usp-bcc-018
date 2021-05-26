

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int busca(int coordX, int coordY, int criterioC, int largura, int altura, int **matriz, int **matriz_analise,float *soma_media, float *num_media, float *media, int consulta);
//declaração da função busca

float modulo(float valor);
//declaração da função modulo

int main(){
 
  char *nome_arq=NULL;
  nome_arq=(char*)malloc(15*sizeof(char));
  if(nome_arq == NULL){
    printf("Sem memoria!");
    exit(1);
  }
  scanf("%s",nome_arq);
  //armazenando o nome do arquivo .pgm

  int num_consult=0;
  scanf("%d",&num_consult);
  //armazenando o numero de consultas a serem feitas

  int **coordenadas;
  coordenadas=(int**)malloc(num_consult*sizeof(int*));
  for(int i=0;i<num_consult;i++){
    coordenadas[i]=(int*)malloc(3*sizeof(int));
  }
  //alocando dinamicamente uma matriz para armazenar os dados das consultas
  if(coordenadas == NULL){
    printf("Sem memoria!");
    exit(1);
  }
  for(int i=0;i<num_consult;i++){
   for(int j=0;j<3;j++){
     scanf("%d",&coordenadas[i][j]);
   }
  }
  //armazenando os dados das consultas X Y e C

  FILE *arquivo;
  arquivo=fopen(nome_arq,"rb");
  if(arquivo == NULL){
    printf("Sem memoria!");
    exit(1);
  }
  //abrindo o arquivo .pgm

  int largura, altura;
  fscanf(arquivo,"%*s%d %d",&largura, &altura);
  //lendo as dimensões da matriz do arquivo .pgm
  
  int lixo;
  fscanf(arquivo,"%d",&lixo);
  //lendo 255 e armazenando como lixo
  
  int **matriz;
  matriz=(int**)malloc(altura*sizeof(int*));
  for(int i=0;i<altura;i++){
    matriz[i]=(int*)malloc(largura*sizeof(int));
  }
  if(matriz == NULL){
    printf("Sem memoria!");
    exit(1);
  }
  //alocando dinamicamente matriz para armazenar imagem do arquivo .pgm
  for(int i=0;i<altura;i++){
    for(int j=0;j<largura;j++){
      fscanf(arquivo,"%d",&matriz[i][j]);
    }
  }
  //armazenando imagem do arquivo na matriz alocada
  fclose(arquivo);
  //fechando o arquivo .pgm

  int **matriz_analise;
  matriz_analise=(int**)calloc(altura,sizeof(int*));
  for(int i=0;i<altura;i++){
    matriz_analise[i]=(int*)calloc(largura,sizeof(int));
  }
  if(matriz_analise == NULL){
    printf("Sem memoria!");
    exit(1);
  }
  //alocando dinamicamente matriz de zeros para análise das bordas
  
  float soma_media;
  float num_media;
  float media;
  //variaveis para cálculo da média na busca
  int coordX;
  int coordY;
  int criterioC;
  int consulta;
  //variáveis para a consulta
  
  for(int i=0;i<num_consult;i++){
    soma_media=0;
    num_media=0;
    coordX=coordenadas[i][0];
    coordY=coordenadas[i][1];
    criterioC=coordenadas[i][2];
    consulta=i+1;
    busca( coordX, coordY, criterioC, largura, altura, matriz, matriz_analise, &soma_media, &num_media, &media, consulta);
    //chamando a função busca
  }
  
  for(int i=0;i<altura;i++){
    for(int j=0;j<largura;j++){
      if(i>0){
        if(matriz_analise[i][j] != matriz_analise[i-1][j]){
          printf("(%d, %d)\n",i, j);
          continue;
        }
      }
      if(j<largura-1){
        if(matriz_analise[i][j] != matriz_analise[i][j+1]){
          printf("(%d, %d)\n",i, j);
          continue;
        }
      }
      if(i<altura-1){
        if(matriz_analise[i][j] != matriz_analise[i+1][j]){
          printf("(%d, %d)\n",i, j);
          continue;
        }
      }
      if(j>0){
        if(matriz_analise[i][j] != matriz_analise[i][j-1]){
          printf("(%d, %d)\n",i, j);
          continue;
        }
      }
    }
  }
  //percorrendo a matriz de analise para procurar os pixels de borda

  for (int i = 0; i < altura; i++) free(matriz[i]);
  for (int i = 0; i < altura; i++) free(matriz_analise[i]);
  for (int i = 0; i < num_consult; i++) free(coordenadas[i]);

  free(coordenadas);
  free(nome_arq);
  free(matriz);
  free(matriz_analise);

  return 0;
}

int busca(int coordX, int coordY, int criterioC, int largura, int altura,int **matriz, int **matriz_analise,float *soma_media, float *num_media,float *media, int consulta){

  if(matriz_analise[coordX][coordY] != 0){
    return 0;
  }
  //quando o pixel da matriz de análise for diferente de zero
  matriz_analise[coordX][coordY] = consulta;
  //transforma o pixel da matriz de analise de 0 para o número da consulta para inserir o pixel na região segmentada
  
  *num_media+=1;
  *soma_media+=matriz[coordX][coordY];
  *media=((*soma_media)/(*num_media));
  //cálculo da média 
  
  if(coordX>0){
    if(criterioC>=modulo(matriz[(coordX-1)][coordY]-(*media))){
      busca(coordX-1, coordY, criterioC, largura, altura, matriz, matriz_analise, soma_media, num_media, media, consulta);
    }
  }//se o pixel acima estiver dentro do critério C
  
  if(coordY<largura-1){
    if(criterioC>=modulo(matriz[coordX][(coordY+1)]-(*media))){
      busca(coordX, coordY+1, criterioC, largura, altura, matriz, matriz_analise, soma_media, num_media, media, consulta);
    }
  }//se o pixel ao lado direito estiver dentro do critério C
  
  if(coordX<altura-1){
    if(criterioC>=modulo(matriz[(coordX+1)][coordY]-(*media))){
      busca(coordX+1, coordY, criterioC, largura, altura, matriz, matriz_analise, soma_media, num_media, media, consulta);
    }
  }//se o pixel abaixo estiver dentro do critério C
  
  if(coordY>0){
    if(criterioC>=modulo(matriz[coordX][(coordY-1)]-(*media))){
      busca(coordX, coordY-1, criterioC, largura, altura, matriz, matriz_analise, soma_media, num_media, media, consulta);
    }
  }//se o pixel ao lado esquerdo estiver dentro do critério C
  
  return 0;

}

float modulo(float valor){
  if(valor<0){
    valor+=((valor)*(-2));
    return(valor);
  }
    return(valor);
}//função que retorna o módulo de um número

