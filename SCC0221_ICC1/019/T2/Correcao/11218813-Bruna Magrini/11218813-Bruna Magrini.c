#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_MAXIMO_PALAVRA 20
#define TAMANHO_MAXIMO_FRASE 381
#define QUANTIDADE_ADJETIVOS 24
#define QUANTIDADE_ADVERBIOS 3

typedef struct _item {
  char nome[TAMANHO_MAXIMO_PALAVRA * 2]; //Nome do item
  int quantidade_de_comentarios; //Armazena a quantidade de comentarios sobre um item
  int quantidade_de_palavras; //Armazena a quantidade de palavras digitadas em todos comentarios 
  char **comentarios; //Armazena cada palavra digitadas sobre um item nos comentarios
  int *quantidade_de_positivos_negativos; //Armazena a quantidade de comentarios positivos e negativos de um item
} info_item;

void montar_item(char item[40], char produto[TAMANHO_MAXIMO_PALAVRA], char marca[TAMANHO_MAXIMO_PALAVRA]);
int recuperar_item(int quantidade_de_itens, info_item *lista_de_itens, char *item);
int recuperar_adjetivo(char adjetivos[QUANTIDADE_ADJETIVOS][12], char palavra[TAMANHO_MAXIMO_PALAVRA]);
void novo_item(int *quantidade_de_itens, info_item **lista_de_itens, int indice_item, char item[TAMANHO_MAXIMO_PALAVRA * 2]);
int ler_armazenar_item(int *quantidade_de_itens, info_item **lista_de_itens);
int e_adverbio(char adverbios[QUANTIDADE_ADVERBIOS][7], char palavra[TAMANHO_MAXIMO_PALAVRA]);
void ler_gerenciar_comentario(info_item *lista_de_itens, int indice_item, char adjetivos[QUANTIDADE_ADJETIVOS][12], char adverbios[QUANTIDADE_ADVERBIOS][7]);
float quantidade_de_feedback(char palavra_procurada[TAMANHO_MAXIMO_PALAVRA], int indice_do_item, int* quantidade_de_positivos_negativos);
void ler_pergunta(char item[TAMANHO_MAXIMO_PALAVRA * 2], char tipo_de_pergunta[8], char palavra_procurada[TAMANHO_MAXIMO_PALAVRA]);
int procurar_por_palavra(info_item *lista_de_itens, int indice_item, char palavra_procurada[TAMANHO_MAXIMO_PALAVRA]);
float calcular_porcentagem(info_item *lista_de_itens, int indice_item, char palavra_procurada[TAMANHO_MAXIMO_PALAVRA]);
void executar_pergunta(int quantidade_de_itens, info_item *lista_de_itens, char item[TAMANHO_MAXIMO_PALAVRA * 2], char tipo_de_pergunta[8], char palavra_procurada[TAMANHO_MAXIMO_PALAVRA]);

//Dado um "produto" e uma "marca", é construido uma string com valor "produto marca"
void montar_item(char item[40], char produto[TAMANHO_MAXIMO_PALAVRA], char marca[TAMANHO_MAXIMO_PALAVRA]) {
  strcpy(item, "");
  strcat(item, produto);
  strcat(item, " ");
  strcat(item, marca);
  strcat(item, "\0");
}

//Essa função percorre a lista de itens para saber se um determinado item já foi inserido. Se estiver, retorna o indice
int recuperar_item(int quantidade_de_itens, info_item *lista_de_itens, char *item){
  int i;
  for(i = 0; i < quantidade_de_itens; i++) 
    if(strcmp(item, lista_de_itens[i].nome) == 0)
      return i;
  return -1;
}

//Na matriz que lista todos os adjetivos, a função verifica se uma palavra é um adjetivo e se for, retorna o indice
int recuperar_adjetivo(char adjetivos[QUANTIDADE_ADJETIVOS][12], char palavra[TAMANHO_MAXIMO_PALAVRA]) {
  int i;
  for(i = 0; i < QUANTIDADE_ADJETIVOS; i++) 
    if(strcmp(adjetivos[i], palavra) == 0)
      return i;
  return -1;
}

//Função responsável por criar novo item e inicializar valores deste item
void novo_item(int *quantidade_de_itens, info_item **lista_de_itens, int indice_item, char item[TAMANHO_MAXIMO_PALAVRA * 2]) {
  (*lista_de_itens) = (info_item *) realloc ((*lista_de_itens), sizeof(info_item) * ((*quantidade_de_itens) + 1));

  strcpy((*lista_de_itens)[indice_item].nome, item);
  (*lista_de_itens)[indice_item].quantidade_de_comentarios = 0;
  (*lista_de_itens)[indice_item].quantidade_de_positivos_negativos = (int *) calloc (2, sizeof(int)); //Uma posição para positivo e uma para negativo
    
  (*quantidade_de_itens) = (*quantidade_de_itens) + 1;
}

