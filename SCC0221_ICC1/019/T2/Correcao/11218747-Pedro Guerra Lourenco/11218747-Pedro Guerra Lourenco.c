#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE_COMMENT 400
#define MAX_SIZE_BAGOFWORDS 200
#define MAX_SIZE_WORD 20
#define NUM_BADANDGOODWORDS 12
#define NUM_INVERSIONWORDS 3

/*
Reenviado devido ao acréscimo de alguns comentários

Está havendo vazamento de memória na função SplitString(),
mas infelizmente não consegui achar o problema...
*/

// -------- Função para contar número de sentenças boas e ruins --------
void countNumBadAndGoodSentences(char *** splitedCommentaryString, int * numGoodSentences, int * numBadSentences, int * numWordsInCommentary) {
	int goodWords = 0, badWords = 0, counterOfPossibleInvesion = 0, invertionFlag = 0;

	// listas de palavras boas, ruins e que invertem "positividade/negatividade"
	static char * goodCommentaryWords[] = {"bom", "maravilhoso", "otimo", "sensacional", "excelente", "adorei", "gostei", "amei", "eficiente", "boa", "maravilhosa", "otima"};
	static char * badCommentaryWords[] = {"detestei", "odiei", "ruim", "pessimo", "terrivel", "raiva", "odio", "pessima", "lento", "lenta", "fragil", "desisti"};
	static char * invertMeaningWords[] = {"nao", "jamais", "nunca"};

	for (int i = 0; i < (*numWordsInCommentary); ++i) {
		if (invertionFlag) { // 'invertionFlag' representa se apareceu [não, nunca, jamais], o que inverterá o tipo da próxima palavra das listas (se é boa ou ruim)
			++counterOfPossibleInvesion;
			if (counterOfPossibleInvesion > 3) { // limite de distância entre [não, nunca, jamais] e palavra de uma das listas (boas ou ruims) é igual a 3
				counterOfPossibleInvesion = 0;
				invertionFlag = 0;
			}
		}

		// -------- Verificando se palavra do comentário == palavra que interve sentido (não, nunca, jamais) --------
		for (int m = 0; m < NUM_INVERSIONWORDS; ++m) {
			if (!strcmp(invertMeaningWords[m], (*splitedCommentaryString)[i])) {
				invertionFlag = 1;
				counterOfPossibleInvesion = 0;
				break;
			}
		}

		// -------- Verificando se palavra do comentário == palavra positiva --------
		for (int j = 0; j < NUM_BADANDGOODWORDS; ++j) {
			if (!strcmp((*splitedCommentaryString)[i], goodCommentaryWords[j])) {
				if (invertionFlag) // palavra boa torna-se ruim devido a algum [não, nunca, jamais] que a antecedeu
					++badWords;
				else
					++goodWords;
			}
			else {
				// -------- Verificando se palavra do comentário == palavra negativa --------
				if (!strcmp((*splitedCommentaryString)[i], badCommentaryWords[j])) {
					if (invertionFlag) // palavra ruim torna-se boa devido a algum [não, nunca, jamais] que a antecedeu
						++goodWords;
					else
						++badWords;
				}
			}
		}
	}

	// -------- Avaliando sentença boa ou ruim com base no número de palavras boas/ruins --------
	if (goodWords > badWords) {
		++(*numGoodSentences);
	}
	else if (badWords > goodWords){
		++(*numBadSentences);
	}

	return;
}
// -------- Função para buscar frequência de certa palavra nos comentários de determinado produto (na Bag Of Words dos comentários) --------
// Retorna a frequência da palavra buscada dentro do 'set' de comentários referente a determinado produto
int getWordFrequency(char ** referenceWord, char ** wordsFromComment, int * wordsFromCommentFrequency, int * numWordsInBow) {
	// -------- Verificando se a palavra buscada está no Bag of Words (wordsFromComment) --------
	for (int i = 0; i < *numWordsInBow; ++i) {
		if (!strcmp(wordsFromComment[i], (*referenceWord))) {
			return wordsFromCommentFrequency[i];
		}
	}
	return 0;
}

// -------- Função para gerar Bag of Words (lista de palavras que estão nos comentários de determinado produto) e lista de frequência de cada palavra da BoW --------
void BagOfWords(char *** prodComment, char ** wordsFromComment, int * wordsFromCommentFrequency, int * numWordsInBow, int * numWordsInCommentary) {
	int WordInBoW = 0; // flag que representa se a palavra está na Bow (1 = está no Bow)

	for (int c = 0; c < (*numWordsInCommentary); ++c) {
		// -------- Verificando se a palavra já está presente na Bow (wordsFromComment) --------
		for (int d = 0; d < *numWordsInBow; ++d) {
			if (!strcmp((*prodComment)[c], wordsFromComment[d])) {
				wordsFromCommentFrequency[d] += 1;
				WordInBoW = 1;
				break;
			}
		}

		// -------- Se palavra não listada na BoW, ela é inserida --------
		if (!WordInBoW) {
			wordsFromComment[*numWordsInBow] = (char *)malloc((strlen((*prodComment)[c])+1) * sizeof(char));

			strcpy(wordsFromComment[*numWordsInBow], (*prodComment)[c]);
			wordsFromCommentFrequency[*numWordsInBow] = 1;
			++(*numWordsInBow);
		}

		WordInBoW = 0;
	}

	return;
}

