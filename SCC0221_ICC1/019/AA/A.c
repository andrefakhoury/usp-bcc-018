#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Pessoa {
	
} Pessoa;

int main(int argc, char* argv[]) {
	printf("Numero de argumentos: %d\n\n", argc);

	// int argumento;

	char* string = "aysgyausd";

	int num1 = atoi(string);
	int num2 = 0;
	sscanf(string, "%d", &num2);

	printf("Num1: %d\n", num1);
	printf("Num2: %d\n", num2);
}

// 1 

// 49 49

// 293