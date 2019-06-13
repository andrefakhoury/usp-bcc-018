#include <stdio.h>
#include <string.h>

typedef struct _unidadeBoW{
  char palavra[40];
  int frequenciaPorProduto[10];// Quantiade de vezes que a palavra aparece nos comentarios de certo produto
}unidadeBoW;

int updateProduto(char *palavra, char tiposDeProduto[10][30]);
void updateBow(char *palavra, unidadeBoW BoW[200], int numeroProduto);
int checkBow(char *palavra, unidadeBoW BoW[200]);
void updatePosNegComentario(char *frase,int posNegComentario[2]);

int main(int argc, char const *argv[]) {
  int qtdFrases, qtdPerg, i;
  char frase[410];// Armazena a frase atual para processar positivos e negativos
  char palavra[40];// Pode armazenar até duas palavras para auxiliar no processamento
  char palavraAux[40];
  unidadeBoW BoW[200];// Armazena todos os tipos de diferentes palavras
  char tiposDeProduto[10][30];// Armazena o nome dos tipos de produtos diferentes
  int posNegComentario[10][2];// Para cada tipo de produto armazena a quantidade de comentários positivos e negativos
  int numeroProduto, numeroPalavra;
  float totalComentariosAux;

  scanf("%d%d",&qtdFrases,&qtdPerg);

  //----- Recebe todas as frases e organiza os produtos e palavras -----//
  for (i = 0; i < qtdFrases; i++) {
    frase[0]='\0';
    //---Atualiza os produtos ---//
    scanf("%s", palavra);scanf("%s", palavraAux);
    strcat(palavra, palavraAux);
    strcat(frase, palavra);
    strcat(frase, " ");

    numeroProduto = updateProduto(palavra,tiposDeProduto);
    //----- Atualiza palavras do BoW ---//
    scanf("%s", palavra);
    do{
      updateBow(palavra, BoW, numeroProduto);
      scanf("%s", palavra);
      strcat(frase, palavra);
      strcat(frase, " ");
    }while(strcmp(palavra,"Ø")!=0);
    updatePosNegComentario(frase,posNegComentario[numeroProduto]);
  }

  for (i = 0; i < qtdPerg; i++) {
    scanf("%s",palavra);
    if(strcmp(palavra,"palavra")==0){
      // Armazena o número desta palavra
      scanf("%s%s",palavra,palavraAux);
      numeroPalavra = checkBow(palavra, BoW);
      // Recebe o nome do produto e coloca na variavel palavraPergunta
      scanf("%s%s",palavra,palavraAux);
      strcat(palavra,palavraAux);
      // Armazena o número do produto
      numeroProduto = updateProduto(palavra, tiposDeProduto);

      printf("%d\n",BoW[numeroPalavra].frequenciaPorProduto[numeroProduto]);
    }else if(strcmp(palavra,"quantos")==0){
      scanf("%s%s",palavra,palavraAux);
      // Armazena se a palavra é negativa ou positiva
      if(strcmp(palavra,"negativos")==0)      numeroPalavra=0;
      else if(strcmp(palavra,"positivos")==0) numeroPalavra=1;
      // Recebe o nome do produto e coloca na variavel palavraPergunta
      scanf("%s%s",palavra,palavraAux);
      strcat(palavra,palavraAux);
      // Armazena o número do produto
      numeroProduto = updateProduto(palavra, tiposDeProduto);
      totalComentariosAux = posNegComentario[numeroProduto][0]+posNegComentario[numeroProduto][1];

      printf("%.1f%%\n", (posNegComentario[numeroProduto][numeroPalavra] / totalComentariosAux)*100);
    }
  }
  return 0;
}

int updateProduto(char *palavra, char tiposDeProduto[10][30]){
  // Adiciona o tipo de produto a lista se ainda não existir
  // Retorna o número do produto no vetor de tipos de produto
  int i;
  for (i = 0; i < 10; i++) {
    if(strcmp(palavra,tiposDeProduto[i])==0)
      return i;
    if(strcmp(tiposDeProduto[i],"")==0){
      strcat(tiposDeProduto[i],palavra);
      return i;
    }
  }
  return -1;
}

void updateBow(char *palavra, unidadeBoW BoW[200], int numeroProduto){
  //Adiciona a palavra ao BoWpalavras se precisar e armazena o numero da palavra
  int i;
  for (i = 0; i < 200; i++) {
    if(strcmp(palavra,BoW[i].palavra)==0){
      BoW[i].frequenciaPorProduto[numeroProduto]++;
      return;
    }
    if(strcmp(BoW[i].palavra,"")==0){
      strcat(BoW[i].palavra,palavra);
      BoW[i].frequenciaPorProduto[numeroProduto]++;
      return;
    }
  }
}

int checkBow(char *palavra, unidadeBoW BoW[200]){
  //Apenas retorna o local onde a palavra está armazenada
  int i;
  for (i = 0; i < 200; i++) {
    if(strcmp(palavra,BoW[i].palavra)==0){
      return i;
    }
  }
  return -1;
}

void updatePosNegComentario(char *frase,int posNegComentario[2]){
  // Calcula a quantidade de comentarios positivos ou negativos na frase para um certo produto
  int i,j,index = 0, contAdvDist = 3, palavrasPos = 0, palavrasNeg = 0;
  char palavra[40] = "";
  char positivo[12][16] = {"bom","maravilhoso", "otimo", "sensacional", "excelente", "adorei", "gostei", "amei", "eficiente", "boa", "maravilhosa", "otima"};
  char negativo[12][16] = {"detestei", "odiei", "ruim", "pessimo", "terrivel", "raiva", "odio", "pessima", "lento", "lenta", "fragil", "desisti"};
  char adverbios[3][10] = {"nao", "jamais", "nunca"};

  for (i = 0; strcmp(palavra,"Ø")!=0; i++) {
    palavra[index]=frase[i];
    palavra[index+1]='\0';
    index++;

    if(frase[i]==' '){
      contAdvDist++;
      palavra[index-1]='\0';
      // Dependendo se tem um adverbio proximo ou nao, a palavra pode ser positiva ou negativa
      for (j = 0; j < 12; j++) {
        if(strcmp(palavra,positivo[j])==0)
          contAdvDist>3 ? palavrasPos++ : palavrasNeg++;
        if(strcmp(palavra,negativo[j])==0)
          contAdvDist>3? palavrasNeg++ : palavrasPos++;
        }
      for (j = 0; j < 3; j++)
        if(strcmp(palavra,adverbios[j])==0) contAdvDist=0;

      palavra[0]='\0';
      index=0;
    }
  }
  if(palavrasPos)posNegComentario[1]++;
  else if(palavrasNeg) posNegComentario[0]++;
}