// -------- Função para dar split nos comentários (separar as palavras) --------
// Retorna a quantidade de palavras presentes no comentário (armazenadas no array de palavras 'resultStringArray')
int splitString(char * stringToSplit, char *** resultStringArray, char delimiter[1]) { // Memory leak (heap mem.)!! 
	char * copyOfStringToSplit;
	int numWordsCounted = 0, l = 0, allocatedSpaceArrayStrings = 10;

	copyOfStringToSplit = (char *)malloc((strlen(stringToSplit)+1) * sizeof(char));
	if (copyOfStringToSplit == NULL)
		exit(1);

	strcpy(copyOfStringToSplit, stringToSplit);

	(*resultStringArray) = (char **)malloc(allocatedSpaceArrayStrings * sizeof(char *));
	if ((*resultStringArray) == NULL)
		exit(1);

	char * token = strtok(copyOfStringToSplit, delimiter);

	while (token != NULL) {
		// -------- Se o número de palavras no comentário ultrapassar os espaços no array, realoca espaço para colocar mais palavras no array --------
		if (numWordsCounted + 1 >= allocatedSpaceArrayStrings) {
			allocatedSpaceArrayStrings *= 2;
			(*resultStringArray) = (char **)realloc((*resultStringArray), allocatedSpaceArrayStrings * sizeof(char *));
			if ((*resultStringArray) == NULL)
				exit(1);
		}

		(*resultStringArray)[numWordsCounted] = (char *)malloc((strlen(token)+1) * sizeof(char));
		if ((*resultStringArray)[numWordsCounted] == NULL)
			exit(1);

		l = 0;
		// -------- Armazenando os caractéres da palavra (do comentário para o array de palavras resultante) um a um --------
		for (char * p = token; *p != '\0'; p++, l++) {
			(*resultStringArray)[numWordsCounted][l] = *p; 
		}
		(*resultStringArray)[numWordsCounted][l] = '\0';

		token = strtok(NULL, delimiter);
		++numWordsCounted;
	}
	// -------- Reajustando a qtd de espaços para palavras no array para o tamanho correto de palavras presentes no comentário --------
	(*resultStringArray) = (char **)realloc((*resultStringArray), numWordsCounted * sizeof(char *));

	free(copyOfStringToSplit);

	return numWordsCounted;
}

// -------- Função para pegar o nome do produto a partir da pergunta --------
void getProdName(char ** productToSearchFor, char ** splitedString, int initPos) {
	char auxString[2*MAX_SIZE_WORD+3]; // armazena o nome do produto temporariamente

	// -------- Copiando nome do produto para string auxiliar --------
	strcpy(auxString, splitedString[initPos]);
	strcat(auxString, " ");
	strcat(auxString, splitedString[initPos+1]);
	strcat(auxString, " ");

	*productToSearchFor = malloc((strlen(auxString)+1) * sizeof(char));
	if (*productToSearchFor == NULL)
		exit(1);

	*productToSearchFor = strcpy(*productToSearchFor, auxString);

	return;
}

