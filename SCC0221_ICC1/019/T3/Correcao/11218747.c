#include<stdio.h>
#include<stdlib.h>
#include<math.h> // somente para uso da função fabs()

// Struct com a quantidade de linhas e colunas do arquivo '.pgm' e a matriz da imagem
typedef struct _PGMData {
    int rows;
    int columns;
    int ** imageMatrix;
} PGMData;

// Struct que armazena as coordenadas referentes ao toque do usuário + o critério de segmentação usado
typedef struct _XYandCriterion {
	int xCoord;
	int yCoord;
	float segmentationCriterion;
} XYandCriterion;

// ------ Função para ler o arquivo '.pgm' ------
void readPGMFile(const char * pgmFileName, PGMData * pgmFileData) {
	FILE * pgmFileReader;

	// ------ Abrindo arquivo para leitura ------
	pgmFileReader = fopen(pgmFileName, "r");
	if (pgmFileReader == NULL) {
		printf("Falha ao abrir arquivo <%s>\n", pgmFileName);
		exit(1);
	}

	// ------ Pegando número de linhas e colunas da matriz da imagem ------
	fscanf(pgmFileReader, "P2\n%d %d\n%*d", &pgmFileData->columns, &pgmFileData->rows);

	pgmFileData->imageMatrix = (int **)malloc(pgmFileData->rows * sizeof(int *));
	if (pgmFileData->imageMatrix == NULL) {
		printf("Falha ao alocar memória para <imageMatrix>\n");
		exit(1);
	}

	// ------ Pegando valores dos pixels da imagem (de 0 a 255) ------
	for (int i = 0; i < pgmFileData->rows; ++i) {
		(pgmFileData->imageMatrix)[i] = (int *)malloc(pgmFileData->columns * sizeof(int));
		if ((pgmFileData->imageMatrix)[i] == NULL) {
			printf("Falha ao alocar memória para <imageMatrix[%d]>\n", i);
			exit(1);
		}

		for (int j = 0; j < pgmFileData->columns; ++j) {
			fscanf(pgmFileReader, "%d", &(pgmFileData->imageMatrix)[i][j]);
		}
	}
 	
	// ------ Fechando stream de leitura ------
	fclose(pgmFileReader);

   return;
}

// ------ Função recursiva para segmentar imagem (formar regiões segmentadas) ------
void constructSegmentedRegion(int currXPos, int currYPos, float segmentationCriterion, float * totalSegRegionValue, int * numPixelsInRegion, int *** segmentedImageByRegions, int queryNumber, PGMData * pgmFileData) {

	if ((*segmentedImageByRegions)[currXPos][currYPos] != 0)
		return;	
	else {
		// ------ Adicionando ponto de coordenadas (currXPos, currYPos) à região segmentada de número 'queryNumber'
		(*segmentedImageByRegions)[currXPos][currYPos] = queryNumber;
		(*numPixelsInRegion)++;
		(*totalSegRegionValue) += pgmFileData->imageMatrix[currXPos][currYPos];

		float currPixelValue;

		// ------ Verificando se o vizinho de cima atende ao critério de segmentação ------
		if (currXPos-1  >= 0) {
			currPixelValue = (float)pgmFileData->imageMatrix[currXPos-1][currYPos];
			float dif = fabs(((*totalSegRegionValue)/(*numPixelsInRegion))-currPixelValue);
			// (*totalSegRegionValue)/(*numPixelsInRegion) = média dos valores de pixel da região segmentada

			if (dif <= segmentationCriterion) { // Se atende ao critério, adiciona-se o pixel à regiao (chamando a função recursiva)
				constructSegmentedRegion(currXPos-1, currYPos, segmentationCriterion, totalSegRegionValue, numPixelsInRegion, segmentedImageByRegions, queryNumber, pgmFileData);
			}
		}

		// ------ Verificando se o vizinho da direita atende ao critério de segmentação ------
		if (currYPos+1 < pgmFileData->columns) { 
			currPixelValue = (float)pgmFileData->imageMatrix[currXPos][currYPos+1];
			float dif = fabs(((*totalSegRegionValue)/(*numPixelsInRegion))-currPixelValue);

			if (dif <= segmentationCriterion) { // Se atende ao critério, adiciona-se o pixel à regiao (chamando a função recursiva)
				constructSegmentedRegion(currXPos, currYPos+1, segmentationCriterion, totalSegRegionValue, numPixelsInRegion, segmentedImageByRegions, queryNumber, pgmFileData);
			}
		}

		// ------ Verificando se o vizinho de baixo atende ao critério de segmentação ------
		if (currXPos+1 < pgmFileData->rows) { 
			currPixelValue = (float)pgmFileData->imageMatrix[currXPos+1][currYPos];
			float dif = fabs(((*totalSegRegionValue)/(*numPixelsInRegion))-currPixelValue);

			if (dif <= segmentationCriterion) { // Se atende ao critério, adiciona-se o pixel à regiao (chamando a função recursiva)
				constructSegmentedRegion(currXPos+1, currYPos, segmentationCriterion, totalSegRegionValue, numPixelsInRegion, segmentedImageByRegions, queryNumber, pgmFileData);
			}
		}

		// ------ Verificando se o vizinho da esquerda atende ao critério de segmentação ------
		if (currYPos-1 >= 0) {
			currPixelValue = (float)pgmFileData->imageMatrix[currXPos][currYPos-1];
			float dif = fabs(((*totalSegRegionValue)/(*numPixelsInRegion))-currPixelValue);

			if (dif <= segmentationCriterion) { // Se atende ao critério, adiciona-se o pixel à regiao (chamando a função recursiva)
				constructSegmentedRegion(currXPos, currYPos-1, segmentationCriterion, totalSegRegionValue, numPixelsInRegion, segmentedImageByRegions, queryNumber, pgmFileData);
			}
		}
	}
	return;
} 

