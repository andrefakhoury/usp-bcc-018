/*
Aluno: Nathan Rodrigues de Oliveira
NUSP 11218938
Professor: Rudinei Goularte
ICC 1
Maio-2019
*/

//inclus�o das bibliotecas padr�o: stdio para leitura e impress�o;stdlib para o uso da mem�ria Heap; e string.h para manipula��o de strings
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Antes de iniciar a leitura do c�digo, ele majoritariamente tem como objetivo armazenar e comparar palavras dentro de uma s�rie de senten�as:
Ele come�a recebendo dois inteiros, que representar�o o n�mero de senten�as (no contexto do problema, s�o coment�rios a respeito de um protudo) e o n�mero de perguntas que v�o gerar uma resposta impressa.
Ap�s isso, ser�o escritas as sentencas que ser�o armazenadas em um vetor de 3 dimens�es como o do exemplo
		1		2		3		4		5
1	p11		p12		p13		p14		p15
2	p12		p22		p23		p24		p25
3	p13		p32		p33		p34		p35			em que cada p[i][j] � uma palavra de at� 20 caracteres. Resumidamente, os elementos ser�o armazenados em uma tabela de palavras.
4	p14		p42		p43		p44		p45
5	p15		p52		p53		p54		p55
*/

// essa fun��o tem como objetivo alocar espa�o na mem�ria heap para um vetor de 3 dimens�es, sendo o 1 par�metro a 1 dimens�o(linhas) e o 2 par�metro a 2 dimens�o (colunas) (a ultima dimens�o � fixa em 20)
char*** alocasent(int nsent,int tamanho);

// essa fun��o tem como objetivo preencher um vetor tridimensional com dados inseridos pelo usu�rio, recebendo um ponteiro com espa�o alocado, o numero de linhas e o n�mero de palavras a ser preenchido (em forma de tabela)
char*** escrevesent(char*** frase, int nsent, int tamanho);

/* a fun��o pegapalavra tem como objetivo criar uma matriz (as linhas s�o palavras e as colunas s�o letras) copiando as palavras de um vetor tridimensional j� criado em uma posi��o espec�fica 
 O primeiro par�metro recebe o n�mero de linhas da matriz a ser criada;
 O segundo par�metro � o pr�prio ponteiro que recebe os dados - que � alocado de acordo com o necess�rio;
 O terceiro parametro � um vetor de 3 dimens�es, o qual deve conter as palavras que v�o para a matriz;
 O quarto parametro indica qual palavra (em ordem) que deve ser escolhida dentro do vetor previamente j� existente;
 */
char** pegapalavra(int perguntas, char** palavra, char*** pergunta, int x);

// essa fun��o devolve uma matriz alocada dinamicamente, em que cada linha est� um vetor que cont�m os indices correspondentes aos produtos iguais aos desejados 
int** alocamatriz(int linhas, int colunas);

// essa fun��o tem como objetivo liberar o espa�o alocado para uma matriz, ap�s receber como par�metro seu ponteiro e numero de linhas
void liberamatriz(char** matriz, int linhas);

// essa fun��o busca liberar o espa�o alocado para um vetor de 3 dimens�es, recebendo como par�metro seu ponteiro, numero de linahs e numero de colunas 
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
	char*** frase=NULL;//ponteiro que vai receber a aloca��o
	
	frase=(char***) malloc(sizeof(char**)*nsent); //a primeira dimens�o � um array de tamanho nsent feito por ponteiros para ponteiros (frases)
					if(frase==NULL){printf("\nSem Memoria\n"); exit(1);} 
	
	for(i=0;i<nsent;i++){
		frase[i]=(char**) malloc(sizeof(char*)*tamanho);// a segunda dimens�o � um array de tamanho 'tamanho' feito por ponteiros para char (letras)
						  if(frase[i]==NULL){printf("\nSem Memoria\n"); exit(1);} 
		for(j=0;j<tamanho;j++){
		frase[i][j]=(char*) malloc(sizeof(char)*20);// a terceira dimens�o aloca 20 espa�os para at� 20 letras em 1 palavra.
							if(frase[i][j]==NULL){printf("\nSem Memoria\n"); exit(1);} 
		}
	}
	return(frase);
}