//Função responsável por ler o produto e marca, e alocar memória caso for um novo item não adicionado na lista antes
int ler_armazenar_item(int *quantidade_de_itens, info_item **lista_de_itens) {
  int indice_item;

  char palavra1[TAMANHO_MAXIMO_PALAVRA];
  char palavra2[TAMANHO_MAXIMO_PALAVRA];
  char item[TAMANHO_MAXIMO_PALAVRA * 2];

  scanf("%s", palavra1); 
  scanf("%s", palavra2); 
  montar_item(item, palavra1, palavra2);

  indice_item = recuperar_item(*quantidade_de_itens, (*lista_de_itens), item);
  if(indice_item < 0) { 
    indice_item = *quantidade_de_itens;
    novo_item(quantidade_de_itens, lista_de_itens, indice_item, item);
  } 

  //Adicionando mais um na contagem de comentarios sobre o produto
  (*lista_de_itens)[indice_item].quantidade_de_comentarios++;

  return indice_item;
}

//Função responsavel por checar se palavra é adverbio
int e_adverbio(char adverbios[QUANTIDADE_ADVERBIOS][7], char palavra[TAMANHO_MAXIMO_PALAVRA]) {
  int i;
  for(i = 0; i < QUANTIDADE_ADVERBIOS; i++) 
    if(strcmp(adverbios[i], palavra) == 0)
      return i;
  return -1;
}

//Função responsável por ler os comentários e contabilizar suas informações
void ler_gerenciar_comentario(info_item *lista_de_itens, int indice_item, char adjetivos[QUANTIDADE_ADJETIVOS][12], char adverbios[QUANTIDADE_ADVERBIOS][7]) {
  int teve_comentario_positivo = 0;
  int quantidade_de_palavras = lista_de_itens[indice_item].quantidade_de_palavras;
  int adverbio = -1, indice_adjetivo = 0;

  char frase[TAMANHO_MAXIMO_FRASE];

  fgets(frase, TAMANHO_MAXIMO_FRASE, stdin);
  memcpy(frase, &frase[1], strlen(frase) - 1); 

  char *token; 
  token = strtok (frase, " ");  //Pegando cada valor, separado por espaço, individualmente. É discartado pois refere-se a " ; "
  token = strtok (NULL, " ");
  while (token != NULL) { 
    strcat(token, "\0");
    if(token[strlen(token)-2] == '\n') //Limpando variavel
      token[strlen(token)-2] = '\0';

    //Construindo lista de cada palavra sobre um mesmo produto
    lista_de_itens[indice_item].comentarios = (char **) realloc (lista_de_itens[indice_item].comentarios, sizeof(char *) * (quantidade_de_palavras + 1));
    lista_de_itens[indice_item].comentarios[quantidade_de_palavras] = (char *) malloc (sizeof(char) * (strlen(token)));
    strcpy(lista_de_itens[indice_item].comentarios[quantidade_de_palavras], token);

    indice_adjetivo = recuperar_adjetivo(adjetivos, token);
    if(indice_adjetivo >= 0 && indice_adjetivo < 12) 
      teve_comentario_positivo = 1;

    if(adverbio == (-1)) {
      adverbio = e_adverbio(adverbios, token);
      if(adverbio > (-1)) 
        adverbio = quantidade_de_palavras;
    } else {
        if(quantidade_de_palavras - adverbio > 3) 
          adverbio = -1;
        else {
          if(indice_adjetivo >= 0 && indice_adjetivo < 24) {
            if(teve_comentario_positivo) 
              teve_comentario_positivo = 0;
            else
              teve_comentario_positivo = 1;
            }
        }
    }

    quantidade_de_palavras++;
    token = strtok (NULL, " ");
	}

  //Atualizando contabilidade de comentário
  if(teve_comentario_positivo) 
    lista_de_itens[indice_item].quantidade_de_positivos_negativos[0]++;
  else
    lista_de_itens[indice_item].quantidade_de_positivos_negativos[1]++;

  //Atualizando quantidade de palavras
  lista_de_itens[indice_item].quantidade_de_palavras = quantidade_de_palavras;
}

//Função responsável por retornar quantidade de comentários de um tipo (positivo/negativo)
float quantidade_de_feedback(char palavra_procurada[TAMANHO_MAXIMO_PALAVRA], int indice_do_item, int* quantidade_de_positivos_negativos) {
  if(strcmp(palavra_procurada, "positivos") == 0) 
    return (float) quantidade_de_positivos_negativos[0];
  else 
    return (float) quantidade_de_positivos_negativos[1];
} 

//Função responsável por ler as perguntas e montar o item
void ler_pergunta(char item[TAMANHO_MAXIMO_PALAVRA * 2], char tipo_de_pergunta[8], char palavra_procurada[TAMANHO_MAXIMO_PALAVRA]) {
  char palavra1[TAMANHO_MAXIMO_PALAVRA];
  char palavra2[TAMANHO_MAXIMO_PALAVRA];

  scanf("%s", tipo_de_pergunta);
  scanf("%s", palavra_procurada);
  scanf("%s", palavra1); //Palavra 'em' descartavel
  scanf("%s", palavra1);
  scanf("%s", palavra2);

  montar_item(item, palavra1, palavra2);
}

