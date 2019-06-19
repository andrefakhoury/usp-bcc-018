#include <stdio.h>
#include <stdlib.h>

float absolute(float n){ // fiz uma função para obter valores absolutos (sem nenhum motivo por que eu poderia ter usado abs())

	if(n<0) n= n*-1;

	return n;
}

void postergar(FILE* arquivo){ //nessa função eu ignoro as informações irrelevantes do inicio de cada imagem
	char trash;
	do{
		trash= (char) fgetc(arquivo);
	}while(trash != '\n' && trash != '\r');
}

void segmentar(int linhas, int colunas, int y, int x, int* parametro, int* m, int criterio, int* pixel[colunas]){ // nessa função eu faço o tratamento dos pixels da imagem
	

	*m+=*(*(pixel+y)+x);                  //o m e o parametro são variaveis auxiliares para que eu possa calcular a media acumulativa de cada segmentação
	*parametro= *parametro+1;
	float media = *m / (float) *parametro;

	*(*(pixel+y)+x)=-1;	

	if (y-1>=0 && *(*(pixel+y-1)+x)>=0){                                        
		if(absolute( *(*(pixel+y-1)+x)-media ) <= criterio){
			segmentar(linhas, colunas, y-1, x, parametro, m, criterio, pixel);
		}
	}

	if (x+1<colunas && *(*(pixel+y)+x+1)>=0){
		if(absolute( *(*(pixel+y)+x+1)-media ) <= criterio){
			segmentar(linhas, colunas, y, x+1, parametro, m, criterio, pixel);
		}
	}

	if (y+1<linhas && *(*(pixel+y+1)+x)>=0){
		if(absolute( *(*(pixel+y+1)+x)-media ) <= criterio){
			segmentar(linhas, colunas, y+1, x, parametro, m, criterio, pixel);
		}
	}

	if (x-1>=0 && *(*(pixel+y)+x-1)>=0){
		if(absolute( *(*(pixel+y)+x-1)-media ) <= criterio){
			segmentar(linhas, colunas, y, x-1, parametro, m, criterio, pixel);
		}
	}
}



int main(){
	
	char nome_do_arquivo[11];
	fgets(nome_do_arquivo, 11, stdin);

	FILE* arquivo = fopen(nome_do_arquivo, "r");     // aqui eu abro o arquivo e garanto que não há erros
	if(arquivo==NULL){
		printf("ERROR!\n");
		return 1;
	}

	postergar(arquivo);				                      			// eu excluo as informações dispensáveis com 'postergar' 
													               // além disso, eu aloco as informações necessárias nas variáveis devidas
	int linhas, colunas;
	
	fscanf(arquivo, "%d", &colunas);
	fscanf(arquivo, "%d", &linhas);


	fgetc(arquivo);
	postergar(arquivo);


	int** pixel = malloc(linhas*sizeof(int*));
	for(int a=0; a<linhas; a++){                  // nesses 2 for's, eu aloco o espaço na heap e armazeno neles as informações dos pixels da imagem
		*(pixel+a) = malloc(sizeof(int)*colunas);
	}

	
	for(int b=0; b<linhas; b++){		
		for(int c=0; c<colunas; c++){
			fscanf(arquivo, "%d", (*(pixel+b)+c) );
		}	 
	}
		
	
	int k;													// a partir daqui, eu começo o processo de segmentação da imagem
	scanf("%d", &k);										// o usuário entra com a quantidade de entradas
	int x[k], y[k], criterio[k];
	for(int d=0; d<k; d++){
		int parametro[1]={0}, m[1]={0};						
		scanf("%d %d %d", (y+d),(x+d),(criterio+d) );      // e o programa recebe a posição do pixel inicial e o critério
		segmentar( linhas ,colunas, y[d], x[d], parametro, m, criterio[d], pixel); //e manda as informações para a função de segmentação
	}

	for(int w=0; w<linhas; w++){
		for(int q =0; q<colunas; q++){
			printf("%d ", *(*(pixel+w) +q));
		}
		printf("\n");
	}
		

	for(int z=0; z<linhas; z++){
		free(*(	pixel+z));
	}
	free(pixel);
	fclose(arquivo);


}