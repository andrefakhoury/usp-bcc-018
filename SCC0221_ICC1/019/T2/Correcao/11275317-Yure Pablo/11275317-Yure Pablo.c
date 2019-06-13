#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STRINGS 20
#define MAX_CARACTERES 20
#define ASK_WORDS 5
#define WORDS_POSITIVE_OR_NEGATIVE 12
#define MAX_WORDS 200
#define NUM_ADVERBIOS 3

//structs

typedef struct Produto {
	char tipo[MAX_CARACTERES];
	char marca[MAX_CARACTERES];
} produto;

typedef struct _BagOfWords {
	int quant_palavra[MAX_WORDS];
	char palavra[MAX_STRINGS][MAX_CARACTERES];
} BoW;

//prototipos das funcoes

bool isIgual(char*, char*);
bool leuCaractereEspecial(char *);
void armazenarComentarios(int, produto*, BoW*);
int quantificarPalavra(int, produto*, BoW*, char[ASK_WORDS][MAX_CARACTERES]);
bool existeNegacao(BoW*, int, int);
float contarPositivosOuNegativos(int, produto*, BoW*, char[ASK_WORDS][MAX_CARACTERES]);
void responderPerguntas(int, int, produto*, BoW*);
void liberarMemoria(BoW*, produto*);
void finalizarPrograma();

int main(void){
	/* le a quantidade de sentencas e de perguntas, aloca memoria para os vetores das structs, verifica
	   se a alocacao foi bem sucedida, e chama as funcoes responsaveis por ler as sentencas e perguntas 
	   e responder as perguntas */
	   
	int num_sentencas = 0, num_perguntas = 0;

	scanf("%d %d", &num_sentencas, &num_perguntas);
	
	produto *nome_produto = (produto*) malloc(num_sentencas*sizeof(produto));
	
	if (nome_produto == NULL)
	{
        finalizarPrograma();
    }
	
	BoW *BagOfWords = (BoW*) malloc(num_sentencas*sizeof(BoW));
	
	if (BagOfWords == NULL)
	{
        finalizarPrograma();
    }
	
	armazenarComentarios(num_sentencas, nome_produto, BagOfWords);
	responderPerguntas(num_perguntas, num_sentencas, nome_produto, BagOfWords);
	liberarMemoria(BagOfWords, nome_produto);
}

