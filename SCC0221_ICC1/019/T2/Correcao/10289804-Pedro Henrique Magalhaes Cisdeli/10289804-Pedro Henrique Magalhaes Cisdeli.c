#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Aluno: Pedro Henrique Magalhães Cisdeli
    NUSP: 10289804
    Professor: 	Moacir Antonelli Ponti
    Turma: BCC-B
*/

/*
 Arrays de strings que contêm os dados necessários para comparação de palavras
 positivas, negativas e, para o bônus, adjuntos adverbiais de negação.
*/
char *cPos[12] = {"bom",       "maravilhoso", "otimo",       "sensacional",
                  "excelente", "adorei",      "gostei",      "amei",
                  "eficiente", "boa",         "maravilhosa", "otima"};
char *cNeg[12] = {"detestei", "odiei", "ruim",   "pessimo",
                  "terrivel", "raiva", "odio",   "pessima",
                  "lento",    "lenta", "fragil", "desisti"};
char *cAdv[3] = {"nao", "jamais", "nunca"};

int main() {
  /*
    Declaração de variáveis e alocação de memória HEAP.
  */
  int numeroStr, numeroPerg;
  scanf("%d %d", &numeroStr, &numeroPerg);
  char **sentencas = malloc(numeroStr * sizeof(char *)),
       **perguntas = malloc(numeroPerg * sizeof(char *));

  /*
    Obtenção das sentenças e perguntas utilizando o %m[] como argumento do scanf
    para alocar dinamicamente o espaço na memória adequado, de acordo com a
    entrada do usuário, terminando a leitura na especificação entre os
    colchetes.
  */
  for (int i = 0; i < numeroStr; i++) {
    scanf(" ");
    scanf("%m[^Ø]Ø", &sentencas[i]);
  }
  for (int i = 0; i < numeroPerg; i++) {
    scanf(" ");
    scanf("%m[^\n\r]", &perguntas[i]);
  }

  /*
    Declaração do Bag Of Words(BoW) e de um array bidimensional de strings
    "pSplit" para armazenar as palavras de cada pergunta em uma única matriz.
    Além de uma variável auxiliar que será utilizada para separação das frases e
    um array para armazenar o tamanho máximo de colunas referente a cada linha
    do BoW.
  */
  char *BoW[numeroStr][200], *pSplit[numeroPerg][5];
  int aux, tamBoW[numeroStr];

  /*
    Método utilizado para separação das sentenças e perguntas em palavras.
    Dois nested loops (for e while) foram usados, o mais abrangente (for) para
    percorrer todas sentenças ou perguntas digitadas, enquanto o mais interno
    (while) para efetivamente separar as frases, com auxilio da função strtok.
  */
  for (int i = 0; i < numeroStr; i++) {
    aux = 0;
    char *sAux;
    sAux = strtok(sentencas[i], " ");
    while (sAux != NULL) {
      BoW[i][aux++] = sAux;
      sAux = strtok(NULL, " ");
    }
    tamBoW[i] = aux;
  }
  for (int i = 0; i < numeroPerg; i++) {
    aux = 0;
    char *pAux;
    pAux = strtok(perguntas[i], " ");
    while (pAux != NULL) {
      pSplit[i][aux++] = pAux;
      pAux = strtok(NULL, " ");
    }

    /*
      O loop acima é utilizado tanto para separação das perguntas quanto para o
      processamento do programa, visto que é necessário verificar o elemento 0
      de cada linha da matriz pSplit para determinar qual é o tipo da saída
      calculada.
    */
    if (strcmp(pSplit[i][0], "palavra") == 0) {
      int counter = 0;
      /*
        Loops para fazer as buscas dos nomes dos produtos e palavras no BoW.
        BoW[k][1] - posição no BoW dos nomes dos produtos.
        pSplit[i][4] - posição nas perguntas dos nomes dos produtos.
        pSplit[i][1] - posição nas perguntas da palavra a ser buscada no BoW.
      */
      for (int k = 0; k < numeroStr; k++) {
        if (!strcmp(BoW[k][1], pSplit[i][4])) { // Busca pelo modelo no BoW.
          for (int l = 0; l < tamBoW[k]; l++) {
            if (!strcmp(BoW[k][l], pSplit[i][1])) { // Busca pela palavra no BoW.
              // Soma 1 cada vez que a palavra a ser buscada é encontrada.
              counter++;
            }
          }
        }
      }
      // Gera uma das saídas do programa.
      printf("%d\n", counter);

      // Else para tratamento do caso de pSplit[i][0] for "quantos".
    } else {
      /*
        Declaração de variáveis para formatação da saída, além de auxiliares
        para tratamento dos casos positivos, negativos e adjuntos adverbiais.
        Ademais, os dois primeiros loopings funcionam da mesma maneira
        explicitada acima. Já o terceiro e quarto são utilizados paras as buscas
        nos arrays globais cPos, cNeg e cAdv.
      */
      char p = '%';
      float total = 0;
      int auxPos, auxNeg, auxAdv, qPositivos = 0, qNegativos = 0;
      float porcentagem;
      for (int k = 0; k < numeroStr; k++) {
        auxNeg = auxPos = auxAdv = 0;
        if (!strcmp(BoW[k][1], pSplit[i][4])) { // Busca pelo modelo no BoW.
          total++;
          for (int l = 0; l < tamBoW[k]; l++) {
            for (int j = 0; j < 12; j++) {
              if (!strcmp(BoW[k][l], cPos[j])) { // Busca por uma palavra positiva.
                for (int iAdv = 0; iAdv < 3; iAdv++) {
                  int iterAdv = l;

                  // Loop para verificar se há um adjunto 3 posições antes da palavra positiva.
                  while (iterAdv > l - 4) {
                    if (!strcmp(BoW[k][iterAdv], cAdv[iAdv])) {
                      auxAdv++;
                    }
                    iterAdv--;
                  }
                }
                if (auxAdv == 0) { // Caso não seja encontrada a frase é positiva.
                  auxPos++;
                } else { // Caso seja a frase é negativa.
                  auxNeg++;
                }
            } else if (!strcmp(BoW[k][l], cNeg[j])) { // Busca por uma palavra negativa.
                for (int iAdv = 0; iAdv < 3; iAdv++) {
                  int iterAdv = l;

                  // Loop para verificar se há um adjunto 3 posições antes da palavra negativa.
                  while (iterAdv > l - 4) {
                    if (!strcmp(BoW[k][iterAdv], cAdv[iAdv])) {
                      auxAdv++;
                    }
                    iterAdv--;
                  }
                }
                if (auxAdv == 0) { // Caso não seja encontrada a frase é negativa.
                  auxNeg++;
                } else { // Caso seja a frase é positiva.
                  auxPos++;
                }
              }
            }
          }
          // Caso os auxiliares positivos sejam maiores que os negativos a frase é positiva.
          if (auxPos > auxNeg) {
            qPositivos++;
          } else { // Caso contrário a frase é negativa.
            qNegativos++;
          }
        }
      }

      // Verificação da pergunta para definir a resposta entre quantidade de positivos ou negativos.
      if (!strcmp(pSplit[i][1], "positivos")) {
        porcentagem = (float)(qPositivos / total) * 100;
        printf("%.1f%c\n", porcentagem, p);
      } else {
        porcentagem = (float)(qNegativos / total) * 100;
        printf("%.1f%c\n", porcentagem, p);
      }
    }
  }

  // Liberação da memória HEAP
  for (int i = 0; i < numeroStr; i++) {
    free(sentencas[i]);
  }
  for (int i = 0; i < numeroPerg; i++) {
    free(perguntas[i]);
  }
  free(sentencas);
  free(perguntas);

  return 0;
}
