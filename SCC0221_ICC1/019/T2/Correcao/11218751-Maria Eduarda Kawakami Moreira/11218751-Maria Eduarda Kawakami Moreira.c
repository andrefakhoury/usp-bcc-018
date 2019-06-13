#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
int i, j, k, m, n; //variaveis auxiliares
int s, p; //s = numero de sentencas, p = numero de perguntas
char **produto;//os 10 produtos disponiveis
produto = (char **) malloc(12 * sizeof(char *));
for(i=0; i<10; i++){
  produto[i] = (char *) malloc(40 * sizeof(char));
}
char *palavra; //auxiliar pra ler palavras
palavra = (char *) malloc(20 * sizeof(char));
char **bow; //bag of words com as 200 palavras com no maximo 20 caracters
int **cont; //as 200 palavras relacionadas aos 10 produtos
bow = (char **) malloc(200 * sizeof(char *));
cont = (int **) malloc(200 * sizeof(int *));
for(i=0; i < 200; i++){
  cont[i] = (int *) calloc(10, sizeof(int));
  bow[i] = (char *) malloc(20 * sizeof(char));
}
int *numeroProdutos; //quantas vezes os 10 produtos aparecem numa sentenca
numeroProdutos = (int *) calloc(10, sizeof(int *));
char *busca; //auxiliar pra palavra que devemos procurar e dizer a quantidade de vezes que aparece em tal produto
busca = (char *)malloc(20 * sizeof(char));
int *sentencasBoas, *sentencasRuins; //contadores de qnts sentencas sao positivas ou negativas
sentencasBoas = (int *) calloc(10, sizeof(int));
sentencasRuins = (int *) calloc(10, sizeof(int));
//alocando memoria acima
float porcentagem;
int d = 4; //distancia dos adverbios de negacao as palavras que determinam polaridade, inicia com 4 para nao interferir com a contagem que pode ser <= 3
char PosOuNeg[20]; //auxiliar pra saber se ele pede quantidade de positivos ou de negativos
char palavrasBoas[12][20] = {"bom", "maravilhoso", "otimo", "sensacional", "excelente", "adorei", "gostei", "amei", "eficiente", "boa", "maravilhosa", "otima"};
char palavrasRuins[12][20] = {"detestei", "odiei", "ruim", "pessimo", "terrivel", "raiva", "odio", "pessima", "lento", "lenta", "fragil", "desisti"};
char inverte[3][20] = {"nao", "jamais", "nunca"};
scanf("%d%d", &s, &p);
for(j=0; j < s; j++){ //um for para as sentencas
  char auxProduto[40]; //auxiliar que vai guardar o produto
  k = 0; // k deve inicializar com 0 porque vai conferir todos os produtos que ja foram colocados
  strcpy(auxProduto, ""); //Deixando o auxProduto como "" para cada loop no for
  scanf("%s", palavra);
  strcat(auxProduto, palavra);
  scanf("%s", palavra);
  strcat(auxProduto, palavra);//armazenando o produto em auxProduto
  while(strcmp(produto[k], "") != 0){
    if(strcmp(produto[k], auxProduto) == 0)
      break; //se o produto ja tiver aparecido entao apenas ficamos com o indice k
    k++;
  }
  if(strcmp(produto[k], "") == 0)
    strcat(produto[k], auxProduto); //e um produto novo, entao sera armazenado em produto[k] e esse sera o indice do produto atual
  numeroProdutos[k]++; //contando em quantas frases esse produto aparece
  int japassou = 0; //vai checar se a frase ja tem polaridade, para que nao conte mais de uma vez
  do{
    i = 0; //deve inicializar com 0 porque vai conferir todos as palavras que ja foram colocadas no bag of words
    scanf("%s", palavra); //lendo uma palavra da frase
    d++; //somando 1 a distancia sempre, se nao tiver um adverbio de negacao, apenas aumentara o d que esta iniciado com 4
    for(n=0; n<3; n++){
      if(strcmp(palavra, inverte[n]) == 0)
        d = 0; //quando encontra um adverbio de negacao, a distancia comeca com zero
    }
    while(strcmp(bow[i], "") != 0){
      if(strcmp(bow[i], palavra) == 0){
        cont[i][k]++; //se essa palavra ja apareceu antes, ent a contagem daql palavra aumenta;
        break;
      }
      i++;
    }
    if(strcmp(bow[i], "") == 0){
      strcat(bow[i], palavra);
      cont[i][k]++; //se e uma palavra nova, entao precisa-se colocar ela no bow seguinte ao ultimo e contar 1
    }
    for(m=0; m<12; m++){ //conferindo a polaridade da sentenca
      if(strcmp(bow[i], palavrasRuins[m]) == 0){
        if(japassou == 0){
          if(d <= 3) //se a distancia entre o adverbio de negacao e as palavras que determinam a polaridade for menor que 3 entao a polaridade inverte
            sentencasBoas[k]++;
          else
            sentencasRuins[k]++;
          japassou++; //se ele achar alguma palavra ruim, entao o japassou passa a ser 1 para mostrar q essa sentenca ja tem polaridade
          break;
        }
      }
      if(strcmp(bow[i], palavrasBoas[m]) == 0){
        if(japassou == 0){
          if(d <= 3)//se a distancia entre o adverbio de negacao e as palavras que determinam a polaridade for menor que 3 entao a polaridade inverte
            sentencasRuins[k]++;
          else
            sentencasBoas[k]++;
          japassou++;//se ele achar alguma palavra boa, entao o japassou passa a ser 1 para mostrar q essa sentenca ja tem polaridade
          break;
        }
      }
    }
  }while(strcmp(palavra, "Ø") != 0); //ate o final de cada frase que tem o simbolo
}
for(i = 0; i < p; i++){ //for para cada pergunta
  char auxProduto[40]; //auxiliar para o produto novamente
  scanf("%s", palavra); //sera uma pergunta de achar quantas vezes alguma palavra aparece
  strcpy(auxProduto, ""); //Deixando o auxProduto como "" para cada loop no for
  if(strcmp(palavra, "palavra") == 0){
    scanf("%s", busca); //guardando a palavra a ser buscada
    scanf("%s", palavra); //lendo a palavra "em" que esta presente em todas as perguntas
    scanf("%s", palavra);
    strcat(auxProduto, palavra);
    scanf("%s", palavra);
    strcat(auxProduto, palavra); //guardando o produto em auxProduto
    for(j=0; j<10; j++){
      if(strcmp(auxProduto, produto[j]) == 0)
        break; //o indice j é o produto[j] atual
    }
    for(k=0; k<200; k++){
      if(strcmp(busca, bow[k]) == 0){
        printf("%d\n", cont[k][j]); //printando a quantidade de vezes que a palavra apareceu em relacao a certo produto
        break; //acha qual e o indice a palavra que esta guardada em busca no bow e printa quantas vezes ela apareceu no produto[j] que e o atual. Assim que acha, sai do for
      }
    }
  }
  if(strcmp(palavra, "quantos") == 0){ //sera uma pergunta sobre a quantidade de comentarios positivos ou negativos sobre tal produto
    scanf("%s", PosOuNeg); //auxiliar pra saber se ele pede quantos positivos ou quantos negativos
    scanf("%s", palavra); //lendo o "em"
    scanf("%s", palavra);
    strcat(auxProduto, palavra);
    scanf("%s", palavra);
    strcat(auxProduto, palavra); //armazenando o produto em auxProduto
    for(j=0; j<10; j++){
      if(strcmp(auxProduto, produto[j]) == 0)
        break; //o indice j armazena o produto atual
    }
    if(strcmp(PosOuNeg, "positivos") == 0)
      porcentagem = (float)sentencasBoas[j] * 100 / numeroProdutos[j];
    else
      porcentagem = (float)sentencasRuins[j] * 100 / numeroProdutos[j];
    printf("%.1f%%\n", porcentagem);
  }
}
//abaixo apenas liberando toda a memoria alocada:
free(palavra);
for(i=0; i<10; i++){
  free(produto[i]);
}
free(produto);
for(i=0; i<200; i++){
  free(bow[i]);
  free(cont[i]);
}
free(bow);
free(cont);
free(busca);
free(numeroProdutos);
free(sentencasBoas);
free(sentencasRuins);
return 0;
}