int main(int argc, char const *argv[])
{
	int numSentences, numQuestions, i, j;

	scanf("%d %d ", &numSentences, &numQuestions);
	fflush(stdin);

	char * productName[numSentences];
	char * productComment[numSentences];
	char * questions[numQuestions];
	char inputQuestion[MAX_SIZE_COMMENT], inputCommentary[MAX_SIZE_COMMENT], inputProdName[MAX_SIZE_COMMENT];

	// -------- Pegando nome do produto e comentário sobre ele --------
	for (i = 0; i < numSentences; i++) {
		scanf("%[^;]; %[^Ø]Ø\n", inputProdName, inputCommentary);

		productComment[i] = (char *)malloc((strlen(inputCommentary)+1) * sizeof(char));
		if (productComment[i] == NULL)
			exit(1);

		productName[i] = (char *)malloc((strlen(inputProdName)+1) * sizeof(char));
		if (productName[i] == NULL)
			exit(1);

		strcpy(productComment[i], inputCommentary);
		strcpy(productName[i], inputProdName);

		fflush(stdin);
	}

	// --------  Pegando perguntas feitas -------- 
	for (i = 0; i < numQuestions; i++) {
		scanf("%[^\n\r]\n\r", inputQuestion);

		questions[i] = (char *)malloc((strlen(inputQuestion)+1) * sizeof(char));
		if (questions[i] == NULL)
			exit(1);

		strcpy(questions[i], inputQuestion);

		fflush(stdin);
	}

	// -------- Executando o que é pedido em cada pergunta (contar palavras negativas/positivas ou frequência de determinada palavra) --------
	for (i = 0; i < numQuestions; i++) {
		int numWordsInBow = 0, numGoodSentences = 0, numBadSentences = 0, numWordsInCommentary = 0, numWordsInQuestion = 0, searchedWordFrequency = 0;
		char ** splitedQuestionString;
		char ** splitedCommentaryString;
		char * productToSearchFor;
		char * wordsFromComment[MAX_SIZE_BAGOFWORDS];
		int wordsFromCommentFrequency[MAX_SIZE_BAGOFWORDS];
		char * searchPosOrNegSentence;

		// -------- Splitando a pergunta --------
		numWordsInQuestion = splitString(questions[i], &splitedQuestionString, " ");

		// -------- Pegando nome do produto a ser procurado --------
		getProdName(&productToSearchFor, splitedQuestionString, numWordsInQuestion-2);

		// -------- Verificando se foi selecionada a primeira opção de pesquisa (frequência de determinada palavra) --------
		if (!strcmp(splitedQuestionString[0], "palavra")) {
			for (j = 0; j < numSentences; j++) {
				// -------- Cada comentário referente ao produto procurado é splitado e é montada a Bag of Words com as palavras desses comentários --------
				if (!strcmp(productName[j], productToSearchFor)) {
					numWordsInCommentary = splitString(productComment[j], &splitedCommentaryString, " ");

					BagOfWords(&splitedCommentaryString, wordsFromComment, wordsFromCommentFrequency, &numWordsInBow, &numWordsInCommentary);
				}
			}

			// -------- Buscando frequência da palavra procurada ("palavra-chave" da pergunta feita) --------
			searchedWordFrequency = getWordFrequency(&splitedQuestionString[1], wordsFromComment, wordsFromCommentFrequency, &numWordsInBow);

			// -------- Resposta para a opção 1 de pergunta (frequência de determinada palavra) --------
			printf("%d\n", searchedWordFrequency);

			for (int k = 0; k < numWordsInBow; ++k) 
				free(wordsFromComment[k]);
		}
		else {
			// -------- Verificando se foi selecionada a segunda opção de pesquisa (porcentagem de sentenças boas/ruins) --------
			if (!strcmp(splitedQuestionString[0], "quantos")) {

				// -------- String que vale "positivos" ou "negativos" => tipo de sentenças para dar a resposta --------
				searchPosOrNegSentence = splitedQuestionString[1];

				for (j = 0; j < numSentences; j++) {
					if (!strcmp(productName[j], productToSearchFor)) {
						// -------- Splitando comentário em palavras separadas (array de palavras) --------
						numWordsInCommentary = splitString(productComment[j], &splitedCommentaryString, " ");

						// -------- Contando número de sentenças positivas e negativas --------
						countNumBadAndGoodSentences(&splitedCommentaryString, &numGoodSentences, &numBadSentences, &numWordsInCommentary);
					}
				}

				// -------- Resposta para a opção 2 de pergunta (porcentagem de palavras positivas/negativas) --------
				if (!strcmp(searchPosOrNegSentence, "negativos")) {
					// -------- Exibindo porcentagem de sentenças negativas --------
					float percentageBadSentences = 100.0 * (float)numBadSentences / (numBadSentences+numGoodSentences);
					
					printf("%.1f%%\n", percentageBadSentences);
				}
				else {
					// -------- Exibindo porcentagem de sentenças positivas --------
					float percentageGoodSentences = 100.0 * (float)numGoodSentences / (numBadSentences+numGoodSentences);
					
					printf("%.1f%%\n", percentageGoodSentences);
				}
			}
			else {
				printf("Pergunta não compreendida...\n");
			}
		}

		// -------- Liberando memória HEAP --------
		for (int k = 0; k < numWordsInCommentary; ++k)
			free(splitedCommentaryString[k]);
		free(splitedCommentaryString);

		for (int k = 0; k < numWordsInQuestion; ++k)
			free(splitedQuestionString[k]);
		free(splitedQuestionString);

		free(productToSearchFor);
	}

	// -------- Liberando memória HEAP --------
	for (i = 0; i < numSentences; ++i) {
		free(productName[i]);
		free(productComment[i]);
	}

	for (i = 0; i < numQuestions; ++i) {
		free(questions[i]);
	}

	return 0;
}


