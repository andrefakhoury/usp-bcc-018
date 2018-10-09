/*	Calculadora de expressões aritméticas
	Programa que, dado uma sequência de prioridades de operadores e uma lista
	de expressões aritméticas, verifica se estas são expressões válidas e imprime
	todos os resultados na tela, a partir da montagem de uma árvore de resolução das
	operações.

		André Fakhoury - 4482145
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"

#define qttOperation 5
#define MAXOPERATION 1024

typedef struct order {
	int o[qttOperation];
} order;

typedef struct node {
	double val;
	char op;
	node *left, *right;
} node;

bool isNumber(char c) {
	return (c >= '0' && c <= '9') || c == '.';
}

bool isDelimiter(char c) {
	return c == '{' || c == '}' || c == '(' || c == ')' || c == '[' || c == ']';
}

void beautify(char* op) {
	char* aux = (char*) malloc(MAXOPERATION * sizeof(char));
	int ind = 0;
	for (int i = 0; op[i] != ',' && op[i] != ';'; i++) {
		if (op[i] == '-' || op[i] == '+' || op[i] == '/') {
			aux[ind++] = op[i];
			aux[ind++] = ' ';
		} else if (op[i] == '*' && op[i+1] == '*') {
			aux[ind++] = '^';
			aux[ind++] = ' ';
		} else if (op[i] == '*') {
			aux[ind++] = '*';
			aux[ind++] = ' ';
		} else if (op[i] == 'l') {
			aux[ind++] = 'l';
			i += 2;
		} else if (op[i] == 's') {
			aux[ind++] = 's';
			aux[ind++] = ' ';
			aux[ind++] = '{';
			aux[ind++] = ' ';
			i += 3;
		} else if (isNumber(op[i])) {
			aux[ind++] = op[i];
			if (!isNumber(op[i+1]))
				aux[ind++] = ' ';
		} else if (isDelimiter(op[i])) {
			aux[ind++] = op[i];
			aux[ind++] = ' ';
		}
	}
	aux[ind] = '\0';

	strcpy(op, aux);
	free(aux);
}

bool compareDelimiter(char a, char b) {
	if (a == '(') return b == ')';
	if (a == '{') return b == '}';
	if (a == '[') return b == ']';
	if (a == ')') return b == '(';
	if (a == '}') return b == '{';
	if (a == ']') return b == '[';
	return false;
}


bool checkExpression(char* op) {
	bool lastWasOperator = true;

	bool ret = true;

	stack* s = create_stack(sizeof(char));

	for (int i = 0; op[i] != '\0'; i++) {
		if (isDelimiter(op[i])) {
			if (op[i] == '(' || op[i] == '{' || op[i] == '[') {
				push_stack(s, op+i);
			} else {
				void* _top = top_stack(s);
				char top;
				if (_top != NULL) {
					memcpy(&top, _top, sizeof(char));
				} else {
					ret = false;
					break;
				}

				if (compareDelimiter(op[i], top)) {
					pop_stack(s);
				} else {
					ret = false;
					break;
				}
			}
			lastWasOperator = false;
		} else if (!isNumber(op[i]) && op[i] != ' ') {
			if (lastWasOperator) {
				printf(" %c ", op[i]);
				ret = false;
				break;
			}

			lastWasOperator = true;
		} else if (op[i] != ' ') {
			lastWasOperator = false;
		}
	}

	if (!empty_stack(s))
		ret = false;

	destroy_stack(s);
	return ret;
}

double numFromString(char* s, int n) {
	char temp[MAXOPERATION];
	for (int i = 0; i < n && s[i] != ' ' && s[i] != '\0'; i++)
		temp[i] = s[i];
	temp[i] = '\0'
	double ret;
	sscanf(temp, "%lf", &ret);
	return ret;
}

node* buildTree(char* s, int n) {
	if (n < 0)
		return NULL;

	if (n == 1) {
		
	}

	int low = -1;
	bool onlyOneNumber = true;
	for (int i = 0; i < n; i++) { //search for the lower expression operator
		if (!isNumber(s[i])) onlyOneNumber = false;
	}

	if (onlyOneNumber) {
		node* n = (node*) malloc(sizeof(node));
		n->val = numFromString(s, n);
		n->op = -1;
		n->right = n->left = NULL;
		return n;
	}

	if (low == -1)
		return buildTree(s+1, n-1);
	else {
		node* n = (node*) malloc(sizeof(node));
		n->val = -1;
		n->op = s[low];
		n->left = buildTree(s, low);
		n->right = buildTree(s+low, n-low);
		return n;
	}
}

double solveAndFreeTree(node* t) {
	
}


int main() {
	char operators[qttOperation][2];
	
	//read the operators
	for (int i = 0; i < qttOperation; i++) {
		scanf(" %s", operators[i]);
		printf("%s\n", operators[i]);
	}

	char* operation = (char*) malloc(MAXOPERATION * sizeof(char));
	while(scanf(" %s", operation) != EOF) {
		beautify(operation);
		printf("%s\n", operation);
		if (!checkExpression(operation)) {
			printf("Expressão incorreta.\n");
		} else {
			node* root = buildTree(operation, strlen(operation));
			printf("%.2lf\n", solveAndFreeTree(root));
		}
	}

	return 0;
}