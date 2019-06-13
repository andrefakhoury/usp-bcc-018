#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {//struct para armazenar o nome do produto ao qual a sentenca se refere e seu respectivo comentario                          
                char produto [380];//armazena o produto com um espaço no final.ex:"Celular LG "
                char comentario [381];//armazena o comentario
        }sentenca;

typedef struct {//struct para armazenar dodos contidos na pergunta  
                char string_pergunta[380];//armazena a string da pergunta inteira
                char palavra[150];//armazena uma possivel palavra que sera procurada entre os comentarios 
                char produto_pergunta[380];//armazena o produto ao qual a pergunta se refere
        }pergunta;



sentenca* aloca_sentencas_heap(int S){//função que aloca as informações das sentencas(S), em um struck sentença na heap
        int i;
        char aux[150];
        sentenca* lista_sentencas=malloc(sizeof(sentenca)*S);//devolve o endereço de uma lista de strucks sentenca criada na heap
        for(i=0;i<S;i++){
                scanf(" %[^;];",lista_sentencas[i].produto);//lê o nome do produto e um espaço no final e armazena na struct
                scanf(" %s",aux);//lê as palavras do comentario até os espaços 
                while(strcmp(aux,"Ø")!=0){//verifica se a string lida não é o criterio de parada
                        strcat(lista_sentencas[i].comentario,aux);//concatena a palavra lida na string de comentarios da struck correspondente
                        strcat(lista_sentencas[i].comentario," ");//concatena um espaço
                        scanf(" %s",aux);//faz a leitura de outra palavra no comentario
                }
        }

        return lista_sentencas;//retorna endereço da lista de strucks sentenca na heap
}

pergunta* aloca_perguntas_heap(int P){//função que aloca a pergunta inteira em "string_pergunta" no struck correspondente
        int i;
        pergunta* lista_perguntas=malloc(sizeof(pergunta)*P);//devolve o endereço de uma lista de strucks pergunta/criada na heap
        for(i=0;i<P;i++){
                scanf(" %[^\n\r]",lista_perguntas[i].string_pergunta);//lê ate o \n
        }
        return lista_perguntas;//retorna endereço da lista de strucks pergunta na heap
}

void encontra_palavra_e_armazena(char* string_perguntas, char*palavra){//funcao que encontra a palavra que sera procurada nos comentarios
        //como toda pergunta inicia como "palavra " sao 8 caracteres ate o primeiro char da palavra procurada entao ela comeca na 8 posição 
        int j=8;
        while(string_perguntas[j]!=' '){
                palavra[j-8]=string_perguntas[j];//armazena carcter por caracter na string"palavra" da struck especifica
                j++;
        }
	palavra[j-8]='\0';
}

void encontra_produto_e_armazena1(char* string_pergunta, int tam_palavra,char* produto_pergunta){//funcao que encontra o produto na pergunta ao qual ela faz referencia
        	int tam_string=strlen(string_pergunta),p;
        for(p=(tam_palavra+12);p<tam_string;p++){
                produto_pergunta[p-(tam_palavra+12)]=string_pergunta[p];/*armazena caracter por caracter na string"produto_pergunta"
na strckt especifica*/
	}
        produto_pergunta[(p-(tam_palavra+12))]=' ';
	produto_pergunta[(p-(tam_palavra+12))+1]='\0';
}


int procura_palavra(char* end_comentario,char* end_palavra){//funcao que contabiliza a quantidade de vezes que a palavra se repete nos comentarios
        int t=0,qtd_palavras=0,tam_comentario=strlen(end_comentario);//calcula o tamanho do comentario
        char string_comparacao[150]="";//array auxiliar para comparar cada palavra do comentario e vê se ela corresponde à palavra procurada
        for(int m=0;m<tam_comentario;m++){//percorre todo o comentario de caracter por caracter
                if(end_comentario[m]!=' '){
                        string_comparacao[t]=end_comentario[m];
                        t++;
                }else{
                        string_comparacao[t]='\0';
                        if(strcmp(string_comparacao,end_palavra)==0){//verifica a palavra com a string auxiliar de comparaçao
                                qtd_palavras++;;//contabiliza a qtd de vezes que a palavra foi achada no cometario
				t=0;//retorna a posiçao 0 da string auxiliar de comparacao
                        }else{
                                t=0;
                         }
                }
        }
        return qtd_palavras;
}
	
