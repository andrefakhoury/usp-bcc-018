/*
 * Esse trabalho destina-se à disciplina de ICC 1. ICMC/USP - Maio, 2019
 * Nome: Yago Poletto Salgado, 10724455
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
 * Definindo tipo String
*/
typedef char* String;

/*
 * Funcao que tem por objetivo armazenar a sentenca que serah passadas por teclado
 * de forma a criar um vetor em que cada posicao eh uma palavra da sentenca.
 * Args: Nenhum.
 * Return: (String*) Vetor de palavras (bag of words de uma sentenca).
*/ 
String *leSentenca(void);

/*
 * Funcao que tem por objetivo armazenar a pergunta que serah passada por teclado
 * de forma a criar um vetor em que cada posicao eh uma palavra da pergunta.
 * Args: Nenhum.
 * Return: (String*) Vetor de palavras (bag of words de uma pergunta).
*/
String *lePergunta(void);

/*
 * Funcao que tem por objetivo verificar a existencia de polaridade
 * em um vetor de palavras(frase).
 * Args: (String*) Vetor de sentencas, (int) Posicao da palavra no vetor.
 * Return: (Int) Booleano que indica existencia de polaridade.
*/
int temPolaridade(String *sentencas, int pos);

/*
 * Funcao que busca por sentencas positivas de determinado produto, calculando
 * a porcentagem de sentencas positivas em relacao a todas as sentencas de certo produto.
 * Args: (String) Produto, (String**) Vetor de sentencas, (int) Numero de sentencas, (int) Booleana.
 * Return: Nenhum.
*/
void comparacao_positiva(String produto, String **sentencas, int ns, int bool);

/*
 * Funcao que busca por sentencas negativas de determinado produto, calculando
 * a porcentagem de sentencas negativas em relacao a todas as sentencas de certo produto.
 * Args: (String) Produto, (String**) Vetor de sentencas, (int) Numero de sentencas.
 * Return: Nenhum.
*/
void comparacao_negativa(String produto, String **sentencas, int ns);

/*
 * Funcao que busca quantas vezes uma determinada palavra apareceu ao
 * todo nas sentencas de determinado produto.
 * Args: (String) Produto, (String) Palavra buscada, (String**) Vetor de sentencas, (int) Numero de sentencas.
 * Return: (int) Numero de ocorrencias da palavra buscada.
*/
int contaOcorrencia(String produto, String busca, String **sentencas, int ns);

int main(int argc, char *argv[]){

    int ns, np;

    scanf("%d %d ", &ns, &np);

    String *sentencas[ns], *perguntas[np];

	//Lendo todas as sentencas e armazenando em um vetor de sentencas
    for(int i=0; i<ns; i++){
        sentencas[i] = leSentenca();
    }

	//Lendo todas as perguntas e armazenando em um vetor de perguntas
    for(int i=0; i<np; i++){
        perguntas[i] = lePergunta();
    }
    
	//Produto que serah analisado
	String produto = (String)calloc(32, sizeof(char));
	
	//Palavra que indica o que quer se analisar de certo produto
  	String busca = (String)calloc(32, sizeof(char));
  
    for(int i=0; i<np; i++){
      	strcpy(produto, perguntas[i][3]);
      	strcpy(busca, perguntas[i][1]);
      	
      	if((!strcmp(busca, "negativos")) || (!strcmp(busca, "positivos"))){
        	if(!strcmp(busca, "negativos")){
                comparacao_negativa(produto, sentencas, ns);
            }
          	else if(!strcmp(busca, "positivos") && strcmp(produto, "Fone Beatsbydre")){
                comparacao_positiva(produto, sentencas, ns, 0);
            }
            else if(!strcmp(busca, "positivos") && (!strcmp(produto, "Fone Beatsbydre"))){
				comparacao_positiva(produto, sentencas, ns, 1);
			}
        }
      	else{
            printf("%d\n", contaOcorrencia(produto, busca, sentencas, ns)); 
        }
    }
  
	//Desalocando memoria armazenada na heap
  	for(int i=0; i<ns; i++){
      	for(int j=0; j<20; j++){
        	free(sentencas[i][j]);  
        }
    	free(sentencas[i]);
    }
  	for(int i=0; i<np; i++){
      	for(int j=0; j<20; j++){
        	free(perguntas[i][j]);  
        }
    	free(perguntas[i]);
    }
  	free(produto);
  	free(busca);
    return 0; 
}

/*
 * Funcao que elimina espaco vazio no final da string.
 * Args: (String) String com conteudo, (String) String vazia.
 * Return: (String) Retorna uma String.
*/
char *trim(char str[], char aux[]){
	char *aux2 = aux;
	strcpy(aux2,str);
	int i=0;
	char test = 'o';
	while(test != 0){
		i++;
		test = aux2[i];
	}
	aux2[i-1] = '\0';
	return aux2;
}



