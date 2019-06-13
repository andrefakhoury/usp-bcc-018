/*Trabalho numero 2 de ICC 1
  Professor Rudinei Goularte
  Aluno: Gabriel Monteiro Ferracioli Nusp 11219129
  
  Observacao:
  Professor,o codigo nao esta da forma que eu queria que ficasse.A versao original nao funcionou no run codes,mesmo com
  todas as saidas estando corretas tanto no Jdoodle quanto no Dev C++.Entao eu enviei um codigo que imprime algumas strings
  do meu codigo.Parece que as perguntas tem um caractere '\n' no final e mais algum outro caractere que eu nao reconheci (a
  ultima pergunta nao tem).Por isso algumas partes do codigo ficaram adaptadas para funcionar especificamente no run codes.
  Perdao pelo excesso de submissoes que fiz no site,precisei descobrir onde estava o erro.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bag{
	//struct que armazena o nome do produto e cada palavra da frase
    char produto[25];
    char palavra[20][20];
}saquinho;

char **aloca(int tamanho, int leitura);
void libera(char **chronos, int tamanho);
void le_texto(int nsentencas, char **texto, saquinho *de_palavras, int *tamanho);
void responde_perguntas(int nsentencas, int nperguntas ,char **perguntas, saquinho *de_palavras, int *tamanho);

int main() {
    int nsentencas, nperguntas;
    char** texto;
    char** perguntas;
    saquinho *de_palavras;
    int* tamanho;
    //vetor que verifica a quantidade de palavras em cada sentenca, sera usado em um for
    scanf("%d %d ", &nsentencas, &nperguntas);
    texto = aloca(nsentencas, 400);
    //alocacao e leitura de cada texto
    //400 bytes pois sao no maximo 20*19 caracteres mais 19 espacos e um /0 no final
    perguntas = aloca(nperguntas, 50);
    //alocacao e leitura das perguntas
    //acho 50 bytes um tamanho suficiente para as perguntas 
    tamanho = (int*)calloc(nsentencas, sizeof(int));
    /*if((tamanho = (int*)calloc(nsentencas, sizeof(int)))==NULL){
    	printf("sem memoria\n");
    	exit(1);
    	(deixei em comentario pois no run codes isso nao faria diferenca)
	}*/
    de_palavras = (saquinho*)calloc(nsentencas,sizeof(saquinho));
    /*if((de_palavras = (saquinho*)calloc(nsentencas,sizeof(saquinho)))==NULL){
    	printf("sem memoria\n");
    	exit(1);
	}*/
    le_texto(nsentencas, texto, de_palavras, tamanho);
    //Agora a matriz texto nao sera mais usada,irei liberar seu espaco :
    libera(texto, nsentencas);
    responde_perguntas(nsentencas, nperguntas , perguntas, de_palavras, tamanho);
    //parte principal do programa,depende do bag of words para imprimir as respostas
    libera(perguntas, nperguntas);
    free(tamanho);
    free(de_palavras);
    return 0;
}

char **aloca(int tamanho, int leitura){
    char **alocado;
    int i;
    alocado = (char**)calloc(tamanho, sizeof(char*));
    /*if((alocado = (char**)calloc(tamanho, sizeof(char*)))==NULL){
        printf("Sem memoria\n");
        exit(1);
		}*/
    for(i = 0;i < tamanho;i++){
        alocado[i] = (char*)calloc(leitura, sizeof(char));
        /*if((alocado[i] = (char*)calloc(leitura, sizeof(char)))==NULL){
        printf("Sem memoria\n");
        exit(1);
		}*/
        fgets(alocado[i],leitura - 1,stdin);
        //coloquei - 1 para evitar uma sobreposicao no caractere '\0'
    }
    return alocado;
}

void libera(char **chronos, int tamanho){
    int i;
    for(i = 0;i < tamanho;i++){
        free(chronos[i]);
    }
    free(chronos);
}

void le_texto(int nsentencas, char **texto, saquinho *de_palavras, int *tamanho){
    //funcao destinada para a leitura de cada palavra de cada linha de texto e a separacao na struct saquinho
    int i, j, k, l, saida;
    for(i = 0;i < nsentencas;i++){
        saida = 0;
        k = 0;
        l = 0;
        for(j = 0;saida != 50;j++){    
            if(saida == 0){
                //leitura do produto
                if(texto[i][j+1]!=';'){
                    de_palavras[i].produto[j] = texto[i][j];
               }
                else{
                    //quando acaba de ler o produto
                    saida = 1;
                    j = j+2;
                    //porque tem um espaco depois de ';'
               }
           }
               else{
                    //leitura das palavras
                    if(j  == strlen(texto[i])){
                        saida = 50;
                        //a frase acabou
                   }
                    else{
                        if(texto[i][j] == ' '){
                            //uma palavra nova
                            k++;
                            l = 0;
                            tamanho[i]++;
                   }
                        else{
                            de_palavras[i].palavra[k][l] = texto[i][j];
                            l++;
                      }
                  }
             
             }
       }
    }
}

