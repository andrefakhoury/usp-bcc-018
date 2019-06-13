/*
Programa para analise de comentarios
Jorge Augusto Salgado Salhani, junho 2019
*/

/*
Este programa tem como objetivo analisar a frequencia se palavras para comentarios a respeito de
determinados produtos de mercado, como impressora, tv, camera...

Esperamos, por exemplo, o seguinte resultado:

--------- Entrada -----------
4 1

Impressora Epson ; nao comprem ela e um nojo jamais diria que eu gostei dela Ø

Laptop HP ; que latop lento meu deus do ceu  Ø

Impressora Epson ; a impressora nao e la muito boa Ø

Impressora Epson ;  nem sei a performance nunca pareceu ser muito eficiente Ø

quantos negativos em Impressora Epson

--------- Saida --------------

0.0% 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/*
FUNCAO
	Leitura e armazenamento do numero de linhas de comentarios e perguntas

PARAMETROS
	Sem parametros

RETORNO
	int* - endereco contendo o numero de linhas e numero de perguntas a serem lidas	
*/

int* ler_numero_de_linhas(){

	int* end_num = (int*)malloc(2*sizeof(int));
	scanf("%d %d ", end_num, end_num+1);
	return end_num;
}

char* ler_linha() {
	
	char c = 'a';
	int tamanho = 0;
	
	char* conteudo = NULL;
	while(c != '\n' && c != EOF){
		c = getchar();
		conteudo = (char*)realloc(conteudo, sizeof(char)*(tamanho+1));
		if (c != '\n' && c != EOF){
			conteudo[tamanho] = c;
		} else {
			conteudo[tamanho] = '\0';
		}
		tamanho++;
	}
	
	return conteudo;
}

/*
FUNCAO
	Leitura e armazenamento de multiplas linhas, onde cada linha armazenada pertence a um comentario distinto

PARAMETROS
	int num_linhas - Numero de linhas (comentarios) a serem entregues

RETORNO
	char** - endereco contendo, para cada linha, um conjunto de caracteres
	
*/

char** ler_multiplas_linhas(int num_linhas){

	char** linhas = (char**)malloc(num_linhas*sizeof(char*));
	for(int i = 0; i < num_linhas; i++){
		linhas[i] = ler_linha();	
	}

	return linhas;
	
}

/*
FUNCAO
	Liberacao de memoria para uma matriz bidimensional

PARAMETROS
	char** matriz_2d - endereco contendo a matriz bidimensional a ser liberada
	int tamanho	 - numero de enderecos (associados aos enderecos contendo as strings). Pode ser entendido como o numero
			   de linhas de uma matriz 2d
	
RETORNO
	Sem retorno

*/

void libera_memoria_matriz_2d(char** matriz_2d, int tamanho){
	for(int i = 0; i < tamanho; i++){
		free(matriz_2d[i]);
	}
	free(matriz_2d);
}

/*
FUNCAO
	Liberacao de memoria para uma matriz bidimensional sem o conhecimento de seu tamanho

PARAMETROS
	char** - endereco contendo a matriz bidimensional a ser liberada

RETORNO
	Sem retorno
*/

void libera_memoria_matriz(char** matriz_2d){
	int i =0;
	char* auxiliar = matriz_2d[i];
	while (auxiliar !=NULL){
		free(auxiliar);
		i++;
		auxiliar = matriz_2d[i];
	}
	free(auxiliar);
	free(matriz_2d);
}

/*Construcao de uma struct que apresentara o produto e seu respectivo comentario*/
typedef struct {
	char produto[2*30];
	char opiniao[20*30];
	int * contagem;
} struct_comentario;

