/* 	Programa que realiza um aprendizado de máquina, utilizando o algoritmo
	"kNN k-Nearest Neighbour" para classificar diferentes espécies da flor Íris.

	André Fakhoury, 4482145
	USP Sao Carlos, 2018 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//macro do tamanho máximo da string dos tipos de Íris
#define espSize 20

//especies de Íris possíveis
typedef enum {
	setosa, versicolor, virginica, undefined
} typeofIris;

/* Armazena os dados das flores.
	values[] = comprimento e largura das sépalas e pétalas.
	esp = tipo da Íris, definido pelo enum typeofIris. */
typedef struct {
	float values[5];
	typeofIris esp;
} Iris;

/* Armazena a distância e índice do valor */
typedef struct {
	float dist;
	int ind;
} Distance;

/* Retorna o tipo da flor mandada por parâmetro (converte de string para o tipo da flor)
	Parâmetros: char* orig - ponteiro para string original contendo a espécie da flor
	Retorno: macro da especie referente a esse tipo */
typeofIris strToIris(char* orig) {
	if (strcmp(orig, "setosa") == 0) return setosa;
	else if (strcmp(orig, "versicolor") == 0) return versicolor;
	else if (strcmp(orig, "virginica") == 0) return virginica;
	return undefined;
}

/* Seta o tipo da flor de acordo com macro correspondente em uma string mandada por parâmetro.
	Parâmetros:
		char esp: espécie contendo o macro da espécie (1, 2, ou 3).
		char str[]: string de destino, recebe o texto referente a espécie mandada no parâmetro anterior. */
void fillStringWithType(typeofIris esp, char str[espSize]) {
	if (esp == setosa)
		strcpy(str, "setosa");
	else if (esp == versicolor)
		strcpy(str, "versicolor");
	else if (esp == virginica)
		strcpy(str, "virginica");
	else
		strcpy(str, "erro");
}

/* Realiza o carregamento de arquivo csv.
	Parâmetros:
		FILE* csv - ponteiro para o arquivo csv, de onde serão lidos os dados
		int* qtt - ponteiro para um inteiro, que armazenará a quantidade de dados lidos.
	Retorno:
		Iris* - ponteiro para vetor de Iris, com os dados lidos do csv. */
Iris* loadData(FILE* csv, int* qtt) {
	Iris* vet = NULL;
	char name[espSize];
	float val[4];

	while(fgetc(csv) != '\n'); //Ignora a primeira linha do csv
	
	int pos;
	*qtt = 0;

	while(fscanf(csv, "%f,%f,%f,%f,\"%20[^\"]\" ", &val[0], &val[1], &val[2], &val[3], name) != EOF) {
		(*qtt)++;
		vet = (Iris*) realloc(vet, (*qtt) * sizeof(Iris));
		pos = (*qtt)-1;

		for (int i = 0; i < 4; i++)
			vet[pos].values[i] = val[i];

		vet[pos].esp = strToIris(name);
		if (vet[pos].esp == undefined) {
			vet = NULL;
			break;
		}
	}

	return vet;
}

/* Realiza a ordenação das distâncias pelo método Insertion Sort.
	Parâmetros:
		Distance* vecDist - ponteiro para vetor de distâncias;
		int total - tamanho total do vetor. */
void sortDistances(Distance* vecDist, int total) {
	int i = 1;
	while(i < total) {
		float key = vecDist[i].dist;
		int ind = vecDist[i].ind;

		int j = i-1;
		while(j >= 0 && key < vecDist[j].dist) {
			vecDist[j+1].dist = vecDist[j].dist;
			vecDist[j+1].ind = vecDist[j].ind;
			j--;
		}

		vecDist[j+1].dist = key;
		vecDist[j+1].ind = ind;
		i++;	
	}
}

/* Calcula a distância euclidiana de dois pontos (de dados e de exemplo).
	Parâmetros:
		float data[], example[] - vetores para calcular a distância
	Retorno: quadrado da distância euclidiana dos pontos. Nao foi retornada a
		distancia euclidiana pois a função sqrt() é muito lenta. */
float calcDistance(float data[4], float example[4]) {
	float dist = 0;
	for (int i = 0; i < 4; i++)
		dist += (data[i]-example[i]) * (data[i]-example[i]);

	return dist;
}

