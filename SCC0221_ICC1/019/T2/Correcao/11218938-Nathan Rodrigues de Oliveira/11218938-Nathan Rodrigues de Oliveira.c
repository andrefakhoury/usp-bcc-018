/*
Aluno: Nathan Rodrigues de Oliveira
NUSP 11218938
Professor: Rudinei Goularte
ICC 1
Maio-2019
*/

//inclusão das bibliotecas padrão: stdio para leitura e impressão;stdlib para o uso da memória Heap; e string.h para manipulação de strings
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Antes de iniciar a leitura do código, ele majoritariamente tem como objetivo armazenar e comparar palavras dentro de uma série de sentenças:
Ele começa recebendo dois inteiros, que representarão o número de sentenças (no contexto do problema, são comentários a respeito de um protudo) e o número de perguntas que vão gerar uma resposta impressa.
Após isso, serão escritas as sentencas que serão armazenadas em um vetor de 3 dimensões como o do exemplo
		1		2		3		4		5
1	p11		p12		p13		p14		p15
2	p12		p22		p23		p24		p25
3	p13		p32		p33		p34		p35			em que cada p[i][j] é uma palavra de até 20 caracteres. Resumidamente, os elementos serão armazenados em uma tabela de palavras.
4	p14		p42		p43		p44		p45
5	p15		p52		p53		p54		p55
*/

// essa função tem como objetivo alocar espaço na memória heap para um vetor de 3 dimensões, sendo o 1 parâmetro a 1 dimensão(linhas) e o 2 parâmetro a 2 dimensão (colunas) (a ultima dimensão é fixa em 20)
char*** alocasent(int nsent,int tamanho);

// essa função tem como objetivo preencher um vetor tridimensional com dados inseridos pelo usuário, recebendo um ponteiro com espaço alocado, o numero de linhas e o número de palavras a ser preenchido (em forma de tabela)
char*** escrevesent(char*** frase, int nsent, int tamanho);

/* a função pegapalavra tem como objetivo criar uma matriz (as linhas são palavras e as colunas são letras) copiando as palavras de um vetor tridimensional já criado em uma posição específica 
 O primeiro parâmetro recebe o número de linhas da matriz a ser criada;
 O segundo parâmetro é o próprio ponteiro que recebe os dados - que é alocado de acordo com o necessário;
 O terceiro parametro é um vetor de 3 dimensões, o qual deve conter as palavras que vão para a matriz;
 O quarto parametro indica qual palavra (em ordem) que deve ser escolhida dentro do vetor previamente já existente;
 */
char** pegapalavra(int perguntas, char** palavra, char*** pergunta, int x);

// essa função devolve uma matriz alocada dinamicamente, em que cada linha está um vetor que contém os indices correspondentes aos produtos iguais aos desejados 
int** alocamatriz(int linhas, int colunas);

// essa função tem como objetivo liberar o espaço alocado para uma matriz, após receber como parâmetro seu ponteiro e numero de linhas
void liberamatriz(char** matriz, int linhas);

// essa função busca liberar o espaço alocado para um vetor de 3 dimensões, recebendo como parâmetro seu ponteiro, numero de linahs e numero de colunas 
void liberacubo(char*** vetor, int linhas, int colunas);

// calcula a porcentagem de x em um total de x+y;
float calcporcentagem(int x, int y);


int** alocamatriz(int linhas, int colunas){
	int i;
	int** matrizdevolvida=NULL;
	
	matrizdevolvida=(int**) malloc(sizeof(int*)*linhas);
							 if(matrizdevolvida==NULL){printf("\nSem Memoria\n"); exit(1);}
							 
	for (i=0;i<colunas;i++){
		matrizdevolvida[i]=(int*) malloc(sizeof(int)*colunas);
								   if(matrizdevolvida[i]==NULL){printf("\nSem Memoria\n"); exit(1);}
	}
	
	return (matrizdevolvida);
}

void liberamatriz(char** matriz, int linhas){
	int i;
	for(i=(linhas-1);i>=0;i--){
		free(matriz[i]);
		matriz[i]=NULL;
	}
	free(matriz);
}


void liberacubo(char*** vetor, int linhas, int colunas){
	int i,j;
	for(i=linhas-1;i>=0;i--){
		for(j=colunas-1;j>=0;j--){
			free(vetor[i][j]);
			vetor[i][j]=NULL;
		}
	}
	for(i=linhas-1;i>=0;i--){
		free(vetor[i]);
		vetor[i]=NULL;
	}
	free(vetor);
}


