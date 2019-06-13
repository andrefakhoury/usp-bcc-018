#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ou ||


//analise da polaridade dos comentarios acerca de todos os produtos
void analyze (char prod[][2][20], char coments[][21][20], char pos[12][15], char neg[12][15], char inv[3][10], int number, int vetor[]) {
	//bool para analise de polaridade
	_Bool flag;
	//bool para sinalizar a palavra encontrada
	_Bool find;
	
	for (int i = 0; i < number; i++)  {                                    //for para cada frase
		for (int j = 0; j < 21; j++) {				       //for para cada palavra da frase
			find = 0;
			for (int k = 0; k < 12; k++) {			       //for para cada palavra dentro do banco de palavras chave
				if (!(strcmp(coments[i][j], pos[k]))) {        //se palavra positiva encontrada
					flag = 1;
					find = 1;
					break;
				}
				else if (!(strcmp(coments[i][j], neg[k]))) {   //se palavra negativa encontrada
					flag = 0;
					find = 1;
					break;
				}
			}
			
			//caso a palavra seja encontrada, verifica a necessidade de inversao
			if (find) {
				for (int x = j-3; x < j ; x++) {
					for (int y = 0; y < 3; y++) {
						if (!(strcmp(coments[i][x], inv[y]))) flag=!flag;
					}
				}
				break;
			}
		}

		vetor[i] = flag; //se comentario "i" positivo, vetor[i] = 1; negativo, vetor[i] = 0

	}

}



//procurar por "word" nos comentarios do produto "prod"
void searchfor (char word[], char prod[], char prods[][2][20], char coments[][21][20], int number) {
	int count = 0;
	for (int i = 0; i < number; i++) {		//para cada frase
		if (!(strcmp(prod, prods[i][0]))) {	//verifica se o produto e' o produto que se deseja comparar
			for (int j = 0; j<21; j++) {
				if (!(strcmp(word, coments[i][j]))) count++; //conta a palavra "word" desejada na frase
			}	
		}
	}	
	printf("%d\n", count);	
}


//contar a polaridade das opinoes sobre "prod"
void reviews (char prod[], char polar[], char prods[][2][20], int number, int vetor[]) {
	int p = 0;
	int n = 0;
	int x;
		for (int i = 0; i < number; i++) {
			if (!(strcmp(prods[i][0], prod))) {
			//conta as polaridades em cada i do vetor
			//caso cada i se refira a posicao do produto a ser analisado
				if (vetor[i]) p++;
				else n++;
			}
		}
	if (!(strcmp(polar, "positivos"))) x = p;
	else x = n;
	float t = p+n;
	float result = (x/t)*100;
	printf("%.1f%%\n", result);
}



int main () {
	//entrada do numero de comentarios e numero de pergunta
	int nComents, nQuest;
	scanf("%d %d", &nComents, &nQuest);
	
	//declarar arrays multdimensionais para os comentarios, o nome dos produtos
	//e as perguntas
	char coments[nComents][21][20];
       	char prod[nComents][2][20];
	char quest[nQuest][5][20];
	//vetor para sinalizar a polaridade de cada comentario
	int polaridade[nComents];
	
	
	//entrada dos comentarios acerca dos produtos
	for (int i = 0; i < nComents; i++) {
		for (int j = 0; j < 23; j++) {
			//entrada dos produtos
			if (!j ou !(j-1)) scanf(" %s", prod[i][j]);

			//supressao do ";"
			else if (j==2) scanf("%*s");

			//entrada dos "reviews"
			else scanf(" %s", coments[i][j-3]);

			//analise do simbolo de finalizacao da frase e substituicao por "\0"
			if (!(strcmp(coments[i][j-3], "Ø"))) {
				coments[i][j-3][0] = '\0';
				break; //finalizar a entrada da mesma frase
			}
			//incrementa o numero de palavras
		}
		strcat(prod[i][0], prod[i][1]);
	}

	//entrada das perguntas
	for (int i = 0; i < nQuest; i++) {
		for (int j = 0; j < 5; j++) scanf("%s", quest[i][j]);
		strcat(quest[i][3], quest[i][4]); // concatenacao para facilitar a comparacao
	}

	//palavras chave para comentarios positivos e negativos e adverbios de negacao
	char positivos[12][15] = {"bom\0", "maravilhoso\0", "otimo\0", "sensacional\0", 
		                  "excelente\0", "adorei\0", "gostei\0", "amei\0", 
				  "eficiente\0", "boa\0", "maravilhosa\0", "otima\0"};

	char negativos[12][15] = {"detestei\0", "odiei\0", "ruim\0", "pessimo\0", "terrivel\0", 
				  "raiva\0", "odio\0", "pessima\0", "lento\0", "lenta\0", 
				  "fragil\0", "desisti\0"};

	char inversor[3][10] = {"nao\0", "jamais\0", "nunca\0"};

	
	
	analyze(prod, coments, positivos, negativos, inversor, nComents, polaridade);


	//analise das perguntas e respostas para elas
	for (int i = 0; i < nQuest; i++) {
		if (!(strcmp(quest[i][0], "palavra"))) searchfor(quest[i][1], quest[i][3], prod, coments, nComents);
		else if (!(strcmp(quest[i][0], "quantos"))) reviews(quest[i][3], quest[i][1], prod, nComents, polaridade);
	}	
	
}