/*
FUNCAO
	Estruturacao de entrada em forma de struct, contendo o produto e a respectiva opiniao sobre o mesmo

PARAMETROS
	char** comentario completo - Enderecos contendo, para cada comentario, a string a ele relacionada. Tal string
				     contem tanto o nome do produto quanto a opiniao sobre ele
	int num_comentarios	   - Numero de comentarios, passado como entrada

RETORNO
	struct_comentario* - Endereco de memoria contendo a struct construida

*/
struct_comentario* estruturar_produto_opiniao(char** comentario_completo, int num_comentarios){
	struct_comentario* comentario_estruturado = (struct_comentario*)malloc(sizeof(struct_comentario)*num_comentarios);
	for(int i = 0; i < num_comentarios; i++){
		char c = comentario_completo[i][0];
		int k, j = 0;
		k = 0;
		while (c != ';'){
			comentario_estruturado[i].produto[k++] = c;
			j++;	
			c = comentario_completo[i][j];
			
		}
		//printf("%s:", comentario_estruturado[i].produto);
		k = 0;
		j++;
		c = comentario_completo[i][j];
		while ((int)c != -61){
			j++;
			comentario_estruturado[i].opiniao[k] = c;
			k++;
			c = comentario_completo[i][j];
		}
		//printf("%s\n", comentario_estruturado[i].opiniao);
	}
	return comentario_estruturado;
}

/*
FUNCAO
	Construcao do saco de palavras (bag of words) para analise de frequencia

PARAMETROS
	struct_comentario* comentario_estruturado - comentario completo (produto + opiniao) em formato de struct_comentario 
	int num_comentarios 			  - numero de comentarios, passado como entrada

RETORNO
	char** - Endereco contendo, para todas as palavras encontradas em dada lista de comentarios, uma lista com
		 cada uma, individualmente
*/

char** montar_saco_de_palavras(struct_comentario* comentario_estruturado, int num_comentarios){
	
	char** saco_de_palavras = NULL;
	int numero_de_palavras = 0;
	for(int i = 0; i < num_comentarios; i++){
		int tam_opiniao = strlen(comentario_estruturado[i].opiniao);
			
		for (int k = 0; k < tam_opiniao; k++){
			char* palavra_temporaria = NULL;
			int l = 0;
			while (comentario_estruturado[i].opiniao[k] == ' '){ 
				k++;
			}
			if (k < tam_opiniao){
				while(comentario_estruturado[i].opiniao[k] != ' '){
					palavra_temporaria = (char*)realloc(palavra_temporaria, sizeof(char)*(l+1));
					palavra_temporaria[l] = comentario_estruturado[i].opiniao[k];
					k++;
					l++;
				}	
				palavra_temporaria = (char*)realloc(palavra_temporaria, sizeof(char)*(l+1));
				palavra_temporaria[l] = '\0';
	
				int existe_palavra = 0;
				for (int j = 0; j < numero_de_palavras && existe_palavra == 0; j++){
					if (strcmp(palavra_temporaria, saco_de_palavras[j]) == 0){
						existe_palavra = 1;
					}
				}
	
				if (existe_palavra == 0 && palavra_temporaria[0] != ' '){
					saco_de_palavras = (char**)realloc(saco_de_palavras, sizeof(char*)*(numero_de_palavras+1));
					saco_de_palavras[numero_de_palavras] = palavra_temporaria;
					palavra_temporaria = NULL;
					numero_de_palavras++;
				//	printf("%s\n", saco_de_palavras[numero_de_palavras-1]);
				}
			}
		}
	}

	saco_de_palavras = (char**) realloc(saco_de_palavras, sizeof(char*)*(numero_de_palavras+1));
	saco_de_palavras[numero_de_palavras] = NULL;

	return saco_de_palavras;
}

/*
FUNCAO
	Recupera a palavra presente em uma dada posicao de uma string. Necessaria para compreensao da pergunta

PARAMETROS
	char* pergunta	       - String contendo a frase que se deseja analisar
	int posicao_da_palavra - Posicao em que temos a ocorrencia da palavra desejada 

RETORNO
	char* - Endereco contendo a sequencia de caracteres representativos da palavra recuperada da frase	
*/

char* recupera_nesima_palavra(char* pergunta, int posicao_da_palavra){
	
	char* palavra = NULL;
	int cursor = 0; 
	int tamanho_da_palavra = 0;
	int espacos = 0;
	
	if (posicao_da_palavra == 1){
		while (pergunta[cursor] != ' ' && pergunta[cursor] != '\0'){
			palavra = (char*) realloc(palavra, sizeof(char)*(tamanho_da_palavra +1));
			palavra[tamanho_da_palavra] = pergunta[cursor];
			tamanho_da_palavra++; 
			cursor++;
		}
		 	
	
	} else {

		while(espacos < posicao_da_palavra-1){
			if(pergunta[cursor] == ' '){
				espacos++;
			}
			cursor++;
		}
			
		while(pergunta[cursor] != ' ' && pergunta[cursor] != '\0'){
                        palavra = (char*) realloc(palavra, sizeof(char)*(tamanho_da_palavra +1));
                        palavra[tamanho_da_palavra] = pergunta[cursor];
                        tamanho_da_palavra++; 
                        cursor++;
                }
	
				

	}
	palavra = (char*) realloc(palavra, sizeof(char)*(tamanho_da_palavra +1));
        palavra[tamanho_da_palavra] = '\0';
	return palavra;
	
}

