#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define wordSize 45
#define alphabetSize 26

#define ERROR 1

//Node of a Trie
typedef struct _node {
	bool isEndOfWord;
	struct _node* next[alphabetSize];
} Node;

Node* initNode() {
	Node* n = (Node*) malloc(sizeof(Node));
	n->isEndOfWord = false;
	for (int i = 0; i < alphabetSize; i++)
		n->next[i] = NULL;
	return n;
}

void destroyNode(Node* n) {
	for (int i = 0; i < alphabetSize; i++)
		if (n->next[i])
			destroyNode(n->next[i]);
	free(n);
}

bool checkChar(char c) {
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int intFromChar(char c) {
	return c-'a' < 0 ? c-'A' : c-'a';
}

void insertInTrie(Node* begin, char* word) {
	Node* trie = begin;

	for (int i = 0; word[i] != '\0'; i++) {
		if (checkChar(word[i])) {
			int position = intFromChar(word[i]);
			if (!trie->next[position])
				trie->next[position] = initNode();
			trie = trie->next[position];
		} else {
			trie->isEndOfWord = true;
			trie = begin;
			continue;
		}
	}

	trie->isEndOfWord = true;
}

bool isEndOfBlock(char* word) {
	int i;
	for (i = 0; word[i] != '\0'; i++);
	return (i >= 2 && word[i-1] == ',' && word[i-2] == '\"');
}

void readDictionary(FILE* fp, Node* trie) {
	char* word;

	while(fscanf(fp, " %ms", &word) != EOF) {
		insertInTrie(trie, word);
		free(word);
	}
}

void printWord(char* word) {
	int i;
	for (i = 0; word[i] != '\0'; i++) {
		if (checkChar(word[i]))
			printf("%c", word[i]);
	}
	if (i > 0)
		printf(" ");
}

void findInTrie(Node* begin, char* word) {
	Node* trie = begin;
	char aux[wordSize];
	int ind = 0;
	bool isInTrie = true;

	for (int i = 0; word[i] != '\0'; i++) {
		if (checkChar(word[i])) {
			aux[ind++] = word[i];
			int position = intFromChar(word[i]);

			if (!trie->next[position])
				isInTrie = false;

			if (isInTrie)
				trie = trie->next[position];
		} else {
			if (!trie->isEndOfWord)
				isInTrie = false;

			if (ind > 0 && !isInTrie) {
				aux[ind] = '\0';
				printWord(aux);
			}
			trie = begin;
			isInTrie = true;
			ind = 0;
		} 
	}
	aux[ind] = '\0';
	if (!trie->isEndOfWord || !isInTrie)
		printWord(aux);
}

bool readTweets(FILE* fp, Node* trie) {
	char* word;
	int tweetCount = 0;

	while(fscanf(fp, " %ms", &word) != EOF) {
		if (!strcmp(word, "\"text\":")) {
			tweetCount++;

			free(word);

			while(fscanf(fp, " %ms", &word) > 0) {
				findInTrie(trie, word);

				if (isEndOfBlock(word))
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
	if (fBook == NULL)
		return ERROR;
	free(fileName);

	scanf("%ms ", &fileName);
	fp = fopen(fileName, "r");
	if (fp == NULL)
		return ERROR;
	free(fileName);

	Node* trieBegin = initNode();

	readDictionary(fBook, trieBegin);
	if (!readTweets(fp, trieBegin)) {
		printf("No tweets to check\n");
	}

	fclose(fBook);
	fclose(fp);
	destroyNode(trieBegin);
}