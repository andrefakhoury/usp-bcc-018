#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct produto {
	char tipo[20];
	char marca[20];
} produto;

typedef struct BagOfWords {
	int quant[200];
	char sentenca[20][20];
} BoW;

void lerComentarios(int num_sentencas, produto *nome_produto, BoW *comentario){
	int i = 0, j = 0, k = 0;
	
	for(i = 0; i < num_sentencas; i++){
		scanf(" %s %s %*c", nome_produto[i].tipo, nome_produto[i].marca);

		printf("%s %s\n", nome_produto[i].tipo, nome_produto[i].marca);

		for(j = 0; j < 20; j++){
			char aux[20];
			scanf(" %s", comentario[i].sentenca[j]);
			
			if (comentario[i].sentenca[j][0] == -61){
				printf("boa");
				break;
			}
			
			comentario[i].quant[j] = 0;
			
			comentario[i].quant[j]++;
			
			for (k = 0; k < j; k++){
				if (strcmp (comentario[i].sentenca[k], comentario[i].sentenca[j]) == 0){
					comentario[i].quant[k]++;
					comentario[i].quant[j]--;
					strcpy(comentario[i].sentenca[j], "\0"); // AQUI
					break;
				}
			}
			
		}
	}
}

int responderPerguntaComPalavra(int num_sentencas, produto *nome_produto, BoW *comentario, char pergunta[20][20]){
	int i = 0, j = 0;
	int quant = 0;
	
	for (i = 0; i < num_sentencas; i++){
			if ((strcmp(nome_produto[i].tipo, pergunta[3]) == 0) && (strcmp(nome_produto[i].marca, pergunta[4]) == 0)){
				for (j = 0; j < 20; j++){
					if (!strcmp(comentario[i].sentenca[j], "Ø")){
						break;
					}
					
					int isIgual = strcmp(comentario[i].sentenca[j], pergunta[1]);
					
					if (isIgual == 0){
						quant+=comentario[i].quant[j];
					}
				}	
			}
	}
	
	return quant;
}

float responderPerguntaComQuant(int num_sentencas, produto *nome_produto, BoW *comentario, char pergunta[5][20]){
	int i = 0, j = 0, k = 0;
	char positivo[12][20] = {"bom", "maravilhoso", "otimo", "sensacional", "excelente", "adorei", "gostei", "amei", "eficiente", "boa", "maravilhosa", "otima"};
	char negativo[12][20] = {"detestei", "odiei", "ruim", "pessimo", "terrivel", "raiva", "odio", "pessima", "lento", "lenta", "fragil", "desisti"};
	int quantPositivos = 0, quantNegativos = 0;
	float porcentagem = 0;
	
	for (i = 0; i < num_sentencas; i++){
			if ((strcmp(nome_produto[i].tipo, pergunta[3]) == 0) && (strcmp(nome_produto[i].marca, pergunta[4]) == 0)){
				for (j = 0; j < 20; j++){
					if (!strcmp(comentario[i].sentenca[j], "Ø")){
						break;
					}
					
					
					for (k = 0; k < 12; k++){
						int isIgual = strcmp(comentario[i].sentenca[j], positivo[k]);
						
						if (isIgual == 0){
							quantPositivos++;
						}	
						else{
							isIgual = strcmp(comentario[i].sentenca[j], negativo[k]);
							if (isIgual == 0){
							quantNegativos++;
							}
						} 
						
						
					}
				}		
			}
	}
	
	if (!strcmp(pergunta[1], "positivos")){
		porcentagem = (quantPositivos*100)/(quantPositivos+quantNegativos);
	}
	else{
		porcentagem = (quantNegativos*100)/(quantPositivos+quantNegativos);
	}
	
	return porcentagem;
}

void lerPerguntas(int num_perguntas, int num_sentencas, produto *nome_produto, BoW *comentario){
	int i = 0, j = 0;
	int quant = 0;
	float porcentagem = 0;
	char pergunta[5][20];
	
	for(i = 0; i < num_perguntas; i++){
		for (j = 0; j < 5; j++){
			scanf("%s", pergunta[j]);
		}
		if (!strcmp(pergunta[0], "palavra")){
			quant = responderPerguntaComPalavra(num_sentencas, nome_produto, comentario, pergunta);
			printf("%d\n", quant);
		}
		else{
			porcentagem = responderPerguntaComQuant(num_sentencas, nome_produto, comentario, pergunta);
			printf("%.1f%%\n", porcentagem);
		}
	}
	
}

int main(void){
	int num_sentencas = 0, num_perguntas = 0;
	
	scanf("%d %d", &num_sentencas, &num_perguntas);
	
	produto *nome_produto = (produto*) malloc(num_sentencas*sizeof(produto));
	BoW *comentario = (BoW*) malloc(num_sentencas*sizeof(BoW));
	
	lerComentarios(num_sentencas, nome_produto, comentario);
	lerPerguntas(num_perguntas, num_sentencas, nome_produto, comentario);	
}
