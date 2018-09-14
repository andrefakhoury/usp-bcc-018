#include <stdio.h>

#define strSize 1024
#define wordSize 45

//.,!?"\n&...’’;@#

#define ERROR 1

void reallocDictionary(char*** d, int oldSize, int newSize) {
	(*d) = (char**) realloc((*d), newSize * sizeof(char**));
	
	for (int i = oldSize; i < newSize; i++)
		(*d)[i] = (char*) malloc(wordSize * sizeof(char));
}


int main() {
	
	char fileName[strSize];
	FILE *fBook = NULL, *fp = NULL;

	scanf(" %s", fileName);
	fBook = fopen(fileName, "r");
	if (fBook == NULL)
		return ERROR;

	scanf(" %s", fileName);
	fp = fopen(fileName, "r");
	if (fp == NULL)
		return ERROR;

	char** dict = NULL;

	reallocDictionary(&dict, 0, 500);

	//OBS: no armazenamento, ignorar caracteres especiais

	//ler todas as palavras do dicionario e armazenar

	//ler todas as palavras do tweet e fazer busca binaria

	//pegar as palavras que nao existem e printar

}