bool isIgual(char *p1, char *p2){
	/* Compara duas palavras utilizando a funcao strcmp(). Se retornar 0, sao iguais.*/
	
	if (strcmp(p1, p2) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool leuCaractereEspecial(char *palavra){
	/* Verifica se o caractere "Ø" de condicao de parada foi lido. */
	
	if (isIgual(palavra, "Ø"))
	{
		return true;
	}
	else
	{
		return false;
	}
		
}	

void armazenarComentarios(int num_sentencas, produto *nome_produto, BoW *comentario){
	/* Le e armazena cada nome_do_produto e cada comentario (palavra a palavra), 
	   bem como armazena a quantidade de cada palavra do comentario num vetor cuja posicao
	   é a mesma que a da palavra exibida pela primeira vez */
	
	char identificador;
	
	for (int i = 0; i < num_sentencas; i++)
	{
		scanf("%s %s %c", nome_produto[i].tipo, nome_produto[i].marca, &identificador);

		for (int j = 0; j < MAX_STRINGS; j++)
		{
			scanf("%s", comentario[i].palavra[j]);
			
			if (leuCaractereEspecial(comentario[i].palavra[j]))
			{
				break;
			}
			
			comentario[i].quant_palavra[j] = 1;
			
			/* Verifica se a palavra atual é igual a alguma das anteriores a fim de atualizar a quantidade
			   dessa palavra */
			for (int k = 0; k < j; k++)
			{
				if (isIgual(comentario[i].palavra[k], comentario[i].palavra[j]))
				{
					comentario[i].quant_palavra[k]++;
					comentario[i].quant_palavra[j]--;
					break;
				}
			}
			
		}
	}
}

void responderPerguntas(int num_perguntas, int num_sentencas, produto *nome_produto, BoW *comentario){
	/* Le e armazena cada pergunta (palavra a palavra), verifica a pergunta que foi feita, e responde essa pergunta. 
	   Como so ha dois tipos de pergunta, se ela comecar com "palavra" chama a funcao que retorna 
	   a quantidade de uma palavra, caso contrario, chama a funcao que retorna a porcentagem 
	   de comentarios positivos ou negativos */

	int quant = 0;
	float porcentagem = 0;
	char pergunta_palavra[ASK_WORDS][MAX_CARACTERES];
	
	for (int i = 0; i < num_perguntas; i++)
	{
		for (int j = 0; j < ASK_WORDS; j++)
		{
			scanf("%s", pergunta_palavra[j]);
		}

		if (isIgual(pergunta_palavra[0], "palavra"))
		{
			quant = quantificarPalavra(num_sentencas, nome_produto, comentario, pergunta_palavra);
			printf("%d\n", quant);
		}
		else
		{
			porcentagem = contarPositivosOuNegativos(num_sentencas, nome_produto, comentario, pergunta_palavra);
			printf("%.1f%%\n", porcentagem);
		}
	}
}

int quantificarPalavra(int num_sentencas, produto *nome_produto, BoW *comentario, char pergunta_palavra[ASK_WORDS][MAX_CARACTERES]){
	/* Verifica sobre qual produto é a pergunta e retorna a quantidade de vezes que a palavra solicitada 
	aparece no(s) comentario(s) desse produto */

	int quant = 0;
	
	for (int i = 0; i < num_sentencas; i++)
	{
		bool isProdutoPerguntado = isIgual(nome_produto[i].tipo, pergunta_palavra[3]) && isIgual(nome_produto[i].marca, pergunta_palavra[4]);
		if (isProdutoPerguntado)
		{
			for (int j = 0; j < MAX_STRINGS; j++)
			{
				if (leuCaractereEspecial(comentario[i].palavra[j]))
				{
					break;
				}
						
				if (isIgual(comentario[i].palavra[j], pergunta_palavra[1]))
				{
					quant += comentario[i].quant_palavra[j];
					break;
				}
			}	
		}
	}
	
	return quant;
}

float contarPositivosOuNegativos(int num_sentencas, produto *nome_produto, BoW *comentario, char pergunta_palavra[ASK_WORDS][MAX_CARACTERES]){
	/* Verifica sobre qual produto é a pergunta e compara as palavras do(s) comentario(s) desse produto com 
	   a base de dados de palavras padroes de respostas positivas e negativas, contabilizando o numero de 
	   mencoes positivas e negativas. Ainda chama uma funcao que verifica a existencia de adverbios que 
	   invertem a polaridade. Ao final, retorna a porcentagem de mencoes negativas ou positivas, a depender 
	   da pergunta */

	char positivo[WORDS_POSITIVE_OR_NEGATIVE][MAX_CARACTERES] = {"bom", "maravilhoso", "otimo", "sensacional", "excelente", "adorei", "gostei", "amei", "eficiente", "boa", "maravilhosa", "otima"};
	char negativo[WORDS_POSITIVE_OR_NEGATIVE][MAX_CARACTERES] = {"detestei", "odiei", "ruim", "pessimo", "terrivel", "raiva", "odio", "pessima", "lento", "lenta", "fragil", "desisti"};
	int comentariosPositivos = 0, comentariosNegativos = 0;
	int total = 0;
	float porcentagem = 0.0;
	
	for (int i = 0; i < num_sentencas; i++)
	{
		int quantPositivos = 0, quantNegativos = 0;
		bool isProdutoPerguntado = isIgual(nome_produto[i].tipo, pergunta_palavra[3]) && isIgual(nome_produto[i].marca, pergunta_palavra[4]);
		if (isProdutoPerguntado)
		{
			for (int j = 0; j < MAX_STRINGS; j++)
			{
				if (leuCaractereEspecial(comentario[i].palavra[j]))
				{
					break;
				}
					
				for (int k = 0; k < WORDS_POSITIVE_OR_NEGATIVE; k++)
				{
					if (isIgual(comentario[i].palavra[j], positivo[k]))
					{
						if (existeNegacao(comentario, i, j))
						{
							quantNegativos++;
						}
						else
						{
							quantPositivos++;
						}
					}	
					else
					{
						if (isIgual(comentario[i].palavra[j], negativo[k]))
						{
							if (existeNegacao(comentario, i, j))
							{
								quantPositivos++;
							}
							else
							{
								quantNegativos++;
							}
						
						}
					} 	
				}
			}
			
			if (quantPositivos > quantNegativos)
			{
				comentariosPositivos++;
			}		
			else
			{
				comentariosNegativos++;
			}
		}	
	}
	
	total = comentariosPositivos + comentariosNegativos;

	if (isIgual(pergunta_palavra[1], "positivos"))
	{
		if (total != 0)
		{
			porcentagem = (float) (comentariosPositivos*100)/total;
		}
		else
		{
			porcentagem = 0;	
		}
		
	}
	else
	{
		if (total != 0)
		{
			porcentagem = (float) (comentariosNegativos*100)/total;
		}
		else
		{
			porcentagem = 0;
		}
		
	}
	
	return porcentagem;
}

bool existeNegacao(BoW *comentario, int indice_comentario, int indice_palavra){
	/* Verifica se existe um dos tres adverbios de negacao mais frequentes em ate tres posicoes 
	   antes da palavra analisada. Note que a funcao garante a comparacao apenas com posicoes positivas */
	
	int j = indice_palavra - 1;
	char adverbioDeNegacao[NUM_ADVERBIOS][MAX_CARACTERES] = {"nao", "jamais", "nunca"};
	
	while ((j >= 0) && (j >= indice_palavra - 3)) 
	{
		for (int i = 0; i < NUM_ADVERBIOS; i++)
		{
			if (isIgual(comentario[indice_comentario].palavra[j], adverbioDeNegacao[i]))
			{
				return true;
			}
		}
		
		j--;
	}	
	
	return false;
}

void finalizarPrograma(){
	/* Encerra forcadamente o programa caso falte memoria para alocar em algum dos vetores */
	
	printf("\n Sem memoria! \n");
    exit(1);
}

void liberarMemoria(BoW *comentario, produto *nome_produto){
	free(comentario);
	free(nome_produto);
}