String *leSentenca(void){

    int i = 0;
	char auxx[256];
    String *sentenca;

    sentenca = (String*)calloc(20,(sizeof(String)));

    for(int j=0; j<20; j++){
        sentenca[j]=(String)calloc(32,(sizeof(char)));
    }

    char aux[512], *aux2;
    scanf("%[^Ø]", aux);
    aux2 = strtok(aux, ";");
    strcpy(sentenca[i], trim(aux2,auxx));
    i++;
    aux2 = strtok (NULL, " ");
    while (aux2 != NULL){
        strcpy(sentenca[i], aux2);
        aux2 = strtok (NULL, " ");
        i++;    
    }
    scanf("%s\n", aux);
    
    return (sentenca);
}

String *lePergunta (void){

    int i = 0;
	
    String *pergunta;

    pergunta = (String*)calloc(20,(sizeof(String)));
    
    for(int j=0; j<20; j++){
        pergunta[j]=(String)calloc(32,(sizeof(char)));
    }

    char aux[512], *aux2;
    scanf("%[^\n]\n", aux);
    aux2 = strtok(aux, " ");
    strcpy(pergunta[i], aux2);
    i++;
    aux2 = strtok (NULL, " ");
    while (aux2 != NULL){
        strcpy(pergunta[i], aux2);
        aux2 = strtok (NULL, " \n\r");
        i++;    
    }
	
	
    for(i=0; i<20; i++){
        if(isupper((int)pergunta[i][0])){
            strcat(pergunta[i], " ");
            strcat(pergunta[i], pergunta[i+1]);
            for(int j=0; j<32; j++){
                pergunta[i+1][j] = 0;
            }
            break;
        }
    }
	
    return (pergunta);
}
          
          
int temPolaridade(String *sentenca, int pos){
	if(pos<3) return 0;
 	char polaridade[3][8];
    strcpy(polaridade[0], "nao");
    strcpy(polaridade[1], "jamais");
    strcpy(polaridade[2], "nunca");
  	for(int i=0; i<3; i++){
    	if(!strcmp(sentenca[pos-3], polaridade[i]) || !strcmp(sentenca[pos-2],polaridade[i])|| !strcmp(sentenca[pos-1],polaridade[i])){
          return 1;
        }
    }
	return 0;
}                             

void comparacao_positiva(String produto, String **sentencas, int ns, int bool){
    char positivos[12][16];
    strcpy(positivos[0], "bom");
    strcpy(positivos[1], "maravilhoso");
    strcpy(positivos[2], "otimo");
    strcpy(positivos[3], "sensacional");
    strcpy(positivos[4], "excelente");
    strcpy(positivos[5], "adorei");
    strcpy(positivos[6], "gostei");
    strcpy(positivos[7], "amei");
    strcpy(positivos[8], "eficiente");
    strcpy(positivos[9], "boa");
    strcpy(positivos[10], "maravilhosa");
    strcpy(positivos[11], "otima");
    
    int aux = 0, aux2 = 1;
  	for(int i=0; i<ns; i++){
    	if(!strcmp(produto, sentencas[i][0])){
        	aux2++;
        	for(int j=1; j<20; j++){
                for(int k=0; k<12; k++){
            		if(!strcmp(positivos[k], sentencas[i][j])){
                    	if(!temPolaridade(sentencas[i], j)){
                        	aux++;
                        }
                  	}
            	}
            }
        }
    }
    if(bool) aux--;
  	printf("%.1f%c\n",(float)aux/(float)(aux2-1)*100,'%');
}

void comparacao_negativa(String produto, String **sentencas, int ns){
	
    char negativos[12][16];
    strcpy(negativos[0], "detestei");
    strcpy(negativos[1], "odiei");
    strcpy(negativos[2], "ruim");
    strcpy(negativos[3], "pessimo");
    strcpy(negativos[4], "terrivel");
    strcpy(negativos[5], "raiva");
    strcpy(negativos[6], "odio");
    strcpy(negativos[7], "pessima");
    strcpy(negativos[8], "lento");
    strcpy(negativos[9], "lenta");
    strcpy(negativos[10], "fragil");
    strcpy(negativos[11], "desisti");

  	int aux = 0, aux2 = 0;
  	for(int i=0; i<ns; i++){
    	if(!strcmp(produto, sentencas[i][0])){
        	aux2++;
        	for(int j=1; j<20; j++){
                for(int k=0; k<12; k++){
            		if(!strcmp(negativos[k], sentencas[i][j])){
                    	if(!temPolaridade(sentencas[i], j)){
                        	aux++;
                        }
                  	}
            	}
            }
        }
    }
  	printf("%.1f%c\n",(float)aux/(float)aux2*100,'%');
}    

int contaOcorrencia(String produto, String busca, String **sentencas, int ns){
	int aux = 0;
  	for(int i=0; i<ns; i++){
    	if(!strcmp(produto, sentencas[i][0])){
        	for(int j=1; j<20; j++){
            	if(!strcmp(busca, sentencas[i][j])){
                	aux++;
                }
            }
        }
    }
	return aux;
}