char*** alocasent(int nsent, int tamanho){
	int i, j;
	char*** frase=NULL;//ponteiro que vai receber a alocação
	
	frase=(char***) malloc(sizeof(char**)*nsent); //a primeira dimensão é um array de tamanho nsent feito por ponteiros para ponteiros (frases)
					if(frase==NULL){printf("\nSem Memoria\n"); exit(1);} 
	
	for(i=0;i<nsent;i++){
		frase[i]=(char**) malloc(sizeof(char*)*tamanho);// a segunda dimensão é um array de tamanho 'tamanho' feito por ponteiros para char (letras)
						  if(frase[i]==NULL){printf("\nSem Memoria\n"); exit(1);} 
		for(j=0;j<tamanho;j++){
		frase[i][j]=(char*) malloc(sizeof(char)*20);// a terceira dimensão aloca 20 espaços para até 20 letras em 1 palavra.
							if(frase[i][j]==NULL){printf("\nSem Memoria\n"); exit(1);} 
		}
	}
	return(frase);
}

//char estranho[] = "Ø";
char*** escrevesent(char*** frase,int nsent, int tamanho){
	int i,j;
	
	for(i=0;i<nsent;i++){//n sent é o tamanho da primeira dimensão (pensando em uma tabela de palavras, seriam as linhas)
		for(j=0;j<tamanho;j++){// tamanho o tamanho da 2 dimensão (pensando na tabela de palavras, seriam as colunas)
			scanf("%s",frase[i][j]);//frase[i][j] é um ponteiro que está apontando para o começo de uma string, então o scanf com %s vai preencher o vetor palavra por palavra
			if(strcmp(frase[i][j],"Ã˜")==0) break;//como nem todas as frases terão o valor máximo de palavras, não é necessário continuar a leitura após o caracter de identificação de fim de frase Ø
		}
	}
	return (frase);
	}


char** pegapalavra(int perguntas, char** palavra, char*** pergunta, int x){
	int i,j;
	
	palavra=(char**)malloc(sizeof(char*)*perguntas);//aloca memoria para cada palavra (igual o numero de linhas de uma tabela de palavras)
					if(palavra==NULL){printf("\nSem Memoria\n"); exit(1);} 
	
	for(i=0;i<perguntas;i++){
		palavra[i]=(char*)malloc(sizeof(char)*20);//aloca memoria para cada letra em cada palavra
						  if(palavra[i]==NULL){printf("\nSem Memoria\n"); exit(1);} 
		for(j=0;j<strlen(pergunta[i][x]);j++){
			palavra[i][j]=pergunta[i][x][j]; //copia para o novo vetor, a palavra selecionada através do 4° parametro.
		}
		
	}
	return (palavra);
}

float calcporcentagem(int x, int y){
	float porcentagem;
	if(y==0&&x!=0) porcentagem=100;
	else porcentagem=(float)(100*x)/(x+y);
	return porcentagem;
	// a conta pode ser resumida em uma regra de 3 de (x+y)--100% x--porcentagem%;
}

