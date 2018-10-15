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
#include <math.h>
#include "stack.h"

#define qttOperation 5 /* Numero maximo de operandos */
#define MAXOPERATION 2048 /* Numero maximo de caracteres da expressao */

/*	Struct para cada no da arvore, que tera seu valor (numeral ou caractere representativo da expressao)
	e seus dois filhos (se for unaria, tera apenas o filho da esquerda); */
typedef struct node {
	double val;
	char op;
	struct node *left, *right;
} node;

//retorna TRUE se o caractere c enviado for um numero ou ponto
bool isNumber(char c) {
	return (c >= '0' && c <= '9') || c == '.';
}

//retorna TRUE se o caractere enviado for um delimitador (){}[]
bool isDelimiter(char c) {
	return c == '{' || c == '}' || c == '(' || c == ')' || c == '[' || c == ']';
}

//deixa a expressao de uma maneira mais limpa para ser manipulada
//exemplo: log{3+4**2} vira l{3+4^2}
void beautify(char* op) {
	char* aux = (char*) malloc(MAXOPERATION * sizeof(char));
	int ind = 0;
	for (int i = 0; op[i] != ',' && op[i] != ';'; i++) {
		if (op[i] == '-' || op[i] == '+' || op[i] == '/') {
			aux[ind++] = op[i];
		} else if (op[i] == '*' && op[i+1] == '*') {
			aux[ind++] = '^';
			i++;
		} else if (op[i] == '*') {
			aux[ind++] = '*';
		} else if (op[i] == 'l') {
			aux[ind++] = 'l';
			aux[ind++] = op[i+3];
			i += 3;
		} else if (op[i] == 's') {
			aux[ind++] = 's';
			aux[ind++] = op[i+4];
			i += 4;
		} else if (op[i] == 'e') {
			aux[ind++] = 'e';
			aux[ind++] = op[i+3];
			i += 3;
		} else if (isNumber(op[i])) {
			aux[ind++] = op[i];
		} else if (isDelimiter(op[i])) {
			aux[ind++] = op[i];
		}
	}
	aux[ind] = '\0';

	strcpy(op, aux);
	free(aux);
}

//compara se os caracteres enviados representam o mesmo delimitador, abrindo ou fechando
bool compareDelimiter(char a, char b) {
	if (a == '(') return b == ')';
	if (a == '{') return b == '}';
	if (a == '[') return b == ']';
	if (a == ')') return b == '(';
	if (a == '}') return b == '{';
	if (a == ']') return b == '[';
	return false;
}


//checa se uma expressao e valida (operandos em posicao certa, delimitadores corretos, etc)
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
		} else if (!isNumber(op[i]) && op[i] != 's' && op[i] != 'e' && op[i] != 'l' && op[i] != ' ') {
			if (lastWasOperator) {
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

//retorna um double a partir de uma string de tamanho n
double numFromString(char* s, int n) {
	char temp[MAXOPERATION];
	int i;
	for (i = 0; i < n && isNumber(s[i]) && s[i] != '\0'; i++)
		temp[i] = s[i];
	temp[i] = '\0';
	double ret;
	sscanf(temp, "%lf", &ret);
	return ret;
}

//constroi uma arvore de forma recursiva.
//a cada chamada, e procurada a expressao de menor valor aritmetico, e a partir dela, sao feitos os filhos da esquerda e direita
node* buildTree(char* s, int n, char* order) {
	if (n < 0)
		return NULL;

	if (n == 1) {
		
	}

	int low = -1;
	bool onlyOneNumber = true;

	//search for the lower expression operator
	stack* stk = create_stack(sizeof(char));
	for (int k = 0; k < qttOperation; k++) {
		for (int i = 0; i < n; i++) {

			if (isDelimiter(s[i])) {
				if (s[i] == '(' || s[i] == '{' || s[i] == '[')
					push_stack(stk, s+i);
				else
					pop_stack(stk);
			}

			if (empty_stack(stk)) {
				if (!isNumber(s[i]) && s[i] != ' ' && onlyOneNumber)
					onlyOneNumber = false;
				if (s[i] == order[k]) low = i;
			}

		}
	}
	destroy_stack(stk);

	if (onlyOneNumber) {
		node* nd = (node*) malloc(sizeof(node));
		nd->val = numFromString(s, n);
		nd->op = -1;
		nd->right = nd->left = NULL;
		return nd;
	}

	if (low == -1) {
		if (s[0] == 'l' || s[0] == 'e' || s[0] == 's') {
			node* nd = (node*) malloc(sizeof(node));
			nd->val = -1;
			nd->op = s[0];
			nd->left = buildTree(s+2, n-3, order);
			nd->right = NULL;
			return nd;
		}

		return buildTree(s+1, n-2, order);
	}
	else {
		node* nd = (node*) malloc(sizeof(node));
		nd->val = -1;
		nd->op = s[low];
		nd->left = buildTree(s, low, order);
		nd->right = buildTree(s+low+1, n-low-1, order);
		return nd;
	}
}

//a partir da arvore formada, resolve as operacoes de forma recursiva e desaloca os nos.
double solveAndFreeTree(node* t, bool* error) {
	double ret = 0;
	if (t == NULL) return 0;
	if (t->val != -1 && t->op == -1) ret = t->val;
	else {
		if (t->op == '+')
			ret = solveAndFreeTree(t->left, error) + solveAndFreeTree(t->right, error);
		else if (t->op == '-')
			ret = solveAndFreeTree(t->left, error) - solveAndFreeTree(t->right, error);
		else if (t->op == '/') {
			double v1 = solveAndFreeTree(t->left, error);
			double v2 = solveAndFreeTree(t->right, error);
			if (v2 != 0) ret = v1/v2;
			else *error = true;
		}
		else if (t->op == '*')
			ret = solveAndFreeTree(t->left, error) * solveAndFreeTree(t->right, error);
		else if (t->op == '^')
			ret = pow(solveAndFreeTree(t->left, error), solveAndFreeTree(t->right, error));
		else if (t->op == 'l') {
			double v = solveAndFreeTree(t->left, error);
			if (v <= 0) *error = true;
			else ret = log2(v);
		}
		else if (t->op == 's') {
			double v = solveAndFreeTree(t->left, error);
			if (v < 0) *error = true;
			else ret = sqrt(v);
		}
		else if (t->op == 'e')
			ret = exp(solveAndFreeTree(t->left, error));
	}

	free(t);
	return ret;
}

int main() {
	char operators[qttOperation][3]; 
	char order[qttOperation];
	
	//Le os operadores e guarda a ordem de relevancia
	for (int i = 0; i < qttOperation; i++) {
		scanf(" %s", operators[i]);

		if (!strcmp(operators[i], "**"))
			order[i] = '^';
		else
			order[i] = operators[i][0];
	}

	char* operation;
	while(scanf(" %m[^\n\r]", &operation) != EOF) {
		beautify(operation);
		if (!checkExpression(operation)) {
			printf("Expressao incorreta.\n");
		} else {
			node* root = buildTree(operation, strlen(operation), order);
			bool error = false;
			double v = solveAndFreeTree(root, &error);
			if (!error)
				printf("%.2lf\n", v);
			else
				printf("Expressao incorreta.\n");
		}
		free(operation);
	}

	return 0;
}