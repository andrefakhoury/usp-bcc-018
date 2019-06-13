#include <stdio.h>

#include <stdlib.h>

#include <string.h>

typedef struct {
  char nome[20]; //nome do produto
  char vocab[20][20]; //armazena as palavras do comentario
  int qtd[20]; //conta as apariçoes de palavras
  int positivo; //conta o numero de palavras positivas
  int negativo; //conta o numero de palavras negativas
}
tipo_Produto;

typedef struct { 
  char nome[20]; //nome do produto presente na pergunta
  char adj[20]; //palavra a ser procurada 
}
tipo_Comando;

int main(void) {
  int aux = 0;
  int num_sentencas;
  int num_perguntas;
  float resultado[20]; //array que armazena a resposta para respectiva pergunta
  char lixo[22]; //elimina parte irrelevante da pergunta
  float total = 0;
  scanf("%d %d", & num_sentencas, & num_perguntas);

  tipo_Produto * produto = (tipo_Produto * ) malloc(num_sentencas * sizeof(tipo_Produto));
  tipo_Comando comando[20]; 
  char positivos[12][20] = {"bom","maravilhoso", "otimo", "sensacional", "excelente", "adorei", "gostei", "amei", "eficiente", "boa", "maravilhosa", "otima"};
  char negativos[12][20] = {"detestei", "odiei", "ruim", "pessimo", "terrivel", "raiva", "odio", "pessima", "lento", "lenta", "fragil", "desisti"};
  char inversores[3][20] = {"nao", "jamais", "nunca"};

  for (int i = 0; i < 10; i++) { // zera a qtd, negativos e positivos de cada produto e o array de resultados
    for (int j = 0; j < 20; j++) {
      produto[i].qtd[j] = 0;
      resultado[j]=0;
    }
    produto[i].positivo = 0;
    produto[i].negativo = 0;
  }

  for (int i = 0; i < num_sentencas; i++) {
    scanf("\r"); //elimina caracteres indesejados
    scanf("\n");
    scanf("%[^;]", produto[i].nome); //le o nome do produto 
    int size = strlen(produto[i].nome) + 1; //retira o espaço no final da string
    if (produto[i].nome[size - 2] == ' ') {
      produto[i].nome[size - 2] = '\0';
    }
    for (int j = 0; j < 20; j++) {
      getchar(); //elimina caracteres indesejados
      scanf("%s", produto[i].vocab[j]); //le todas as sentenças armazenando suas palavra (inclue o Ø) 
      if (strcmp(produto[i].vocab[j], "Ø") == 0) { // em seu produto correspondente
        break;
      }
    }
  }
  for (int i = 0; i < num_sentencas; i++) { //conta as repeticoes das palvras e armazena no array qtd
    for (int j = 0; j < 20; j++) { //onde vocab[i]=palavra e qtd[i]=repetiçoes da palavra
      for (int k = 0; k < 20; k++) {
        if (strcmp(produto[i].vocab[j], produto[i].vocab[k]) == 0) { //k é a posicao onde a palavra aparece antes
          aux = k;                                                   //achada a primeira apariçao, a palavra aux "lembra" essa posiçao
          break;                                                     //e a incrementa sempre que a palavra em questao se repetir
        }                                                            //ex: vocab[2]="bom",qtd[2]++; vocab[4]="bom",qtd[2]++;
      }
      produto[i].qtd[aux]++;
    }
  }
  for (int i = 0; i < num_perguntas; i++) { //le as perguntas e identifica o produto e as palavras a serem contadas
    scanf("%s", lixo); //a estrutura da pergunta e sempre a mesma, logo e possivel ler apenas as palavras chave
    scanf("%s", comando[i].adj);
    scanf(" em ");
    scanf("%[^\r\n]", comando[i].nome);
    int size = strlen(comando[i].nome);
    if (comando[i].nome[size - 1] == ' ') {
      comando[i].nome[size - 1] = '\0';
    }
  }
  for (int i = 0; i < num_sentencas; i++) { //identifica se uma sentença e positiva ou negativa, cada sentenca é tratada como um produto diferente
    int inversor = -1;
    for (int j = 0; j < 20; j++) { //j percorre todas as palavras de cada produto[i]
      inversor--; //apos cada palavra o tempo de efeito do inversor diminui 1
      for (int k = 0; k < 3; ++k) { 
        if (strcmp(produto[i].vocab[j], inversores[k]) == 0) {//checa se a palavra e um inversor
          inversor = 3;                                       //caso seja so exerce sua funçao caso
          break;                                              //um adjetivo seja encontrado em ate 3 posiçoes adiante
        }
      }
      for (int k = 0; k < 12; k++) {
        if (strcmp(produto[i].vocab[j], positivos[k]) == 0) {
          if (inversor >= 0) {
            produto[i].negativo++;
          } else {
            produto[i].positivo++;
          }

          j = 20;
          break;
        }
        if (strcmp(produto[i].vocab[j], negativos[k]) == 0) {
          if (inversor >= 0) {
            produto[i].positivo++;
          } else {
            produto[i].negativo++;
          }
          j = 20;
          break;
        }
      }
    }
  }
  for (int i = 0; i < num_perguntas; i++) { //testa para todas as perguntas  
    for (int j = 0; j < num_sentencas; j++) { //todas as sentenças
      if (strcmp(comando[i].nome, produto[j].nome) == 0) { //caso o produto da sentença seja igual ao da pergunta
        for (int k = 0; k < 20; k++) { // testa todo vocabulario desse produto com a palavra a ser procurada    
          if (strcmp(comando[i].adj, "negativos") == 0 || strcmp(comando[i].adj, "positivos") == 0) { //caso especial de negativos e positivos
            total++; //primeiro descobre a soma total das palavras positivas e negativas
            if (strcmp(comando[i].adj, "negativos") == 0) { //caso procure pela % de negativos o resultado é incrementado
              resultado[i] += produto[j].negativo; //apenas nos negativos
            }
            if (strcmp(comando[i].adj, "positivos") == 0) { //caso procure por % de positivos o resultado é incrementado
              resultado[i] += produto[j].positivo; //apenas nos positivos
              //printf("%d ",j);
            }
            break;
          }
          if (strcmp(comando[i].adj, produto[j].vocab[k]) == 0) {
            resultado[i] += produto[j].qtd[k];
          }
        }
      }
    }
    if (strcmp(comando[i].adj, "negativos") == 0 || strcmp(comando[i].adj, "positivos") == 0) {
      printf("%.1f", resultado[i] / total * 100); //nos casos especiais o resultado,que e o quantidade de positivos ou negativos
      printf("%%\n"); //e dividido pela soma total destes e sendo imprimindo como porcentagem
    } else {
      printf("%.0f\n", resultado[i]); //em casos normais apenas imprime o resultado
    }
    total = 0; //zera o total para nao interferir no proximo caso especial
  }
  free(produto);
}