/*
FUNCAO
	Compreensao da pergunta, recuperando as quarta e quinta (se houver) palavras referentes ao produto que se deseja analisar

PARAMETROS
	char* pergunta - Endereco contendo a pergunta que se deseja responder

RETORNO
	char* - Endereco contendo os caracteres condizentes ao produto em analise 
*/

char* recupera_produto(char* pergunta){
	char* produto = NULL;
	int j = strlen(pergunta)-1;
        int cursor = 0;

        while (!(pergunta[j] == 'm' && pergunta[j-1] == 'e')){
		j--;
	}

        j+=2;

        while (pergunta[j] != '\0'){
        	produto = (char*) realloc(produto,sizeof(char)*(cursor+1));	
		produto[cursor] = pergunta[j];
                cursor++;
                j++;
        }

       	produto = (char*) realloc(produto,sizeof(char)*(cursor+1));
        produto[cursor] = pergunta[j];
        cursor ++;

	return produto;
}

/*
FUNCAO
	Contabilizacao do numero total de palavras na opiniao de cada produto

PARAMETROS
	struct_comentario* comentario_estruturado - Comentario em tipo 'struct_comentario', no qual armazenamos o produto
						    e a opiniao sobre o mesmo

RETORNO
	int - Numero total de palavras contadas

*/

int conta_total_de_palavras(struct_comentario * comentario_estruturado){

	int total_palavras = 0;
	int inicio =0;
	int final= strlen(comentario_estruturado[0].opiniao)-1;

	
	while(comentario_estruturado[0].opiniao[inicio] == ' ') inicio++;
	while(comentario_estruturado[0].opiniao[final]  == ' ') final--;


	for(int i = inicio; i < final; i++){
		if(comentario_estruturado[0].opiniao[i]==' ')
			total_palavras++;
	}
	return total_palavras+1;
}

/*
FUNCAO
	Contagem do numero de uma determinada palavra em cada opiniao referente ao produto

PARAMETROS
	char* palavra  - Palavra que se deseja buscar na pergunta
	char* pergunta - Pergunta (frase) onde se deseja analisar a frequencia da palavra

RETORNO
	int - Numero de vezes que <palavra> foi encontrada em <frase>
*/
int conta_ocorrencias(char* palavra, char* frase){


	char *p;
	char temp[100];
    	char* t = temp;
 	int bandeira;
	int ocorrencia = 0;

    	bandeira = 0;
   	for(p = frase; *p; p++) {
        	if(isspace(*p)) {
            		if(bandeira == 1) {
                 		*t = '\0';
                 		t = temp;
                 		if(strcmp(temp, palavra) == 0)
                    		ocorrencia++;
             		}
             		bandeira = 0;
          		} else {
             			*t++ = *p;
             			bandeira = 1;
          		}
    	}
    	*t = '\0';
    	if(strcmp(temp, palavra) == 0)
       	ocorrencia++;

        return ocorrencia;
}

/*
FUNCAO
	Reconhecimento da pergunta a ser respondida e determinacao da resposta a ela associada

PARAMETROS
	char** toda_pergunta 			  - Endereco contendo, para toda pergunta feita, uma string com a 
						    pergunta, propriamente dita
	int num_perguntas   			  - Numero de perguntas realizada, dado como entrada
	int num_comentarios			  - Numero de comentarios passados, dado como entrada
	struct_comentario* comentario_Estruturado - Comentario (produto + opiniao) ja estruturado em struct para que seja
						    consultado como banco de dados
	char** saco				  - Saco de palavras, contendo toda palavra, sem repeticao, para um 
						    dado conjunto de comentarios

RETORNO
	float* - Endereco contendo as respostas (inteiro ou percentual) que sao desejadas

*/