int main (void){
	
	int i,j,k,a,b; // i,j,k,a,b, são contadores, que serão inicializados antes de cada inicialização
	int sentencas,perguntas;//sentencas vai guardar o primeiro input dado pelo usuário, já perguntas vai armazenar o segundo - que equivalem aos comentários e as perguntas respectivamente
	int tamanho=100;//reserva um tamanho máximo para comentários de um mesmo produto
	int acm=0,acmn=0;//acm funciona como um contador de palavras ou de sentenças positivas (um para cada caso), já acmn é um acumulador de sentenças negativas;
	float porcentagem=1.0;//porcentagem vai receber a porcetagem de palavras positivas ou negativas caso solicitado pela pergunta
	
	//diversos ponteiros usados no decorrer da execução do programa, todos inicializados apontando para nulo
	int* xprodutos=NULL;
	int** sentdoproduto=NULL;
	char** identifica=NULL;
	char** produto=NULL;
	char** marca=NULL;
	char** identificamarca=NULL;
	char** identificaproduto=NULL;
	char** palavrabuscada=NULL;
	char** negoupos=NULL;
	char*** frase=NULL;
	char*** pergunta=NULL;
	
	scanf("%d %d",&sentencas,&perguntas); // recebe o número de sentencas e perguntas para começar a execução do programa
	
	//aloca espaço e preenche o vetor frase com todas as palavras feitas nos comentarios, identificando o comentario pela 1 dimensão(de tamanho sentencas), o numero de palavras pela 2 dimensão(de tamanho até 23) e cada letra pela 3 dimensão (de tamanho 20)
	frase=alocasent(sentencas,23);
	frase=escrevesent(frase,sentencas,23);
	
	//analogo ao processoa acima, porém tendo como parâmetro o numero de perguntas para a 1 dimensão e 5 palavras para a 2
	pergunta=alocasent(perguntas,5);
	pergunta=escrevesent(pergunta,perguntas,5);

	//a função pegapalavra vai ser usada para criar uma matriz que vai servir para identificar o tipo da pergunta (de contar palavras específicas ou ver a porcetagem);
	identifica=pegapalavra(perguntas,identifica,pergunta,0);
	
	//a funcao pegapalavra também será utilizada para identificar o produto e a marca para cada comentário lido
	produto=pegapalavra(sentencas,produto,frase,0);
	marca=pegapalavra(sentencas,marca,frase,1);
	
	//para realizar uma comparação e escolher qual produto será analisado, a função pegapalavra vai guardar as marcas e produtos das perguntas.
	identificaproduto=pegapalavra(perguntas,identificaproduto,pergunta,3);
	identificamarca=pegapalavra(perguntas,identificamarca,pergunta,4);
	
	//os dois for's a seguir contém o mesmo objetivo inicial, concatenar marca e produto para evitar trabalhar com marca e produto separadamente.
	for(i=0;i<perguntas;i++){
			strcat(identificaproduto[i],identificamarca[i]);
	}
	for(i=0;i<sentencas;i++){
		strcat(produto[i],marca[i]);
	}// ao final, existe uma matriz contendo o produto e marca das perguntas juntos, e outra com o produto e a marca de cada comentário com a primeira dimensão se tratando de cada produto(na ordem de inserção) e a segunda dimensão as letras individuais


	// aloca espaço para uma matriz que, em cada linha vai conter uma pergunta e as colunas serão um vetor com os indices dos comentarios que falam a respeito do produto de tal pergunta (processo descrito abaixo)
	sentdoproduto=alocamatriz(perguntas,tamanho);
	//o vetor xprodutos, em cada um de seus indices, vai armazenar o tamanho de sentdoproduto[i]
	xprodutos=(int*) malloc(sizeof(int)*perguntas);
		
	for(i=0;i<perguntas;i++){//para cada pergunta, o identificador de produto(identificaproduto) vai ferificar todas as sentenças para encontrar quais falam a respeito do mesmo produto
		k=0;
		for(j=0;j<sentencas;j++){
			if(strcmp(identificaproduto[i],produto[j])==0){//se a função strcmp retornar 0, significa que o produto da pergunta i e da sentença j são os mesmos, logo esse j deve ser guardado no vetor palavrabuscada
				sentdoproduto[i][k]=j; // o valor de j é armazenado 
				//k avança para que, se houver mais de um comentário sobre o mesmo produto, ele seja guardado em posições diferentes do vetor
				k++;
			}
		}
		if(k>0) xprodutos[i]=k-1; //na pergunta 'i' o vetor sentdoproduto[i] tem tamanho até a posição xprodutos[i]
	}
	


		//seleciona a palavra que deve ser buscada em caso de pergunta de % (positivo ou negativo)
		negoupos=pegapalavra(perguntas,negoupos,pergunta,1);
		//seleciona a palavra que deve ser contada em caso de pergunta de contagem 
		palavrabuscada=pegapalavra(perguntas,palavrabuscada,pergunta,1);
		
	/*  Nesse momento, (sentdoproduto[i]) contém um ponteiro para um vetor de tamanho xprodutos[i] que contem os indices das perguntas que falam a respeito do problema
		Já (palavrabuscada[i]) possui um vetor de chars com a palavra que a pergunta quer contar e (negoupos[i]) contém se a porcentagem buscada é a de positivos ou a de negativos
		Então, deve-se percorrer o vetore frase[a][b][c] (que contém todos os comentarios) nos indices[a] a indicados por sentproduto[i][xprodutos[i]] - já que esses são todos 
		os indices de frases aos quais a pergunta faz referencia. E [b] representado por todas as palávras do comentário (após o ;)
		
		Então, em caso de pergunta de contagem, deve-se buscar se strcmp(frase[a][b],palavrabuscada[i]==0), se for, acm++, ao final da busca, printf("%d\n",acm);
		*/

		//com todas essas informações a respeito das perguntas, os vetores identificaproduto,produto e pergunta podem ser liberados
	
	liberamatriz(identificaproduto,perguntas);
	liberamatriz(produto,sentencas);
	liberacubo(pergunta,perguntas,5);
	
	//aqui começa a resolução de cada problema, iniciando com um if else indicando qual problema a ser resolvido
	for(i=0;i<perguntas;i++){
		
		if (identifica[i][0]=='p') //'p' indica que a pergunta será a respeito de contar palavras
		{	
	
		for(a=sentdoproduto[i][xprodutos[i]];xprodutos[i]>=0;xprodutos[i]--){
		    a=sentdoproduto[i][xprodutos[i]];
			for(b=3;b<23;b++){
				if(strcmp(frase[a][b],palavrabuscada[i])==0) acm++;//com a busca orientada aos lugares certos, bastar contar quantas vezes a palavra foi encontrada
			}
		}
		//o número de vezes é printado e o acumulador zerado para a próxima pergunta
		printf("%d\n",acm);
		acm=0;
	
		}
		else if (identifica[i][0]=='q') // 'q' indica que a pergunta será a respeito da % de palavras positivas ou negativas
		{
		
		for(a=sentdoproduto[i][xprodutos[i]];xprodutos[i]>=0;xprodutos[i]--){
		    a=sentdoproduto[i][xprodutos[i]];
		    //semelhante ao caso anterior, o vetor vai ser percorrido, mas dessa vez o que será buscado é se o comentário contém uma palavra dentro de uma lista pré-definida
			for(b=3;b<23;b++){
				if(strcmp(frase[a][b],"bom")==0||strcmp(frase[a][b],"boa")==0||strcmp(frase[a][b],"maravilhoso")==0||strcmp(frase[a][b],"maravilhosa")==0||
				strcmp(frase[a][b],"otimo")==0||strcmp(frase[a][b],"otima")==0||strcmp(frase[a][b],"excelente")==0||strcmp(frase[a][b],"adorei")==0||
				strcmp(frase[a][b],"gostei")==0||strcmp(frase[a][b],"amei")==0||strcmp(frase[a][b],"eficiente")==0||strcmp(frase[a][b],"sensacional")==0) 
				{acm++;break;}//se encontrada uma palavra positiva, o comentário é classificado como positivo
				if(strcmp(frase[a][b],"detestei")==0||strcmp(frase[a][b],"odiei")==0||strcmp(frase[a][b],"ruim")==0||strcmp(frase[a][b],"pessimo")==0||
				strcmp(frase[a][b],"terrivel")==0||strcmp(frase[a][b],"raiva")==0||strcmp(frase[a][b],"odio")==0||strcmp(frase[a][b],"pessima")==0||
				strcmp(frase[a][b],"lento")==0||strcmp(frase[a][b],"lenta")==0||strcmp(frase[a][b],"fragil")==0||strcmp(frase[a][b],"desisti")==0)
				{acmn++;break;}//se encontrada uma palavra negativa, o comentário é classificado como negativo
			}
		}
		//com as quantidades de comentários positivos e negativos, basta analisar se o desejado é a % de positivos ou negativos, sendos essa calculada pela função calcporcentagem
		if (negoupos[i][0]=='p'){
		    porcentagem=calcporcentagem(acm,acmn);
		}
		else if (negoupos[i][0]=='n') {
		    porcentagem=calcporcentagem(acmn,acm);}
		printf("%.1f%c\n",porcentagem,37);
		acm=0;
		acmn=0;
		
		} 
	}
	
	//como o vetor frase,negoupos,identifica,xprodutos,sentdoproduto,palavrabuscada são usados até o fim do programa, eles são liberados pouco antes do programa se encerrar;
	
	free(xprodutos);
	liberamatriz(negoupos,perguntas);
	liberamatriz(identifica,perguntas);
	liberamatriz(palavrabuscada,perguntas);
	liberacubo(frase,sentencas,23);
	
	return 0;
}

//fim do algoritmo
