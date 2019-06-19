#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int pertence(int x,int y,int c,double* media,int** matriz){//função responsável por verificar se o pixel pertence à região

	double sub = matriz[x][y] - (*media);
	if((sub<=c)&&(sub>=-c)){//se o pixel pertencer à região, a função retorna 0
		return 0;
	} else {
		return 1;
	}
}

void busca(int x,int y,int c,double* media,int** matriz,int m,int n,int i,double* soma,double* q){//função reponsável pela busca de novos pixeis


	*soma = (*soma) + matriz[x][y];//soma dos pixeis já avaliados
	*q = (*q) + 1;//número de pixeis já avaliados
	*media = (*soma)/ (*q);//cálculo da nova média
	matriz[x][y] = -1;//os pixeis pertencentes à região têm seus valores alterados para -1

	if(((x-1)>=0) && (matriz[x-1][y]!=-1)){//teste do pixel de cima
		if(pertence(x-1,y,c,media,matriz)==0){//se a função retornar 0, o pixel pertence à região e uma nova busca é iniciada a partir dele
			busca(x-1,y,c,media,matriz,m,n,i,soma,q);
		}
	}
	if(((y+1)<m) && (matriz[x][y+1]!=-1)){//teste do pixel da direita
		if(pertence(x,y+1,c,media,matriz)==0){
			busca(x,y+1,c,media,matriz,m,n,i,soma,q);
		} 
	}
	if(((x+1)<n) && (matriz[x+1][y]!=-1)){//teste do pixel de baixo
		if(pertence(x+1,y,c,media,matriz)==0){
			busca(x+1,y,c,media,matriz,m,n,i,soma,q);
		}
	}
	if(((y-1)>=0) && (matriz[x][y-1]!=-1)){//teste do pixel da esquerda
		if(pertence(x,y-1,c,media,matriz)==0){
			busca(x,y-1,c,media,matriz,m,n,i,soma,q);
		}
	}
}

int main(void) {

	int k,i,j,m,n,l=0,quant=0;//k:número de buscas,m:altura,n:largura
	double soma=0,q=0;
	double media=0;
	char nome[20];//armazena o nome do arquivo

	scanf("%[^\n\r]", nome );//lê o nome do arquivo
	FILE* arquivo = fopen(nome,"r");//abre o arquivo requisitado

	scanf(" %d", &k);//leitura do número de buscas

	int* x = malloc(k*(sizeof(int)));//são alocados "k" espaços para as coordenadas iniciais e critérios de cada busca 
	int* y = malloc(k*(sizeof(int)));
	int* c = malloc(k*(sizeof(int)));

	for(i=0;i<k;i++){
		scanf(" %d %d %d", &x[i],&y[i],&c[i]);//leitura das coordenadas iniciais e do critério de cada busca
	}

	fscanf(arquivo," %*s");//string ignorada

	fscanf(arquivo," %d",&n);//leitura da largura
	fscanf(arquivo," %d",&m);//leitura da altura

	fscanf(arquivo," %*d");//inteiro ignorado

	int** matriz = malloc(m*(sizeof(int*)));//é alocado o espaço necessário para o armazenamento da imagem
	for(i=0;i<m;i++){
		matriz[i] = malloc((n*(sizeof(int))));
	}

	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			fscanf(arquivo," %d", &matriz[i][j]);//leitura dos inteiros pertencentes à matriz da imagem
		}
	}

	int* bordax = malloc(m*n*(sizeof(int)));//é alocado espaço para o armazenamento das coordenadas do pixeis pertencentes à borda
	int* borday = malloc(m*n*(sizeof(int)));

	for(i=0;i<k;i++){//realização das "k" buscas
		if(matriz[x[i]][y[i]] !=-1){
			busca(x[i],y[i],c[i],&media,matriz,m,n,i,&soma,&q);
		}

		media = 0;
		q=0;
		soma = 0;
	}

	for(i=0;i<m;i++){//confere se os pixeis pertencem às bordas
		for(j=0;j<n;j++){
			if(matriz[i][j]==-1){
				if(((i-1)>=0)&&(matriz[i-1][j]!=-1)){//confere se o vizinho de cima pertence à região
					quant++;
					bordax[l]= i - 1;
					borday[l] = j;
					l++;
				}
				if(((j+1)<n)&&(matriz[i][j+1]!=-1)){//confere se o vizinho da direita pertence à região
					quant++;
					bordax[l]= i;
					borday[l] = j+1;
					l++;
				}

				if(((i+1)<m)&&(matriz[i+1][j]!=-1)){//confere se o vizinho de baixo pertence à região
					quant++;
					bordax[l]= i + 1;
					borday[l] = j;
					l++;
				}
				if(((j-1)>=0)&&(matriz[i][j-1]!=-1)){//confere se o zvizinho da esuerda pertence à região
					quant++;
					bordax[l]= i;
					borday[l] = j - 1;
					l++;
				}

				if(quant>=1){//se quant>=1,sabemos que o pixel pertence a borda, já que pelo menos um de seus vizinhos não pertence à região segmentada 
					bordax[l] = i;
					borday[l] = j;
					l++;
				}
				quant = 0;
			}
		}
	}

	q=0;

	for(i=0;i<l;i++){//os pixeis que aparecem mais de uma vez são reduzidos a uma única ocorrência
		for(j=0;j<i;j++){
			if((bordax[i] == bordax[j])&&(borday[i] == borday[j])){
				q++;
			}
		}

		if(q == 0){//se q = 0, esta é a primeira ocorrência das coordenas e esta é mantida, senão, é descartada

			matriz[bordax[i]][borday[i]] = -2;//os pixeis pertencentes às bordas têm seus valores alterados para -2(o que facilita a impressão na oredem requisitada)
		}

		q=0;
	}

	for(i=0;i<m;i++){//as coordenadas dos pixeis das bordas são exibidas
		for(j=0;j<n;j++){
			if(matriz[i][j] == -2){
				printf("(%d, %d)\n",i,j);
			}
		}
	}

	free(x);
	free(y);
	free(c);
	free(matriz);
	free(bordax);
	free(borday);
	fclose(arquivo);

	return 0;
}