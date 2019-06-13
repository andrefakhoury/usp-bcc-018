#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {

int f,p,i,j,quantidade=0; /*f: número de frases; p: número de perguntas; quantidade: conta a quantidade de resultados durante a busca por palavras*/
float quantidadeb = 0,quantidader = 0,porcentagem;/*quantidadeb: conta o número de comentários positivos; quantidader: conta o número de comentários negativos; porcentagem: porcentagem de comentários negativos \
ou positivos*/
char* end;

 scanf(" %d%d", &f,&p); //leitura dos números de frases de perguntas inseridos pelo usuário

char frase[f][600]; //armazena os comentários
char pergunta[p][5][20]; //armazena as perguntas

char produto[f][20];//armazena o tipo do produto
char produto2[f][20];//armazena a marca do produto

for(i = 0; i<f ; i++){ //leitura dos produtos e comentários inseridos
 scanf(" %s", produto[i]);
 scanf(" %s", produto2[i]);
 scanf(" %[^\n\r]", frase[i]);
}

for (int i = 0; i < p; i++) {//leitura das perguntas
 for (int j = 0; j < 5; j++) {
  scanf(" %s", pergunta[i][j]);
 }
}


 for(i = 0; i<p ;i++){ //analisa os comentários de acordo com o conteúdo de cada pergunta
 for(j = 0;j<f;j++){
   if(strcmp(produto[j], pergunta[i][3]) == 0){//procura pelo tipo do produto no comentário
     if(strcmp(produto2[j], pergunta[i][4]) == 0){//procura pela marca do produto no comentário

    end = frase[j];

    while(strstr(end,pergunta[i][1]) != NULL){ //realiza a contagem do número de vezes que a palavra requisitada aparece em cada comentário
     quantidade++;
     if(*(strstr(end,pergunta[i][1]) + strlen(pergunta[i][1])) == 's'){ //exclui palavras no plural do resultado final da busca
       quantidade--;
      }
      end = strstr(end,pergunta[i][1]) + strlen(pergunta[i][1]);
     }

//as próximas linhas procuram por comentários positivos

    while((strstr(frase[j], "bom") != NULL)||(strstr(frase[j], "maravilhoso")!= NULL)||(strstr(frase[j], "otimo")!= NULL)||(strstr(frase[j], "sensacional")!= NULL)||(strstr(frase[j], "excelente")!= NULL)||(strs\
tr(frase[j], "adorei")!= NULL)||(strstr(frase[j], "gostei")!= NULL)||(strstr(frase[j], "amei")!= NULL)||(strstr(frase[j], "eficiente")!= NULL)||(strstr(frase[j], "boa")!= NULL)||(strstr(frase[j], "maravilhosa")\
!= NULL)||(strstr(frase[j], "otima")!= NULL)){
     quantidadeb++;
     break;
    }

//as próximas linhas procuram por comentários negativos

    while((strstr(frase[j], "detestei") != NULL)||(strstr(frase[j], "odiei")!= NULL)||(strstr(frase[j], "ruim")!= NULL)||(strstr(frase[j], "pessimo")!= NULL)||(strstr(frase[j], "terrivel")!= NULL)||(strstr(fras\
e[j], "raiva")!= NULL)||(strstr(frase[j], "odio")!= NULL)||(strstr(frase[j], "pessima")!= NULL)||(strstr(frase[j], "lento")!= NULL)||(strstr(frase[j], "lenta")!= NULL)||(strstr(frase[j], "fragil")!= NULL)||(str\
str(frase[j], "desisti")!= NULL)){
     quantidader++;
     break;
    }


   }
  }
 }

 if(strcmp(pergunta[i][0], "palavra") == 0){ //imprime a quantidade de vezes que a palavra requisitada foi encontrada
  printf("%d\n", quantidade);
 }
 if(strcmp(pergunta[i][0], "quantos") == 0){
   if(strcmp(pergunta[i][1], "negativos") == 0){//imprime a porcentagem de comentários negativos
   porcentagem = (quantidader / (quantidadeb + quantidader)*100);
   printf("%.1f%%\n", porcentagem);
  }
   if(strcmp(pergunta[i][1], "positivos") == 0){//imprime a porcentagem de comentários positivos
   porcentagem = (quantidadeb / (quantidadeb + quantidader)*100);
   printf("%.1f%%\n", porcentagem);
  }
 }

//valores contidos nas variáveis são zerados para ser feita a análise da próxima pergunta
 quantidade = 0;
 quantidadeb = 0;
 quantidader = 0;
 porcentagem = 0;

}

return 0;
}