float* encontrar_respostas(char** toda_pergunta, int num_perguntas, int num_comentarios, struct_comentario* comentario_estruturado, char** saco){
	char* positivos[30] = {"bom", "maravilhoso", "otimo", "sensacional", "excelente", "adorei", "gostei", "amei", "eficiente", "boa", "maravilhosa", "otima"};

	char* negativos[30] = {"detestei", "odiei", "ruim", "pessimo", "terrivel", "raiva", "odio", "pessima", "lento", "lenta", "fragil", "desisti"};		
	int num_positivos = 12;
	int num_negativos = 12;
	float* respostas = (float*)malloc(sizeof(float)*num_perguntas);
	int modo_de_saida;
	for(int i = 0; i < num_perguntas; i++){
		char * palavra_busca = NULL;	
		char * produto_busca = NULL;	
	
		if (toda_pergunta[i][0] == 'q'){
			modo_de_saida = 1;
		} else {
			modo_de_saida = 0;
		}
		palavra_busca = recupera_nesima_palavra(toda_pergunta[i],2);

		int num_produto_igual = 0;
		int contagem_de_palavra_busca = 0;

		int contador_pn = 0;
		for (int j = 0; j < num_comentarios; j++){
			produto_busca = recupera_produto(toda_pergunta[i]);
			int tam_produto_busca = strlen(produto_busca);
			if (i != num_perguntas - 1){
				produto_busca[tam_produto_busca-1] = ' ';
			} else {
				produto_busca[tam_produto_busca] = ' ';
			}

			if (strcmp(comentario_estruturado[j].produto, produto_busca) == 0){
				num_produto_igual++;
				
				contagem_de_palavra_busca += conta_ocorrencias(palavra_busca, comentario_estruturado[j].opiniao);

				if (modo_de_saida == 1){
					int band = 0;
					if (strcmp(palavra_busca, "positivos") == 0 || strcmp(palavra_busca, "negativos") == 0){
						if (strcmp(palavra_busca, "positivos") == 0){
							for (int t = 0; t < num_positivos && band == 0; t++){
								if (conta_ocorrencias(positivos[t], comentario_estruturado[j].opiniao) > 0){
										contador_pn++;
										band = 1;
								}
							}
						} else {
							for (int t = 0; t < num_negativos && band == 0; t++){
								if (conta_ocorrencias(negativos[t], comentario_estruturado[j].opiniao) > 0){
										contador_pn++;
										band = 1;
								}
							}
						
						}	
					}
				}
			}
		}

		if (modo_de_saida == 0){
			respostas[i] = contagem_de_palavra_busca;
			printf("%d\n", (int)respostas[i]);
		} else {
			respostas[i] = 100*(float)contador_pn/(float)num_produto_igual;
			printf("%.1f%%\n", respostas[i]);
		}
		
		free(produto_busca);
		free(palavra_busca);
	}

	return respostas;

}

int main (void) {
	
	/*Parte 1 - Leitura e Armazenamento*/
	int* tamanho_de_entrada = ler_numero_de_linhas();
	char** todo_comentario = ler_multiplas_linhas(tamanho_de_entrada[0]);
	char** toda_pergunta = ler_multiplas_linhas(tamanho_de_entrada[1]);

	/*Parte 2 - Estruturacao de Dados*/
	struct_comentario* comentario_estruturado = estruturar_produto_opiniao(todo_comentario, tamanho_de_entrada[0]);	
	char** saco_de_palavras = montar_saco_de_palavras(comentario_estruturado, tamanho_de_entrada[0]);

	/*Parte 3 - Obtencao de Resposta Final*/
	float* respostas = encontrar_respostas(toda_pergunta, tamanho_de_entrada[1], tamanho_de_entrada[0], comentario_estruturado, saco_de_palavras);
	/*Parte 4 - Impressao de Resposta Final*/

	
	/*Parte 5 - Liberacao de Memoria*/
	libera_memoria_matriz_2d(todo_comentario, tamanho_de_entrada[0]);
	libera_memoria_matriz_2d(toda_pergunta, tamanho_de_entrada[1]);
	free(tamanho_de_entrada);
	free(comentario_estruturado);
	libera_memoria_matriz(saco_de_palavras);	
	free(respostas);

	return 0;
}