int encontra_produto_nas_sentencas1(sentenca* end_sentencas, int S, char* end_produto_pergunta, char* end_palavra){//funcao que encontra o produto da pergunta nas sentencas
        int j,retorno;
        int qtd_palavras=0;//conta quantas vezes a palavra determinada apareceu entre comentarios de um produto especifico
        for(j=0;j<S;j++){
                retorno=strcmp(end_sentencas[j].produto,end_produto_pergunta);//ve se o produto daquela struck sentenca é o mesmo do apontado na pergunta que estamos analisando 
                if(retorno==0){
			qtd_palavras=qtd_palavras+procura_palavra(end_sentencas[j].comentario,end_palavra);
                }
        }
        return qtd_palavras;//retorna quantas palavras daquela foram achadas entre os comentarios do produto pedido
}

char avalia_pergunta(char*pergunta){//funcao que analisa se a pergunta procura por comentarios positivos ou negativos
        char decisao;
	if (pergunta[8]=='p'){
                decisao='p';
        }
        if (pergunta[8]=='n'){
                decisao='n';
        }
	return decisao;
}

void encontra_produto_e_armazena2(char*produto_pergunta,char* string_pergunta, int tam_saltar){//funçao que encontra o produto ao qual a pergunta faz referencia
        int p,tam_string=strlen(string_pergunta);//calcula tamanho da pergunta
        for(p=tam_saltar;p<tam_string;p++){//conjunto de caracteres fixos alem do tamanho da pergunta ate chegar na especificacao do produto
                produto_pergunta[p-(tam_saltar)]=string_pergunta[p];
        }
        produto_pergunta[(p-(tam_saltar))]=' ';//adiciona um espaco no fim por razoes de comparacoes futuras
	produto_pergunta[(p-(tam_saltar))+1]='\0';
}

float porcentagem(float qtd_sentencas,float critica){
	float porcentagem_resultado;
	porcentagem_resultado=(critica*100)/qtd_sentencas;//calculo da porcentagem 
	return porcentagem_resultado;
}

int compara_palavra(char* string_comparacao,char char_aux){
        char matriz_para_comparar[12][12];
        if(char_aux=='p'){//matriz recebe elementos referentes as palavras positivas
		strcpy(matriz_para_comparar[0], "bom");
	        strcpy(matriz_para_comparar[1], "maravilhoso");
	     	strcpy(matriz_para_comparar[2], "otimo");
	    	strcpy(matriz_para_comparar[3], "sensacional");
		strcpy(matriz_para_comparar[4], "excelente");
		strcpy(matriz_para_comparar[5], "adorei");
		strcpy(matriz_para_comparar[6], "gostei");
		strcpy(matriz_para_comparar[7], "amei");
		strcpy(matriz_para_comparar[8], "eficiente");
		strcpy(matriz_para_comparar[9], "boa");
		strcpy(matriz_para_comparar[10], "maravilhosa");
		strcpy(matriz_para_comparar[11], "otima");
	    
		
        }
        if(char_aux=='n'){//matriz recebe elementos referentes as palavras negativas
		strcpy(matriz_para_comparar[0], "detestei");
                strcpy(matriz_para_comparar[1], "odiei");
                strcpy(matriz_para_comparar[2], "ruim");
                strcpy(matriz_para_comparar[3], "pessimo");
                strcpy(matriz_para_comparar[4], "terrivel");
                strcpy(matriz_para_comparar[5], "raiva");
                strcpy(matriz_para_comparar[6], "odio");
                strcpy(matriz_para_comparar[7], "pessima");
                strcpy(matriz_para_comparar[8], "lento");
                strcpy(matriz_para_comparar[9], "lenta");
                strcpy(matriz_para_comparar[10], "fragil");
                strcpy(matriz_para_comparar[11], "desisti");
               
        }
	int retorno2;
        for(int r=0;r<12;r++){//compara a palavra com cada uma da matriz correspondenete
                retorno2=strcmp(string_comparacao,matriz_para_comparar[r]);
                if(retorno2==0){
                        return 0;//retorno caso ache correspondencia
                }
        }
        return -1;//retorno caso nao haja correspondencia 
}


