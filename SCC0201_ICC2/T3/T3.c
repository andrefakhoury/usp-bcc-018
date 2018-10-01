/* Programa que localiza palavras incorretas em um arquivo .JSON, de acordo com um conjunto de palavras em um dicionário .TXT
 * 	André Fakhoury, 4482145
 * 	
 * 	Foi utilizado uma trie para a inserção e busca das palavras, pois apresenta complexidade de tempo menor.
 * 	
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define wordSize 45
#define alphabetSize 26

#define ERROR 1

//Estrutura de cada nó da trie
typedef struct _node {
	bool isEndOfWord; //representa se o no apresenta o fim de uma palavra
	struct _node* next[alphabetSize]; //filhos de cada no
} Node;

//Cria um nó na Trie
Node* createNode() {
	Node* n = (Node*) malloc(sizeof(Node));
	n->isEndOfWord = false;

	//cada no da Trie possui um ponteiro para cada outra letra do alfabeto
	for (int i = 0; i < alphabetSize; i++)
		n->next[i] = NULL;
	return n;
}

//Desaloca um nó da trie e todos os seus filhos.
void destroyNode(Node* n) {
	for (int i = 0; i < alphabetSize; i++)
		if (n->next[i])
			destroyNode(n->next[i]);
	free(n);
}

//Retorna se o caractere enviado por parâmetro é uma letra válida de A a Z, maiúscula ou minúscula
bool checkChar(char c) {
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

//Retorna a ordem no alfabeto de um caractere (ignorando maiúsculas e minúsculas) - 0 Based
int intFromChar(char c) {
	return c-'a' < 0 ? c-'A' : c-'a';
}

//Insere uma palavra na trie
//O(M), em que M = Tamanho da palavra
void insertInTrie(Node* root, char* word) {
	Node* trie = root;

	for (int i = 0; word[i] != '\0'; i++) {
		if (checkChar(word[i])) {
			int position = intFromChar(word[i]);
			if (!trie->next[position])
				trie->next[position] = createNode();
			trie = trie->next[position];
		} else { //cada caractere especial representa o fim de uma palavra
			trie->isEndOfWord = true;
			trie = root;
			continue;
		}
	}

	trie->isEndOfWord = true;
}

//Lê um dicionário de arquivos e armazena suas palavras na trie
//O(N*M), em que N = numero de strings no arquivo e M = tamanho da palavra
void readDictionary(FILE* fp, Node* trie) {
	char* word;

	while(fscanf(fp, " %ms", &word) != EOF) {
		insertInTrie(trie, word);
		free(word);
	}
}

//Imprime uma palavra, ignorando os caracteres inválidos
//O(M), em que M = tamanho da palavra
void printWord(char* word) {
	int i;
	for (i = 0; word[i] != '\0'; i++) {
		if (checkChar(word[i]))
			printf("%c", word[i]);
	}
	if (i > 0)
		printf(" ");
}

//Procura uma string na trie
//O(M), em que M = tamanho da palavra
void findInTrie(Node* root, char* word) {
	Node* trie = root;
	char aux[wordSize];
	int ind = 0;
	bool isInTrie = true;

	//percorre a string, armazenando os caracteres validos de cada palavra em uma string auxiliar
	for (int i = 0; word[i] != '\0'; i++) {

		if (checkChar(word[i])) {
			aux[ind] = word[i];
			int position = intFromChar(word[i]);

			if (!trie->next[position])
				isInTrie = false;

			if (isInTrie)
				trie = trie->next[position];

			ind++;
		} else { //caracteres invalidos representam o fim das palavras
			if (!trie->isEndOfWord)
				isInTrie = false;

			if (ind > 0 && !isInTrie) {
				aux[ind] = '\0';
				printWord(aux);
			}
			trie = root;
			isInTrie = true;

			ind = 0;
		} 
	}
	aux[ind] = '\0';
	if (!trie->isEndOfWord || !isInTrie)
		printWord(aux);
}

//Retorna se uma string representa o fim de um bloco de texto do arquivo JSON
//O(M), em que M = tamanho da palavra
bool isEndOfBlock(char* word) {
	int i;
	for (i = 0; word[i] != '\0'; i++);
	return (i >= 2 && word[i-1] == ',' && word[i-2] == '\"');
}

//A partir de um arquivo JSON, localiza as palavras contidas nos tweets e as procura na trie
//Retorna FALSE caso não forem localizados tweets, e TRUE caso contrário.
//O(N*M), em que N = numero de strings no arquivo e M = tamanho da palavra
bool readTweets(FILE* fp, Node* root) {
	char* word;
	int tweetCount = 0;

	while(fscanf(fp, " %ms", &word) != EOF) {
		if (!strcmp(word, "\"text\":")) {
			tweetCount++;

			free(word);

			while(fscanf(fp, " %ms", &word) > 0) { //enquanto o fscanf for bem sucedido
				findInTrie(root, word);

				if (isEndOfBlock(word)) //caso termine com ' ", ' a string indica fim do texto do tweet
					break;

				free(word);
			}
			printf("\n");
		}

		free(word);
	}

	return tweetCount > 0;
}

int main(int argc, const char *argv[]) {
	char* fileName;
	FILE *fBook = NULL, *fp = NULL;
	
	scanf("%ms ", &fileName);
	fBook = fopen(fileName, "r");
	free(fileName);
	if (fBook == NULL)
		return ERROR;

	scanf("%ms ", &fileName);
	fp = fopen(fileName, "r");
	free(fileName);
	if (fp == NULL)
		return ERROR;

	Node* trieRoot = createNode(); //cria a raiz da trie

	readDictionary(fBook, trieRoot); //le o dicionario e forma a trie
	if (!readTweets(fp, trieRoot)) 	 //le os tweets e procura suas palavras na trie
		printf("No tweets to check\n");

	fclose(fBook);
	fclose(fp);
	destroyNode(trieRoot);
	
	return 0;
}