//char estranho[] = "�";
char*** escrevesent(char*** frase,int nsent, int tamanho){
	int i,j;
	
	for(i=0;i<nsent;i++){//n sent � o tamanho da primeira dimens�o (pensando em uma tabela de palavras, seriam as linhas)
		for(j=0;j<tamanho;j++){// tamanho o tamanho da 2 dimens�o (pensando na tabela de palavras, seriam as colunas)
			scanf("%s",frase[i][j]);//frase[i][j] � um ponteiro que est� apontando para o come�o de uma string, ent�o o scanf com %s vai preencher o vetor palavra por palavra
			if(strcmp(frase[i][j],"Ø")==0) break;//como nem todas as frases ter�o o valor m�ximo de palavras, n�o � necess�rio continuar a leitura ap�s o caracter de identifica��o de fim de frase �
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
			palavra[i][j]=pergunta[i][x][j]; //copia para o novo vetor, a palavra selecionada atrav�s do 4� parametro.
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
	
	int i,j,k,a,b; // i,j,k,a,b, s�o contadores, que ser�o inicializados antes de cada inicializa��o
	int sentencas,perguntas;//sentencas vai guardar o primeiro input dado pelo usu�rio, j� perguntas vai armazenar o segundo - que equivalem aos coment�rios e as perguntas respectivamente
	int tamanho=100;//reserva um tamanho m�ximo para coment�rios de um mesmo produto
	int acm=0,acmn=0;//acm funciona como um contador de palavras ou de senten�as positivas (um para cada caso), j� acmn � um acumulador de senten�as negativas;
	float porcentagem=1.0;//porcentagem vai receber a porcetagem de palavras positivas ou negativas caso solicitado pela pergunta
	
	//diversos ponteiros usados no decorrer da execu��o do programa, todos inicializados apontando para nulo
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
	
	scanf("%d %d",&sentencas,&perguntas); // recebe o n�mero de sentencas e perguntas para come�ar a execu��o do programa
	
	//aloca espa�o e preenche o vetor frase com todas as palavras feitas nos comentarios, identificando o comentario pela 1 dimens�o(de tamanho sentencas), o numero de palavras pela 2 dimens�o(de tamanho at� 23) e cada letra pela 3 dimens�o (de tamanho 20)
	frase=alocasent(sentencas,23);
	frase=escrevesent(frase,sentencas,23);
	
	//analogo ao processoa acima, por�m tendo como par�metro o numero de perguntas para a 1 dimens�o e 5 palavras para a 2
	pergunta=alocasent(perguntas,5);
	pergunta=escrevesent(pergunta,perguntas,5);

	//a fun��o pegapalavra vai ser usada para criar uma matriz que vai servir para identificar o tipo da pergunta (de contar palavras espec�ficas ou ver a porcetagem);
	identifica=pegapalavra(perguntas,identifica,pergunta,0);
	
	//a funcao pegapalavra tamb�m ser� utilizada para identificar o produto e a marca para cada coment�rio lido
	produto=pegapalavra(sentencas,produto,frase,0);
	marca=pegapalavra(sentencas,marca,frase,1);
	
	//para realizar uma compara��o e escolher qual produto ser� analisado, a fun��o pegapalavra vai guardar as marcas e produtos das perguntas.
	identificaproduto=pegapalavra(perguntas,identificaproduto,pergunta,3);
	identificamarca=pegapalavra(perguntas,identificamarca,pergunta,4);
	
	//os dois for's a seguir cont�m o mesmo objetivo inicial, concatenar marca e produto para evitar trabalhar com marca e produto separadamente.
	for(i=0;i<perguntas;i++){
			strcat(identificaproduto[i],identificamarca[i]);
	}
	for(i=0;i<sentencas;i++){
		strcat(produto[i],marca[i]);
	}// ao final, existe uma matriz contendo o produto e marca das perguntas juntos, e outra com o produto e a marca de cada coment�rio com a primeira dimens�o se tratando de cada produto(na ordem de inser��o) e a segunda dimens�o as letras individuais


	// aloca espa�o para uma matriz que, em cada linha vai conter uma pergunta e as colunas ser�o um vetor com os indices dos comentarios que falam a respeito do produto de tal pergunta (processo descrito abaixo)
	sentdoproduto=alocamatriz(perguntas,tamanho);
	//o vetor xprodutos, em cada um de seus indices, vai armazenar o tamanho de sentdoproduto[i]
	xprodutos=(int*) malloc(sizeof(int)*perguntas);
		
	for(i=0;i<perguntas;i++){//para cada pergunta, o identificador de produto(identificaproduto) vai ferificar todas as senten�as para encontrar quais falam a respeito do mesmo produto
		k=0;
		for(j=0;j<sentencas;j++){
			if(strcmp(identificaproduto[i],produto[j])==0){//se a fun��o strcmp retornar 0, significa que o produto da pergunta i e da senten�a j s�o os mesmos, logo esse j deve ser guardado no vetor palavrabuscada
				sentdoproduto[i][k]=j; // o valor de j � armazenado 
				//k avan�a para que, se houver mais de um coment�rio sobre o mesmo produto, ele seja guardado em posi��es diferentes do vetor
				k++;
			}
		}
		if(k>0) xprodutos[i]=k-1; //na pergunta 'i' o vetor sentdoproduto[i] tem tamanho at� a posi��o xprodutos[i]
	}
	


		//seleciona a palavra que deve ser buscada em caso de pergunta de % (positivo ou negativo)
		negoupos=pegapalavra(perguntas,negoupos,pergunta,1);
		//seleciona a palavra que deve ser contada em caso de pergunta de contagem 
		palavrabuscada=pegapalavra(perguntas,palavrabuscada,pergunta,1);
		
	/*  Nesse momento, (sentdoproduto[i]) cont�m um ponteiro para um vetor de tamanho xprodutos[i] que contem os indices das perguntas que falam a respeito do problema
		J� (palavrabuscada[i]) possui um vetor de chars com a palavra que a pergunta quer contar e (negoupos[i]) cont�m se a porcentagem buscada � a de positivos ou a de negativos
		Ent�o, deve-se percorrer o vetore frase[a][b][c] (que cont�m todos os comentarios) nos indices[a] a indicados por sentproduto[i][xprodutos[i]] - j� que esses s�o todos 
		os indices de frases aos quais a pergunta faz referencia. E [b] representado por todas as pal�vras do coment�rio (ap�s o ;)
		
		Ent�o, em caso de pergunta de contagem, deve-se buscar se strcmp(frase[a][b],palavrabuscada[i]==0), se for, acm++, ao final da busca, printf("%d\n",acm);
		*/

		//com todas essas informa��es a respeito das perguntas, os vetores identificaproduto,produto e pergunta podem ser liberados
	
	liberamatriz(identificaproduto,perguntas);
	liberamatriz(produto,sentencas);
	liberacubo(pergunta,perguntas,5);
	
	//aqui come�a a resolu��o de cada problema, iniciando com um if else indicando qual problema a ser resolvido
	for(i=0;i<perguntas;i++){
		
		if (identifica[i][0]=='p') //'p' indica que a pergunta ser� a respeito de contar palavras
		{	
	
		for(a=sentdoproduto[i][xprodutos[i]];xprodutos[i]>=0;xprodutos[i]--){
		    a=sentdoproduto[i][xprodutos[i]];
			for(b=3;b<23;b++){
				if(strcmp(frase[a][b],palavrabuscada[i])==0) acm++;//com a busca orientada aos lugares certos, bastar contar quantas vezes a palavra foi encontrada
			}
		}
		//o n�mero de vezes � printado e o acumulador zerado para a pr�xima pergunta
		printf("%d\n",acm);
		acm=0;
	
		}
		else if (identifica[i][0]=='q') // 'q' indica que a pergunta ser� a respeito da % de palavras positivas ou negativas
		{
		
		for(a=sentdoproduto[i][xprodutos[i]];xprodutos[i]>=0;xprodutos[i]--){
		    a=sentdoproduto[i][xprodutos[i]];
		    //semelhante ao caso anterior, o vetor vai ser percorrido, mas dessa vez o que ser� buscado � se o coment�rio cont�m uma palavra dentro de uma lista pr�-definida
			for(b=3;b<23;b++){
				if(strcmp(frase[a][b],"bom")==0||strcmp(frase[a][b],"boa")==0||strcmp(frase[a][b],"maravilhoso")==0||strcmp(frase[a][b],"maravilhosa")==0||
				strcmp(frase[a][b],"otimo")==0||strcmp(frase[a][b],"otima")==0||strcmp(frase[a][b],"excelente")==0||strcmp(frase[a][b],"adorei")==0||
				strcmp(frase[a][b],"gostei")==0||strcmp(frase[a][b],"amei")==0||strcmp(frase[a][b],"eficiente")==0||strcmp(frase[a][b],"sensacional")==0) 
				{acm++;break;}//se encontrada uma palavra positiva, o coment�rio � classificado como positivo
				if(strcmp(frase[a][b],"detestei")==0||strcmp(frase[a][b],"odiei")==0||strcmp(frase[a][b],"ruim")==0||strcmp(frase[a][b],"pessimo")==0||
				strcmp(frase[a][b],"terrivel")==0||strcmp(frase[a][b],"raiva")==0||strcmp(frase[a][b],"odio")==0||strcmp(frase[a][b],"pessima")==0||
				strcmp(frase[a][b],"lento")==0||strcmp(frase[a][b],"lenta")==0||strcmp(frase[a][b],"fragil")==0||strcmp(frase[a][b],"desisti")==0)
				{acmn++;break;}//se encontrada uma palavra negativa, o coment�rio � classificado como negativo
			}
		}
		//com as quantidades de coment�rios positivos e negativos, basta analisar se o desejado � a % de positivos ou negativos, sendos essa calculada pela fun��o calcporcentagem
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
	
	//como o vetor frase,negoupos,identifica,xprodutos,sentdoproduto,palavrabuscada s�o usados at� o fim do programa, eles s�o liberados pouco antes do programa se encerrar;
	
	free(xprodutos);
	liberamatriz(negoupos,perguntas);
	liberamatriz(identifica,perguntas);
	liberamatriz(palavrabuscada,perguntas);
	liberacubo(frase,sentencas,23);
	
	return 0;
}

//fim do algoritmo