// ------ Função para determinar bordas das regiões segmentadas ------
// Retorna a quantidade de pixels que estão nas bordas das regiões segmentadas
int getSegRegionBorders(PGMData pgmFileData, int ** segmentedImageByRegions, int ** borderXCoordinates, int ** borderYCoordinates) {
	int totalBorderPixels = 0;
	int initAllocSpace = 20; // quantidade inicial de espaços que serão alocados para as coordenadas das bordas

	// ------ Vetores dinâmicos para armazenar as coordenadas das bordas ------
	(*borderXCoordinates) = (int *)malloc(initAllocSpace * sizeof(int));
	if ((*borderXCoordinates) == NULL) {
		printf("Falha ao alocar memória para <borderXCoordinates>\n");
		exit(1);
	}
	(*borderYCoordinates) = (int *)malloc(initAllocSpace * sizeof(int));
	if ((*borderYCoordinates) == NULL) {
		printf("Falha ao alocar memória para <borderYCoordinates>\n");
		exit(1);
	}

	// ------ Avaliando se cada pixel da imagem pertence ou não a uma borda ------
	for (int i = 0; i < pgmFileData.rows; ++i) {
		for (int j = 0; j < pgmFileData.columns; ++j) {
			int currPixelRegion = segmentedImageByRegions[i][j];

			// ------ Realocando espaço para os vetores se número de pixels > posições nos vetores ------
			if (totalBorderPixels+4 >= initAllocSpace) {
				initAllocSpace *= 2;
				(*borderXCoordinates) = (int *)realloc((*borderXCoordinates), initAllocSpace * sizeof(int));
				if ((*borderXCoordinates) == NULL) {
					printf("Falha ao realocar memória para <borderXCoordinates>\n");
					exit(1);
				}
				(*borderYCoordinates) = (int *)realloc((*borderYCoordinates), initAllocSpace * sizeof(int));
				if ((*borderYCoordinates) == NULL) {
					printf("Falha ao realocar memória para <borderYCoordinates>\n");
					exit(1);
				}
			}

			if (i > 0) {
				// ------ Se o pixel atual não estiver na mesma regiao que o acima dele, ele está na borda ------
				if (currPixelRegion != segmentedImageByRegions[i-1][j]) {
					(*borderXCoordinates)[totalBorderPixels] = i;
					(*borderYCoordinates)[totalBorderPixels] = j;
					totalBorderPixels++;
					continue;
				}
			}

			if (j > 0) {
				// ------ Se o pixel atual não estiver na mesma regiao que o à esquerda dele, ele está na borda ------
				if (currPixelRegion != segmentedImageByRegions[i][j-1]) {
					(*borderXCoordinates)[totalBorderPixels] = i;
					(*borderYCoordinates)[totalBorderPixels] = j;
					totalBorderPixels++;
					continue;
				}
			}

			if (i < (pgmFileData.rows)-1) {
				// ------ Se o pixel atual não estiver na mesma regiao que o abaixo dele, ele está na borda ------
				if (currPixelRegion != segmentedImageByRegions[i+1][j]) {
					(*borderXCoordinates)[totalBorderPixels] = i;
					(*borderYCoordinates)[totalBorderPixels] = j;
					totalBorderPixels++;
					continue;
				}
			}


			if (j < (pgmFileData.columns)-1) {
				// ------ Se o pixel atual não estiver na mesma regiao que o à direita dele, ele está na borda ------
				if (currPixelRegion != segmentedImageByRegions[i][j+1]) {
					(*borderXCoordinates)[totalBorderPixels] = i;
					(*borderYCoordinates)[totalBorderPixels] = j;
					totalBorderPixels++;
					continue;
				}
			}

		}
	}
	// ------ Retornando quantidade de pixels nas bordas ------
	return totalBorderPixels;
}

