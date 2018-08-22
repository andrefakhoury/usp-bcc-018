#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define min(a, b) a < b ? a : b

#define SETOSA 1
#define VERSICOLOR 2
#define VIRGINICA 3

typedef struct iris {
	float valores[5];
	char esp;
} Iris;

char copiaNome(char* orig) {
	char dest[11];	
	int i;
	for (i = 1; orig[i] != '"'; i++)
		dest[i-1] = orig[i];
	dest[i-1] = '\0';

	if (strcpy(dest, "setosa") == 0) return SETOSA;
	else if (strcpy(dest, "versicolor") == 0) return VERSICOLOR;
	else if (strcpy(dest, "virginica") == 0) return VIRGINICA;
}

Iris* carregaDados(FILE* csv) {
	Iris* vet = NULL;
	float valExemplo[5];
	char especie[11];

	char *exemplo, *atributo;

	//Ignora a primeira linha do csv
	while(fgetc(csv) != '\n');
	
	int qtd = 0;
	while(fscanf(csv, " %m[^\n]", &exemplo) != EOF) {
		qtd++;
		vet = (Iris*) realloc(vet, qtd * sizeof(Iris));		

		atributo = strtok(exemplo, ",");
		int ind = 0;
		while(atributo != NULL) {
			if (atributo[0] != '"') {
				sscanf(atributo, "%f", &vet[qtd-1].valores[ind]);
				ind++;
			} else {
				vet[qtd-1].esp = copiaNome(atributo);
			}
			atributo = strtok(NULL, ",");
		}
	}
	return vet;
}

char kNN(Iris* Dados, Iris exemplo, int vizinhos) {
	int menorInd;










	return SETOSA;
}

int main() {
	FILE *ftrain, *ftest;
	char nomeArq[30];
	int numVizinhos;
	
	scanf("%s ", nomeArq);
	ftrain = fopen(nomeArq, "r");
	
	scanf("%s ", nomeArq);
	ftest = fopen(nomeArq, "r");
	
	scanf("%d", &numVizinhos);

	Iris* train = carregaDados(ftrain);
	Iris* test = carregaDados(ftest);

	
	
	fclose(ftrain);
	fclose(ftest);
	return 0;	
}
