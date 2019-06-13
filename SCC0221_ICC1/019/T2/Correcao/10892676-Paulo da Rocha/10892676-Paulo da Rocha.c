#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// funçao que aloca os vetores e em seguida le as entradas
void ler_comentario(char*** produto, char**** comentario, int c){
  //aloca dinamicamente os vetores de comentario e produto
  (*produto) = malloc(c*sizeof(char*));
  (*comentario) = malloc(c*sizeof(char**));
  for(int k=0; k<c; k++){
    (*produto)[k] = malloc(45*sizeof(char));
    (*comentario)[k] = malloc(20*sizeof(char*));
    for(int l=0; l<20; l++){
      (*comentario)[k][l] = malloc(20*sizeof(char));
    }
  }


  //le as entadas de produtos e comentario
  for (int i = 0; i < c; i++){
    scanf(" %[^;]", (*produto)[i]);
    (*produto)[i][strlen((*produto)[i])-1] = '\0';
    getchar();
    for(int j=0; j<20; j++){
        scanf(" %s", (*comentario)[i][j]);
      if(strcmp((*comentario)[i][j], "Ø")==0) break;
    }
  }
}

//cria as respostas para as perguntas sobre quantidade de palavras
int conta_palavra(int n_comentario, char* produto_aux, char* palavra_aux,char** produto, char*** comentario){
  int contador_palavras = 0;
  for(int i=0; i<n_comentario; i++){
    if(strcmp(produto[i], produto_aux) == 0){
      for(int j=0; j<20; j++){
        if(strcmp(comentario[i][j], palavra_aux) == 0) contador_palavras++;
        if(strcmp(comentario[i][j], "Ø") == 0) break;
      }
    }
  }
  return contador_palavras;
}

float polaridade(int n_comentario, char* produto_aux, char* palavra_aux,char** produto, char*** comentario){
  //dicionario de palavras boas e ruins
  char ruins[12][12] = {"detestei", "odiei", "ruim", "pessimo", "terrivel", "raiva", "odio", "pessima", "lento", "lenta", "fragil", "desisti"};
  char boas[12][12] = {"bom", "maravilhoso", "otimo", "sensacional", "excelente", "adorei", "gostei", "amei", "eficiente", "boa", "maravilhosa", "otima"};

  int contador_negativos = 0, contador_positivos = 0, contador_comentarios = 0;
  int aux_break = 0; // essa variavel serve para que seja possivel parar dois "for"s aninhados
  float porcentagem = 0;

  for(int i=0; i<n_comentario; i++){
    if(strcmp(produto[i], produto_aux) == 0){
      contador_comentarios++;
      for(int j=0; j<20; j++){
        for(int k=0; k<12; k++){

          //verifica se alguma das palavras é ruim
          if(strcmp(comentario[i][j], ruins[k]) == 0){

            if(j==0) contador_negativos++;
            else{
              //verificador de inversão de sentido
              for(int l = (j-1) , m = 0; m<3 && l>=0; l--, m++){
                if(strcmp(comentario[i][l], "nao")==0 || strcmp(comentario[i][l], "jamais")==0 || strcmp(comentario[i][l], "nunca")==0){
                  contador_positivos++;
                  break;

                }else{
                  if(m==2 || l==0){
                    contador_negativos++;
                    break;
                  }
                }
              }
              aux_break = 1;
              break;
            }
          }else{
            //verifica se alguma das palavras é boa
            if(strcmp(comentario[i][j], boas[k]) == 0){
              if(j==0) contador_positivos++;
              else{
                //verificador de inversão de sentido
                for(int l = (j-1) , m = 0; m<3 && l>=0; l--, m++){
                  if(strcmp(comentario[i][l], "nao")==0 || strcmp(comentario[i][l], "jamais")==0 || strcmp(comentario[i][l], "nunca")==0){
                    contador_negativos++;
                    break;
                  }else{
                    if(m==2 || l==0){
                      contador_positivos++;
                      break;
                    }
                  }
                }
                aux_break = 1;
                break;
              }
            }
          }
        }
        if(aux_break){
          aux_break = 0;
          break;
        }

        if(strcmp(comentario[i][j], "Ø") == 0) break;
      }
    }
  }
  // calcula as porcentagens
  if(strcmp(palavra_aux, "negativos") == 0){
  porcentagem = ((float)contador_negativos/(float)contador_comentarios)*100;
  }else{
    porcentagem = ((float)contador_positivos/(float)contador_comentarios)*100;
  }

  return porcentagem;
}



int main(void){
  int n_comentario=0, n_perguntas=0;
  char ***comentario;
  char **produto;


  scanf("%d %d", &n_comentario, &n_perguntas);

 ler_comentario(&produto, &comentario, n_comentario);

  //auxiliares de perguntas
  char opcao_aux[8];
  char palavra_aux[20];
  char produto_aux[45];

  // le as perguntas, e gera as resposatas
  for(int y=0; y<n_perguntas; y++){
    scanf(" %s %s %*s %[^\r]", opcao_aux, palavra_aux, produto_aux);

    //responde as perguntas que começam com "palavra"
    if(strcmp(opcao_aux, "palavra") == 0){
      printf("%d\n", conta_palavra(n_comentario, produto_aux, palavra_aux, produto, comentario));
    }else{
      //cria as respostas para o caso de porcentagem de positivos ou negativospa
      if((strcmp(opcao_aux, "quantos") == 0)){
        printf("%.1f%%\n", polaridade(n_comentario, produto_aux, palavra_aux, produto, comentario));
      }
    }
  }

//libera os vetores alocados
  for(int i=0; i<n_comentario; i++){
    free(produto[i]);
  }
  free(produto);

  for(int i=0; i<n_comentario; i++){
    for(int k=0; k<20; k++){
      free(comentario[i][k]);
    }
    free(comentario[i]);
  }
  free(comentario);

  return 0;
}