int main(void) {
	PGMData pgmFileData;
	XYandCriterion * queryCoordAndCriterion; // coordenadas do toque do usuário + critério de segmentação
	char * pgmFileName;
	float totalSegRegionValue;
	int numberOfQueries, totalBorderPixels, numPixelsInRegion;
	int * borderXCoordinates, * borderYCoordinates;
	int ** segmentedImageByRegions; // matriz com as 'labels' de região em cada posição

	// ------ Lendo nome do arquivo '.pgm' e número de buscas que serão feitas ------
	scanf("%ms ", &pgmFileName); // alocando dinamicamente a string em pgmFileName
	scanf("%d ", &numberOfQueries);

	queryCoordAndCriterion = (XYandCriterion *)malloc(numberOfQueries * sizeof(XYandCriterion));
	if (queryCoordAndCriterion == NULL) {
		printf("Falha ao alocar memória para <queryCoordAndCriterion>\n");
		exit(1);
	}

	// ------ Lendo informações referentes a cada busca (posição inicial + critério de segmentação) ------
	for (int i = 0; i < numberOfQueries; ++i) {
		scanf("%d %d %f", &queryCoordAndCriterion[i].xCoord, &queryCoordAndCriterion[i].yCoord, &queryCoordAndCriterion[i].segmentationCriterion);
	}

	readPGMFile(pgmFileName, &pgmFileData);

	segmentedImageByRegions = (int **)calloc(pgmFileData.rows, sizeof(int *));
	if (segmentedImageByRegions == NULL) {
		printf("Falha ao alocar memória para <segmentedImageByRegions>\n");
		exit(1);
	}

	for (int i = 0; i < pgmFileData.rows; ++i) {
		segmentedImageByRegions[i] = (int *)calloc(pgmFileData.columns, sizeof(int));
		if (segmentedImageByRegions[i] == NULL) {
			printf("Falha ao alocar memória para <segmentedImageByRegions[%d]>\n", i);
			exit(1);
		}
	}

	// ------ Efetuando segmentação para cada 'query' do usuário ------
	for (int i = 0; i < numberOfQueries; ++i) {
		int currXPos = queryCoordAndCriterion[i].xCoord, currYPos = queryCoordAndCriterion[i].yCoord, segmentationCriterion = queryCoordAndCriterion[i].segmentationCriterion;

		numPixelsInRegion = 0;
		totalSegRegionValue = 0;

		constructSegmentedRegion(currXPos, currYPos, segmentationCriterion, &totalSegRegionValue, &numPixelsInRegion, &segmentedImageByRegions, i+1, &pgmFileData);
	}

	// ------ Formando bordas das regiões de segmentação e pegando quantidade total de pixels de borda ------
	totalBorderPixels = getSegRegionBorders(pgmFileData, segmentedImageByRegions, &borderXCoordinates, &borderYCoordinates);

	if (totalBorderPixels > 0) {
		borderXCoordinates = (int *)realloc(borderXCoordinates, totalBorderPixels * sizeof(int));
		if (borderXCoordinates == NULL) {
			printf("Falha ao realocar memória para <borderXCoordinates>\n");
			exit(1);
		}
		borderYCoordinates = (int *)realloc(borderYCoordinates, totalBorderPixels * sizeof(int));
		if (borderYCoordinates == NULL) {
			printf("Falha ao realocar memória para <borderYCoordinates>\n");
			exit(1);
		}
	}

	// ------ Exibindo coordenadas das bordas ------
	for (int i = 0; i < totalBorderPixels; ++i) {
		printf("(%d, %d)\n", borderXCoordinates[i], borderYCoordinates[i]);
	}

	// ------ Liberando memória HEAP utilizada ------
	for (int a = 0; a < pgmFileData.rows; ++a) {
		free(segmentedImageByRegions[a]);
		free(pgmFileData.imageMatrix[a]);
	}
	free(segmentedImageByRegions);
	free(pgmFileData.imageMatrix);
	free(borderXCoordinates);
	free(borderYCoordinates);
	free(queryCoordAndCriterion);
	free(pgmFileName);


	return 0;
}