#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 0
#define alphabetSize 26
#define maxSize 100

typedef struct _node{
	int endWord;
	struct _node* nextLetter[alphabetSize + 1];
} node;

int validChar(char letter){
	if(letter < 'A' || letter > 'z')
		return 0;
	else if(letter > 'Z' && letter < 'a')
		return 0;
	else
		return 1;
}

void startNode(node* n){
	for(int j = 0; j < alphabetSize; j++){
		n->nextLetter[j] = NULL;
	}
}

void destroyTrie(node* n){	
	for(int j = 0; j < alphabetSize; j++){
		if(n->nextLetter[j] != NULL)
			destroyTrie(n->nextLetter[j]);
	}
	free(n);
}


//O(WordSize)
int serchWord(node* root, char* word, int wordSize){
	int pos;
	
	for(int i = 0; i < wordSize; i++){
		if(word[i] < 'a') 
			pos = word[i] - 'A';
		else
			pos = word[i] - 'a';

		if(root->nextLetter[pos] == NULL) {
			printf("%s ", word);
			return 0;
		}
		else
			root = root->nextLetter[pos];
	}
	
	if(root->endWord == 1)
		return 1;
	else{
		printf("%s ", word);
		return 0;
	}
}

void loadTweets(FILE* fp, node* root){
	int size = 0;
	char* word = malloc(sizeof(char) * maxSize);
	char aux = fgetc(fp);
	aux = fgetc(fp);
	
	while(aux != '\n'){
		if(aux == ' ') {
			word[size] = '\0';
			if(size != 0)
				serchWord(root, word, size);
			size = 0;
		}
		else if(validChar(aux)){
			word[size] = aux;
			size++;
		}
		aux = fgetc(fp);
	}
	free(word);
}

void loadJson(char* fileName, node* root){
	int size = 0;
	FILE* fp = NULL;
	fp = fopen(fileName, "r");
	char* word = malloc(sizeof(char) * maxSize);
	
	while(!feof(fp)){	
		char aux = fgetc(fp);
		if(aux == ' ' || aux == '\n') {
			word[size] = '\0';
			
			if(!strcmp(word, "text")){
				loadTweets(fp, root);
				printf("\n");
			}
			
			size = 0;
		}
		
		else if(validChar(aux)){
			word[size] = aux;
			size++;
		}
	}
	free(word);
	fclose(fp);
}

//O(n * alphabetSize)
void insertWord(node* root, char* word, int wordSize){
	int pos = 0;
	for(int i = 0; i < wordSize; i++){	
		
		if(word[i] >= 'a') 
			pos = word[i] - 'a';
		else 
			pos = word[i] - 'A';
		
		if(root->nextLetter[pos] == NULL){
			node* n = malloc(sizeof(node));
			
			startNode(n);
			
			n->endWord = 0;
			root->nextLetter[pos] = n;
			root = n;
		} else
			root = root->nextLetter[pos];
	}

	root->endWord = 1;
}	

void loadDictionary(char* fileName, node* root){
	int size = 0;
	FILE* fp = NULL;
	fp = fopen(fileName, "r");
	
	char* word = malloc(sizeof(char) * maxSize);
	
	while(!feof(fp)){
		char aux = fgetc(fp);
		if(aux == ' ' || aux == '\n') {
			insertWord(root, word, size);
			size = 0;
		}
		else if(validChar(aux)){
			word[size] = aux;
			size++;
		}
	}
	free(word);
	fclose(fp);
}

int main(int argc, const char *argv[]){
	node* root = malloc(sizeof(node));
	startNode(root);

	char* fileName = malloc(sizeof(char) * maxSize);

	scanf("%s ", fileName);
	loadDictionary(fileName, root);

	scanf("%s", fileName);
	loadJson(fileName, root);
	
	free(fileName);
	destroyTrie(root);

	return 0;
}