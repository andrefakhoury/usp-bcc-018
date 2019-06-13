/*
 *	<TRABALHO 2 DE ICC1: Contando Palavras>
 *
 *	Aluno: Gabriel de Oliveira Guedes Nogueira
 *	NUSP: 10295496
 *
 *	Professor: Rudinei Goularte
 *	Universidade de Sao Paulo (USP) - Sao Carlos
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*
 * Definicao de constantes. 
 */
//Tamanhos limites (por seguranca, sao usados valores maiores do que o necessario!)
#define MAX_CHARS 600
#define MAX_SENTENCES 32

//Tipos de perguntas
enum {
	POSITIVOS = 101, NEGATIVOS = 102, PALAVRA = 103
};

//Listas de palavras
const char *POSITIVE_WORDS[] = {"bom", "maravilhoso", "otimo", "sensacional", "excelente", "adorei", "gostei", "amei", "eficiente", "boa", "maravilhosa", "otima"};
const char *NEGATIVE_WORDS[] = {"detestei", "odiei", "ruim", "pessimo", "terrivel", "raiva", "odio", "pessima", "lento", "lenta", "fragil", "desisti"};
const char *INVERSION_WORDS[] = {"nao", "jamais", "nunca"};


/*
 * Implementacao de funcoes nao existentes no C99.
 */
//strdup (copia uma string)
char *my_strdup(char *src)
{
    size_t len = strlen(src) + 1; //o +1 serve para que o simbolo \0 seja copiado tambem
    char *s = malloc(len);
    
    if (s == NULL)
        return NULL;
        
    return (char *) memcpy(s, src, len); //memcpy retornara um ponteiro para s
}
//strsep (separa uma string usando um delimitador)
char *my_strsep(char** stringp, const char* delim)
{
  char *p, *start = *stringp;
  p = (start != NULL) ? strpbrk(start, delim) : NULL;

  if (p == NULL) {
    *stringp = NULL;
  }
  else {
    *p = '\0';
    *stringp = p + 1;
  }

  return start;
}
 

/*
 * Estrutura de um produto.
 */
typedef struct
{
	char *name; //nome do produto
	char sentences[MAX_SENTENCES][MAX_CHARS]; //sentencas que se referem ao produto
	int sentences_count; //numero de sentencas que se referem ao produto	
} Product;


/*
 * Associa uma sentenca a um produto.
 *
 * Product *p: produto em questao.
 * char *sentence: string contendo a sentenca.
 */
void addSentenceToProduct(Product *p, char *sentence)
{
	if(p->sentences_count < MAX_SENTENCES) {
		strcpy(p->sentences[p->sentences_count], sentence);
		p->sentences_count++;
	}
}


/*
 * Remove o ultimo caractere de uma string caso ele seja igual a c.
 *
 * char *str: a string que deseja-se alterar.
 * char c: o caractere que deve estar na ultima posicao da string.
 */
void removeLastChar(char *str, char c)
{
	int len = strlen(str);
	if(len > 0 && str[len-1] == c)
		str[len-1] = '\0';
}


/*
 * Le sentencas com multiplas palavras e as armazena na matriz dada.
 *
 * int count: quantidade de sentencas.
 * char sentencas[][]: matriz onde as sentencas serao armazenadas.
 */
void readSentences(int count, char sentences[][MAX_CHARS])
{
	for(int i = 0; i < count; i++) {
		fgets(sentences[i], MAX_CHARS, stdin);
		
		//ignora a entrada caso ela seja apenas um line breaker
		if(sentences[i][0] == '\n' || sentences[i][0] == '\r') {
			i--;
			continue;
		}
		
		//remove o line breaker do final da string, caso haja um
		removeLastChar(sentences[i], '\n');
	}
}


/*
 * Le sentencas na qual um produto é especificado no inicio. A funcao strsep() é usada para separar o produto do restante da sentenca.
 *
 * int count: quantidade de sentencas.
 * Product products[]: lista com os produtos
 * 
 */
int readSentencesWithProducts(int count, Product products[])
{
	char temp[MAX_SENTENCES][MAX_CHARS];
	readSentences(count, temp); //lendo a frase completa
	
	int productsCount = 0;
	for(int i = 0; i < count; i++) {
		char *temp2 = my_strdup(temp[i]);

		char *productName = my_strsep(&temp2, ";");
		removeLastChar(productName, ' '); //remove o espaco no final do nome do produto
			
		//Verifica se o produto ja esta na lista
		int index = -1; 
		for(int j = 0; j < productsCount; j++) {
			if(strcmp(productName, products[j].name) == 0) {
				index = j;
			}
		}

		//Novo produto, caso nao haja nenhum com o nome especificado
		if(index < 0) {
			index = productsCount;
			productsCount++;

			products[index].name = productName;
			products[index].sentences_count = 0;
		}

		//Descobre a sentenca e a adiciona ao produto associado
		char *sentence = my_strsep(&temp2, ";"); //separando sentencas
		addSentenceToProduct(&products[index], sentence);
		
		free(temp2); //liberando a memoria alocada com o strdup()
	}

	return productsCount;
}


/*
 * Retorna o index (referente a array de produtos) do produto ao qual a pergunta se refere. Retorna -1 caso o produto nao seja encontrado.
 *
 * char *question: referencia para a string que contem a pergunta.
 * Products products[]: array que contem os produtos.
 * int count: numero de produtos
 */
int findProductIndex(char *question, Product products[], int count)
{
	for(int i = 0; i < count; i++) {
		if(strstr(question, products[i].name) != NULL)
			return i;
	}

	return -1;
}


/*
 * Busca pela intencao da pergunta (o que ela quer saber).
 *
 * char *question: referencia para a string contendo a pergunta.
 */