int analisa_comentario(char* end_sentencas_comentario,char char_aux){
	int tam=strlen(end_sentencas_comentario);//verifica tamanho do comentario
        int t=0;
        char string_comparacao[150]="";//array auxiliar para comparar cada palavra do comentario e vê se ela nao corresponde a algum adjetivo da matriz de positivos ou da matriz de negativos
        for(int y=0;y<tam;y++){
        	if(end_sentencas_comentario[y]!=' '){
                	string_comparacao[t]=end_sentencas_comentario[y];
			t++;
                }else{
			string_comparacao[t]='\0';
			if(compara_palavra(string_comparacao,char_aux)==0){//verifica a palavra com as palavras da  matriz correspondenete
				return 0;//caso dê correspondencia de palavras
			}else{
				t=0;
		         }
	        }
	}
	return -1;//caso não ache nenhuma palavra compativel as palavras usuais para negativos ou positivos
}


float encontra_produto_nas_sentencas2(char char_aux,sentenca* end_sentencas, int S, char* end_produto_pergunta){
        int j,retorno;
        float critica=0;//variavel que contabiliza o numero de sentencas positivas ou negativas sobre um produto
        float qtd_sentencas=0;//variavel que contabiliza a quantidade de sentencas relativas ao produto indicado na pergunta
        for(j=0;j<S;j++){
                retorno=strcmp(end_sentencas[j].produto,end_produto_pergunta);//compara o produto da pergunta com o da sentenca em posicao de struck especifica
                if(retorno==0){
                        qtd_sentencas++;
                        if(analisa_comentario(end_sentencas[j].comentario,char_aux)==0){//se estao falando do mesmo produto, chama a funcao que analisa o comentario referente a ele no struck sentenca especifico
                                critica++;
                        }
                }
        }
        return porcentagem(qtd_sentencas,critica);
}


int main (void){
        int S,P,i;

        scanf("%d",&S);//recebe a quantidade de sentencas
        scanf("%d",&P);//recebe a quantidade de perguntas

        sentenca*end_sentencas=NULL;//ponteiro de sentenca* para armazenar o endereço da lista de structs sentencas
        end_sentencas=aloca_sentencas_heap(S);//recebe enderço da lista de structs sentencas alocada na heap    
        pergunta*end_perguntas=NULL;//ponteiro de pergunta* para armazenar o endereço da lista de structs perguntas
        end_perguntas=aloca_perguntas_heap(P);//recebe enderço da lista de structs perguntas alocada na heap 
        	
	for(i=0;i<P;i++){//para percorrer todas as perguntas armazenadas e responde-las uma por uma
                if(end_perguntas[i].string_pergunta[0]=='p'){//tipo de pergunta que inicia com "palavra"
                        encontra_palavra_e_armazena(end_perguntas[i].string_pergunta,end_perguntas[i].palavra);
                        int tam_palavra= strlen(end_perguntas[i].palavra);
                        encontra_produto_e_armazena1(end_perguntas[i].string_pergunta,tam_palavra,end_perguntas[i].produto_pergunta);
                        int qtd_palavras=encontra_produto_nas_sentencas1(end_sentencas,S,end_perguntas[i].produto_pergunta,end_perguntas[i].palavra);
                        printf("%d\n",qtd_palavras);
                }
                
                if(end_perguntas[i].string_pergunta[0]=='q'){//tipo de pergunta que inicia com "quantos" 
                        char char_aux=avalia_pergunta(end_perguntas[i].string_pergunta);//avalia se a pergunta procura por positivos ou negativos nos comentarios 
	                encontra_produto_e_armazena2(end_perguntas[i].produto_pergunta,end_perguntas[i].string_pergunta,21);//encontra o produto ao qual a pergunta se refere
                        float resultado;//variavel para receber a porcentagem final
		       	resultado=encontra_produto_nas_sentencas2(char_aux,end_sentencas,S,end_perguntas[i].produto_pergunta);
                	printf("%.1f%%\n",resultado);
		}
		
        }
	free(end_sentencas);
	free(end_perguntas);
        return 0;
}//final da main