/* Compara a quantidade de flores de cada espécie (feita no kNN) e retorna a classe mais representativa.
	Parâmetros: quantidade de setosas, versicolors e virginicas; distâncias mínimas de cada classe.
	Retorno: caractere representativo desta classe. */
typeofIris compareFlowers(int qtSeto, int qtVers, int qtVirg, float minSeto, float minVers, float minVirg) {
	if (qtSeto > qtVers && qtSeto > qtVirg) return setosa;
	if (qtVers > qtSeto && qtVers > qtVirg) return versicolor;
	if (qtVirg > qtSeto && qtVirg > qtVers) return virginica;

	if (qtSeto == qtVers) {
		if (minSeto < minVers) return setosa;
		return versicolor;
	}

	if (qtSeto == qtVirg) {
		if (minSeto < minVirg) return setosa;
		return virginica;
	}
	
	if (qtVers == qtVirg) {
		if (minVers < minVirg) return versicolor;
		return virginica;
	}

	return undefined; //Ocorreu algum erro
}

/* Calcula a classe mais representativa de certa flor, de acordo com os casos de treino.
	Parâmetros:
		Iris* data - ponteiro para vetor de flores de treino;
		Iris test - flor a ser testada;
		int nData - quantidade de casos de treino;
		int k - número de vizinhos que devem ser analisados. */
char kNN(Iris* data, Iris test, int nData, int k) {
	Distance* distances = malloc(nData * sizeof(Distance));

	for (int i = 0; i < nData; i++) {
		distances[i].dist = calcDistance(data[i].values, test.values);
		distances[i].ind = i; 
	}

	sortDistances(distances, nData);

	int qtSetosa = 0, qtVersicolor = 0, qtVirginica = 0;
	int idSetosa = -1, idVersicolor = -1, idVirginica = -1;

	//calcula a quantidade de flores de cada tipo, nos k vizinhos mais próximos
	for (int i = k-1; i >= 0; i--) {
		char irisType = data[distances[i].ind].esp;
		if (irisType == setosa) {
			qtSetosa++;
			idSetosa = i;
		} else if (irisType == versicolor) {
			qtVersicolor++;
			idVersicolor = i;
		} else if (irisType == virginica) {
			qtVirginica++;
			idVirginica = i;
		}
	}

	float minSetosa = distances[idSetosa].dist;
	float minVersicolor = distances[idVersicolor].dist;
	float minVirginica = distances[idVirginica].dist;

	free(distances);

	return compareFlowers(qtSetosa, qtVersicolor, qtVirginica, minSetosa, minVersicolor, minVirginica);
}

int main() {
	FILE* ftrain = NULL;
	FILE* ftest = NULL;
	char fileName[1024];
	int neighbours, nTrain, nTest;
	
	scanf("%1024s ", fileName);
	ftrain = fopen(fileName, "r");
	if (ftrain == NULL) //Ocorreu algum erro ao abrir o arquivo
		return 1;
	
	scanf("%1024s ", fileName);
	ftest = fopen(fileName, "r");
	if (ftest == NULL) //Ocorreu algum erro ao abrir o arquivo
		return 1;
	
	Iris* train = loadData(ftrain, &nTrain);
	if (train == NULL) //Ocorreu algum erro na leitura do arquivo
		return 1;

	Iris* test = loadData(ftest, &nTest);
	if (test == NULL) //Ocorreu algum erro na leitura do arquivo
		return 1;
	
	scanf("%d", &neighbours);

	if (neighbours > nTrain) {
		printf("k is invalid\n");
		return 0;
	}

	int rightAns = 0;
	for (int i = 0; i < nTest; i++) {
		char cKNN[espSize], cOTH[espSize];
		
		typeofIris typeKNN = kNN(train, test[i], nTrain, neighbours);
		if (typeKNN == undefined) //Ocorreu erro no calculo do KNN
			return 1;
		
		fillStringWithType(typeKNN, cKNN);
		fillStringWithType(test[i].esp, cOTH);
		printf("%s %s\n", cKNN, cOTH);
		
		if (typeKNN == test[i].esp)
			rightAns++;
	}
	
	printf("%.4f\n", rightAns/(float)nTest);

	fclose(ftrain);
	fclose(ftest);
	free(train);
	free(test);

	return 0;
}