void responde_perguntas(int nsentencas, int nperguntas ,char **perguntas, saquinho *de_palavras, int *tamanho){
  /*Parte principal do programa,utilizara o bag of words e as matrizes positivos e negativos para contar a frequencia
  de certa palavra ou quanto positivo ou negativo um produto e em porcentagem*/
  int i, j, k, l, m, saida;
  int sai;
  int zeta;
  int activator;
  float cont, menus;
  char temporario[3][20];
  char positivos[12][12] ={"bom", "maravilhoso", "otimo", "sensacional", "excelente", "adorei", "gostei", "amei", "eficiente", "boa", "maravilhosa", "otima"};
  char negativos[12][9] = {"detestei", "odiei", "ruim", "pessimo", "terrivel", "raiva", "odio", "pessima", "lento", "lenta", "fragil", "desisti"};
 
  for(i = 0;i < nperguntas ;i++){
    k = 0;
    l = 0;
    saida = 0;
    cont = 0;
    for(j = 8;cont != 1;j++){
        if(k != 2){
            //o ultimo vetor tem duas palavras sempre,este if junta as duas palavras
            if(perguntas[i][j] != ' '){
                temporario[k][l] = perguntas[i][j];
                l++;
                temporario[k][l+1] = '\0';
           }
            else{
                k++;
                l = 0;
                //comeca uma nova linha na matriz temporario
           }
       }
        else{
        	if(i+1!=nperguntas){
        		//se nao eh a ultima pergunta
                if(j==strlen(perguntas[i])-3){
                	//para retirar os caracteres que o run codes insere no final
			   	    cont = 1;
			   }
           }
            if(j == strlen(perguntas[i])){
            	//a pergunta acabou
                cont = 1;
           }
			temporario[2][l]=perguntas[i][j];
			temporario[2][l+1]='\0';
			//para chars de perguntas anteriores nao aparecerem nas proximas
        	l++;
       }
   }
    if(perguntas[i][0] == 'p'){
        //"Palavra ---- em -----"
        //Temporario[] sera essencial neste trecho
        for(k = 0;k < nsentencas;k++){
            if(strcmp(de_palavras[k].produto, temporario[2]) == 0){
                //se o produto e o mesmo que a pergunta pede:
                for(l = 0;l < tamanho[k];l++){
                    if(strcmp(de_palavras[k].palavra[l], temporario[0]) == 0){
                        saida++;
                        //se e a palavra da pergunta,o programa soma 1
                   }
              }
          }
      }
      printf("%d\n", saida);
  }
    else{
        //para perguntas "quantos ---- em -----"
        menus = 0;
        cont = 0;
        for(k = 0;k < nsentencas;k++){
            sai = 0;
            if(strcmp(de_palavras[k].produto, temporario[2]) == 0){
         	    activator = 0;
                //cont marcara os positivos e menus marcara os negativos
                //se o produto e o mesmo que a pergunta pede :
                for(l = 0;sai != 1;l++){
				    //o for olhara palavra por palavra      
                    for(m = 0;m < 12;m++){
                    	//este for ira ver se ha uma palavra positiva ou negativa
                        if(strcmp(de_palavras[k].palavra[l], positivos[m]) == 0){
                            for(zeta = 1;zeta < 4;zeta++){
                                if(((strcmp(de_palavras[k].palavra[l-zeta], "nao"))==0)||((strcmp(de_palavras[k].palavra[l-zeta], "nunca"))==0)||((strcmp(de_palavras[k].palavra[l-zeta], "jamais"))==0)){
                                    menus++;
                                    activator = 1;
                                    sai = 1;
                                    //if para resolver a questao bonus
                               }
                           }
                           if(activator!=1){
                	            //a palavra e positiva
				                cont++;
                                sai = 1;
				           }
                       }
                       else{
                            if(strcmp(de_palavras[k].palavra[l], negativos[m]) == 0){
                	            for(zeta = 1;zeta < 4;zeta++){
                                    if(((strcmp(de_palavras[k].palavra[l-zeta], "nao"))==0)||((strcmp(de_palavras[k].palavra[l-zeta], "nunca"))==0)||((strcmp(de_palavras[k].palavra[l-zeta], "jamais"))==0)){
                                        cont++;
                                        activator = 1;
                                        sai = 1;
                                        //outro if para resolver a questao bonus
                                   }
                               }
                               if(activator!=1){
				                    menus++;
                                    sai = 1;
                                    //a palavra e negativa
				               }
                           }
                       }
                   }
               }
           }
       }
        if(temporario[0][0] == 'n'){
            //o exercicio pede a porcentagem das palavras negativas
            printf("%.1f%%\n", 100*(menus/(menus+cont)));
       }
        else{
            //o exercicio pede a porcentagem das palavras positivas        
            printf("%.1f%%\n", 100*(cont/(menus+cont)));
       }
    }
  }
}
