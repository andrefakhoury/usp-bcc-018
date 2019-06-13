//TRABALHO 2 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOME_MAX 20 //eu que criei
#define PALAVRAS_MAX 20 //max de palavras que uma frase pode ter
#define CHAR_MAX 20 //max de caracteres que uma palavra pode ter

int main (void) {

	//declaracao de variaveis
	int numero_sentencas, numero_perguntas;
	char** nome_produto;
	char*** opiniao;
	char*** perguntas;

	//declaracao de um banco de dados que guarda as palavras positivas e negativas
	char banco_de_dados_bom[12][30] = {"bom", "maravilhoso", "otimo", "sensacional", "excelente", 
									"adorei", "gostei", "amei", "eficiente", "boa", "maravilhosa", "otima"};
	char banco_de_dados_ruim[12][30] = {"detestei", "odiei", "ruim", "pessimo", "terrivel", "raiva", 
									"odio", "pessima", "lento", "lenta", "fragil", "desisti"};


	//declaracao de contador das palavras negativas ou positivas em um comentario
	int* contador_pos = NULL;
	int* contador_neg = NULL;

	//declarando ponteiros flag de comentarios
	//essa flag indica quantas palavras boas tem em um comentario
	int* flag_coment_pos = NULL;
	

	//primeira entrada de dados
	scanf ("%d %d ", &numero_sentencas, &numero_perguntas);

	//aloca dinamicamente as variaveis contadoras
	contador_pos = calloc (numero_sentencas, sizeof(int));
	contador_neg = calloc (numero_sentencas, sizeof(int));
	flag_coment_pos = calloc (numero_sentencas, sizeof(int));
	
	
	//aloca dinamicamente a variavel nome_produto
	nome_produto = malloc (numero_sentencas*sizeof(char*));
	for (int i = 0; i < numero_sentencas; i++) {
		nome_produto[i] = malloc (NOME_MAX*sizeof(char));
	}

	//aloca dinamicamente a varivael opiniao
	opiniao = malloc (numero_sentencas*sizeof(char**));
	for (int i = 0; i < numero_sentencas; i ++) {
		opiniao[i] = malloc (PALAVRAS_MAX*sizeof(char*));
		for (int j = 0; j < PALAVRAS_MAX; j++) {
			opiniao[i][j] = malloc (CHAR_MAX*sizeof(char));
		}
	}

	//aloca dinamicamente a variavel perguntas
	perguntas = malloc (numero_perguntas*sizeof(char**));
	for (int i = 0; i < numero_perguntas; i ++) {
		perguntas[i] = malloc (PALAVRAS_MAX*sizeof(char*));
		for (int j = 0; j < PALAVRAS_MAX; j++) {
			perguntas[i][j] = malloc (CHAR_MAX*sizeof(char));
		}
	}

	//for que le os produtos e as opinioes
	for (int m = 0; m < numero_sentencas; m++) {
		scanf ("%[^;];", nome_produto[m]);
		for (int n = 0; n < PALAVRAS_MAX; n++) {
			scanf ("%s ", opiniao[m][n]);
		
			
			//esse if faz com que o programa pare de ler quando 
			//chega no caracter especial	
			if (strcmp (opiniao[m][n], "Ø") == 0) {
				break;
			}

			//quantas positivas/negativas em cada frase
			for (int i = 0; i < 12; i++) {
				if (strcmp (opiniao[m][n], banco_de_dados_bom[i]) == 0 ) {
					contador_pos[m] ++;
				}
				if (strcmp (opiniao[m][n], banco_de_dados_ruim[i]) == 0) {
					contador_neg[m] ++;
				}

			}
		}
		
		//flag indica se o comentario eh positivo ou negativo
		if (contador_pos[m] > contador_neg[m]) {
			flag_coment_pos[m] = 1;
		}

		if (contador_neg[m] > contador_pos[m]) {
			flag_coment_pos[m] = -1;
		}


	}
	

	//for que le as perguntas
	for (int i = 0; i < numero_perguntas; i++) {

		for (int j = 0; j < 5; j++) { 
			scanf ("%s ", perguntas[i][j]);

			if (strcmp (perguntas[i][j], "\n") == 0) {
				break;
			}	


			if (strcmp (perguntas[i][j], "\0") == 0) {
				break;
			}
		}

		//funcao que concatena o nome dos produtos de uma pergunta
		//para que a compracao seja feita
		strcat (perguntas[i][3], " ");
		strcat (perguntas[i][3], perguntas[i][4]);
		strcat (perguntas[i][3], " ");

		//esse if inicia o codigo do primeiro tipo de pergunta
		if (strcmp (perguntas[i][0], "quantos") == 0) {
			float contador_de_coment_pos = 0.0;
			float contador_de_coment_neg = 0.0;
			float resposta1;

			//for que verifica qual o produto sera analisado de acordo com a pergunta
			for (int k = 0; k < numero_sentencas; k++) {
				if (strcmp (perguntas[i][3], nome_produto[k]) == 0) {
					if (flag_coment_pos[k] == 1) {
						contador_de_coment_pos += 1.0;
					}	
					if (flag_coment_pos[k] == -1) {
						contador_de_coment_neg += 1.0;
					}
				}
			}

			if (strcmp (perguntas[i][1], "positivos") == 0) {
				resposta1 = (contador_de_coment_pos / (contador_de_coment_pos + contador_de_coment_neg)) *100;
				printf("%.1f%%\n", resposta1);
			}
			if (strcmp (perguntas[i][1], "negativos") == 0) {
				resposta1 = (contador_de_coment_neg / (contador_de_coment_pos + contador_de_coment_neg)) *100;
				printf("%.1f%%\n", resposta1);
			}

		}

		//esse if inicia o codigo do segundo tipo de pergunta
		if (strcmp (perguntas[i][0], "palavra") == 0) {		
			int contador_auxiliar = 0;

			for (int j = 0; j < numero_sentencas; j++) {				
				if (strcmp (perguntas[i][3], nome_produto[j]) == 0) {	
					for (int k = 0; k < PALAVRAS_MAX; k++) {
						if (strcmp (opiniao[j][k], "Ø") == 0) {
							break;
						}
						if (strcmp (perguntas[i][1], opiniao[j][k]) == 0) {
							contador_auxiliar ++;
						}			
					}
				}				
			}
			printf("%d\n", contador_auxiliar);
			contador_auxiliar = 0;
		}
	}

	//desaloca as variaveis contadoras
	free (contador_pos);
	free (contador_neg);
	free (flag_coment_pos);
	
	//desaloca variavel nome_produto
	for (int i = 0; i < numero_sentencas; i++) {
		free (nome_produto[i]);
	}
	free (nome_produto);

	//desaloca a varivael opiniao
	for (int i = 0; i < numero_sentencas; i ++) {
		for (int j = 0; j < PALAVRAS_MAX; j++) {
			free (opiniao[i][j]);
		}
		free (opiniao[i]);
	}
	free (opiniao);

	//desaloca a variavel perguntas
	for (int i = 0; i < numero_perguntas; i ++) {
		for (int j = 0; j < PALAVRAS_MAX; j++) {
			free (perguntas[i][j]);
		}
		free (perguntas[i]);
	}
	free (perguntas);


	return 0;

}