//Função responsável por contabilizar as aparições de uma determinada palavra
int procurar_por_palavra(info_item *lista_de_itens, int indice_item, char palavra_procurada[TAMANHO_MAXIMO_PALAVRA]) {
  int i, contador_de_aparicoes = 0;

  for(i = 0; i < lista_de_itens[indice_item].quantidade_de_palavras; i++)
    if(strcmp(lista_de_itens[indice_item].comentarios[i], palavra_procurada) == 0)
      contador_de_aparicoes++;

  return contador_de_aparicoes;
}

//Função responsável por calcular porcentagem de palavras positivas ou negativas
float calcular_porcentagem(info_item *lista_de_itens, int indice_item, char palavra_procurada[TAMANHO_MAXIMO_PALAVRA]) {
  //Pois (feedback * 100 / quantidade total de comentarios) = porcentagem
  return ((quantidade_de_feedback(palavra_procurada, indice_item, lista_de_itens[indice_item].quantidade_de_positivos_negativos) * 100) / lista_de_itens[indice_item].quantidade_de_comentarios); 
}

//Função responsável por verificar o tipo de perguntar e executar função correspondente
void executar_pergunta(int quantidade_de_itens, info_item *lista_de_itens, char item[TAMANHO_MAXIMO_PALAVRA * 2], char tipo_de_pergunta[8], char palavra_procurada[TAMANHO_MAXIMO_PALAVRA]) {
  int indice_item;

  indice_item = recuperar_item(quantidade_de_itens, lista_de_itens, item);
  if(strcmp(tipo_de_pergunta, "palavra") == 0)  //Pegando quantidade de aparição de uma palavra
    printf("%d\n", procurar_por_palavra(lista_de_itens, indice_item, palavra_procurada));
  else 
    printf("%.1f%%\n", calcular_porcentagem(lista_de_itens, indice_item, palavra_procurada));
}

//Função responsavel por liberar memória reservada
void liberar_memoria(int quantidade_de_itens, info_item *lista_de_itens) {
  int i, j;

  for(i = 0; i < quantidade_de_itens; i++) {
    for(j = 0; j < lista_de_itens[i].quantidade_de_palavras; j++){
      //free(lista_de_itens[i].comentarios[j]);
    }
    free(lista_de_itens[i].comentarios);

    free(lista_de_itens[i].quantidade_de_positivos_negativos);
  }

  free(lista_de_itens);
}

int main(void) {
  char adjetivos[QUANTIDADE_ADJETIVOS][12] = {
                            {"bom\0"}, 
                            {"maravilhoso\0"}, 
                            {"otimo\0"}, 
                            {"sensacional\0"}, 
                            {"excelente\0"}, 
                            {"adorei\0"}, 
                            {"gostei\0"}, 
                            {"amei\0"}, 
                            {"eficiente\0"}, 
                            {"boa\0"}, 
                            {"maravilhosa\0"},
                            {"otima\0"},
                            {"detestei\0"}, 
                            {"odiei\0"}, 
                            {"ruim\0"}, 
                            {"pessimo\0"},
                            {"terrivel\0"},
                            {"raiva\0"}, 
                            {"odio\0"}, 
                            {"pessima\0"}, 
                            {"lento\0"}, 
                            {"lenta\0"}, 
                            {"fragil\0"}, 
                            {"desisti\0"}
                          };

  char adverbios[QUANTIDADE_ADVERBIOS][7] = {
                          {"nao\0"}, 
                          {"jamais\0"}, 
                          {"nunca\0"}
                        }; 

  int i;
  int quantidade_de_sentencas, quantidade_de_perguntas;

  int indice_item, quantidade_de_itens = 0;

  info_item *lista_de_itens = NULL;

  scanf("%d %d", &quantidade_de_sentencas, &quantidade_de_perguntas);

  for(i = 0; i < quantidade_de_sentencas; i++) {
    indice_item = ler_armazenar_item(&quantidade_de_itens, &lista_de_itens);
    ler_gerenciar_comentario(lista_de_itens, indice_item, adjetivos, adverbios);
  } 

  char item[TAMANHO_MAXIMO_PALAVRA * 2];
  char tipo_de_pergunta[8];
  char palavra_procurada[TAMANHO_MAXIMO_PALAVRA];

  for(i = 0; i < quantidade_de_perguntas; i++) {
    ler_pergunta(item, tipo_de_pergunta, palavra_procurada);
    executar_pergunta(quantidade_de_itens, lista_de_itens, item, tipo_de_pergunta, palavra_procurada);
  }
  
  liberar_memoria(quantidade_de_itens, lista_de_itens);

  return 0;
}