int getQuestionIntent(char *question) 
{
	if(strstr(question, "palavra") != NULL)
		return PALAVRA;
	if(strstr(question, "negativos") != NULL)
		return NEGATIVOS;
	
	return POSITIVOS;
}


/*
 * Retorna a quantidade de vezes que uma dada palavra aparece em uma sentenca.
 *
 * char *word: palavra cujo uso sera contado.
 * char *sentence: sentenca que sera analisada.
 */
int countWordUsage(const char *word, char *sentence)
{
	int counter = 0;

	char *temp = my_strdup(sentence);
	char *resultWord = my_strsep(&temp, " ");
	
	while(resultWord != NULL) {
		if(strcmp(word, resultWord) == 0) 
			counter++;

		resultWord = my_strsep(&temp, " ");
	}		

    free(temp);
	return counter;
}


/*
 * Retorna 1 caso a palavra dada seja um inversor e 0 caso nao.
 *
 * char *word: palavra que sera checada.
 */
int isInversor(char *word)
{
	for(int i = 0; i < 3; i++) {
		if(strcmp(word, INVERSION_WORDS[i]) == 0)
			return 1;
	}
	return 0;
}


/*
 * Retorna 1 caso a palavra dada pertenca a classe das "positivas".
 *
 * char *word: palavra que sera analisada.
 */
int isPositive(char *word) {
	for(int i = 0; i < 12; i++) {
		if(strcmp(word, POSITIVE_WORDS[i]) == 0)
			return 1;
	}
	return 0;
}


/*
 * Retorna 1 caso a palavra dada pertenca a classe das "negativas".
 *
 * char *word: palavra que sera analisada.
 */
int isNegative(char *word) {
	for(int i = 0; i < 12; i++) {
		if(strcmp(word, NEGATIVE_WORDS[i]) == 0)
			return 1;
	}
	return 0;
}


/*
 * Retorna a quantidade de vezes que palavras de uma dada lista, levando-se em consideracao inversores, aparecem nas sentencas de um produto.
 *
 * Product p: produto que sera analisado.
 * int dividend: o dividendo da razao (POSITIVO ou NEGATIVO)
 */
double countPosNegRatio(Product p, const int dividend)
{
	int pos = 0, neg = 0, lastInversor = 4;
	for(int i = 0; i < p.sentences_count; i++) 
	{
		char *sentence = my_strdup(p.sentences[i]);
		char *word = my_strsep(&sentence, " ");
		
		int countedPos = 0, countedNeg = 0; //verifica se ja foi contada uma opiniao positiva ou negativa na sentenca em questao	
		while(word != NULL) 
		{
			if(isInversor(word)) {
				lastInversor = 1;
			}
			else {
				if(lastInversor > 3) {
					//Positiva
					if(isPositive(word) && !countedPos) {
						pos++;
						countedPos = 1;
					}
					//Negativa
					else if(isNegative(word) && !countedNeg) {
						neg++;
						countedNeg = 1;
					}
				}
				else {
					//Negativa (inversao)
					if(isPositive(word) && !countedNeg) {
						neg++;
						countedNeg = 1;
					}
					//Positiva(inversao)
					else if(isNegative(word) && !countedPos) {
						pos++;
						countedPos = 1;
					}
				}
				lastInversor++;
			}
			word = my_strsep(&sentence, " ");
		}
		free(sentence);
	}
	
	int total = pos + neg;
	return (dividend == POSITIVOS) ? (double) pos/total : (double) neg/total;
}


/*
 * Processa e responde a uma pergunta.
 *
 * char *question: pergunta que deve ser respondida.
 * Products products[]: lista de produtos
 * int count: quantidade total de produtos
 */
void processQuestion(char *question, Product products[], int count)
{
	int pIndex = findProductIndex(question, products, count);
	
	if(pIndex >= 0) 
	{
		Product p = products[pIndex];
		int intent = getQuestionIntent(question);

		switch(intent)
		{
			case POSITIVOS:
			case NEGATIVOS:
			{
				printf("%.1lf%%\n", 100*countPosNegRatio(p, intent));
				break;
			}
			case PALAVRA:
			{
				
				//descobre a palavra que se deseja buscar
				char *temp = my_strdup(question);
				my_strsep(&temp, " "); //descarta a primeira palavra
				char *word = my_strsep(&temp, " "); //armazena a segunda palavra
				
				//checa quantas vezes a palavra apareceu
				int counter = 0;
				for(int i = 0; i < p.sentences_count; i++) {
					counter += countWordUsage(word, p.sentences[i]);
				}
				
				printf("%d\n", counter);
				break;
			}
			default:
				printf("Nao foi possivel detectar a intencao da pergunta!\n");
		}
	}
	else {
		printf("Produto nao encontrado!\n");
	}
}


/*
 * MAIN
 */
int main()
{
	int sentences_count, questions_count; 
	scanf("%d %d", &sentences_count, &questions_count);

	Product products[MAX_SENTENCES]; //armazena os produtos e suas respectivas sentencas
	int products_count = readSentencesWithProducts(sentences_count, products);

	char questions[MAX_SENTENCES][MAX_CHARS]; //armazena as perguntas
	readSentences(questions_count, questions);

	for(int i = 0; i < questions_count; i++) {
		processQuestion(questions[i], products, products_count);
	}


	/*
	//DEBUG
	for(int i = 0; i < productsCount; i++) {
		Product p = products[i];
		printf("-> %s:\n", p.name);
		for(int j = 0; j < p.sentences_count; j++) {
			printf("    %d - %s\n", j, p.sentences[j]); 
		}
	}
	*/

	return 0;
}
