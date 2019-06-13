#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//infelizmente, eu não consegui adaptar o código para receber o modelo de texto exato do run codes (como o  Ø por exemplo), então ele não deve acertar nenhum caso de teste pelo site


#define maxchar 20*20


int evalue(char* sentenca, char* palavra){      // função para avaliar se o comentário é positivo ou negativo, infelizmente não consegui fazê=lá funcionar corretamente devido a algum erro de lógica que não consigo encontrar
												// portanto, na maioria dos casos ela deve estar errada
	int space=0, tam=0;							//no geral, eu fiz uma espécie de split do python para o comentário e comparei cada palavra com as sugeridas no trabalho e dependendo do tipo da palavra ele retorna 1, para as positivas, e -1 para as negativas
	char* token;							

	tam =strlen(sentenca);
	for(int i=0; i<tam; i++){
		if(*(sentenca+i)==' ') space++;
	}

	switch(*palavra){
		case 'p':

		token= strtok(sentenca, " ");
		if(strcmp(token, "bom")==0 || strcmp(token, "maravilhoso")==0 || strcmp(token, "otimo")==0 || strcmp(token, "sensacional")==0 ||  strcmp(token, "execelente")==0 ||  strcmp(token, "adorei")==0 ||  strcmp(token, "gostei")==0 ||  strcmp(token, "amei")==0 ||  strcmp(token, "eficiete")==0 ||  strcmp(token, "boa")==0 ||  strcmp(token, "maravilhosa")==0 ||  strcmp(token, "otima")==0)return +1;
		for(int j=0;j<space; j++){
			token= strtok(NULL, " ");
			if(strcmp(token, "bom")==0 || strcmp(token, "maravilhoso")==0 || strcmp(token, "otimo")==0 || strcmp(token, "sensacional")==0 ||  strcmp(token, "execelente")==0 ||  strcmp(token, "adorei")==0 ||  strcmp(token, "gostei")==0 ||  strcmp(token, "amei")==0 ||  strcmp(token, "eficiete")==0 ||  strcmp(token, "boa")==0 ||  strcmp(token, "maravilhosa")==0 ||  strcmp(token, "otima")==0)return +1;
		}
		return- 1;

			break;

		case 'n':
		token= strtok(sentenca, " ");
		if(strcmp(token, "detestei")==0 || strcmp(token, "odiei")==0 || strcmp(token, "ruim")==0 || strcmp(token, "pessimo")==0 ||  strcmp(token, "terrivel")==0 ||  strcmp(token, "raiva")==0 ||  strcmp(token, "odio")==0 ||  strcmp(token, "pessima")==0 ||  strcmp(token, "lento")==0 ||  strcmp(token, "lenta")==0 ||  strcmp(token, "fragil")==0 ||  strcmp(token, "desisti")==0)return -1;
		for(int j=0;j<space; j++){
			token= strtok(NULL, " ");
			if(strcmp(token, "detestei")==0 || strcmp(token, "odiei")==0 || strcmp(token, "ruim")==0 || strcmp(token, "pessimo")==0 ||  strcmp(token, "terrivel")==0 ||  strcmp(token, "raiva")==0 ||  strcmp(token, "odio")==0 ||  strcmp(token, "pessima")==0 ||  strcmp(token, "lento")==0 ||  strcmp(token, "lenta")==0 ||  strcmp(token, "fragil")==0 ||  strcmp(token, "desisti")==0)return -1;
		}
		return 1;
	}
    return 0;

}

int count(char* sentenca, char* palavra){  // nessa função eu fiz um contador de palavras, que funciona muito similarmente à função acima
	int qtd=0, space=0, tam=0;				// ele também faz o split e compara cada palavra da sentença com a palavra que a pergunta requer
	
	tam=strlen(sentenca);                   // felizmente, essa função parece estar funcionando corretamente
	for(int i=0; i<tam; i++){
		if(*(sentenca+i)==' ') space++;
	}


	char* token= strtok(sentenca, " ");
	if(strcmp(token, palavra)==0)qtd++;
	for(int j=0;j<space; j++){
		int length= strlen(palavra);
		token= strtok(NULL, " ");
		if(strncmp(token, palavra, length)==0)qtd++;
	}
	
	return qtd;
}



struct produto{                   //nessa struct eu trato de duas coisas, do nome dos produtos e dos comentarios que o acompanha                 
	char nome[30];
	char sentenca[maxchar];

};


int main(){
	
	struct produto itens[100];

	int c, q;
	int qtd=0, qtdn=0, total=0, opniao;                        //nessa região declaro algumas variaveis para auxiliar na execução do programa
	scanf("%d %d", &c, &q);
	bool define;
	
	char comments[c][maxchar], questions[q][maxchar];         
	getchar();

	for(int i=0; i<c; i++){  // começo tratando dos nome dos produtos/ comentarios
			
			fgets (*(comments+i), maxchar, stdin);       //os escaneio com o fgets
			strtok(*(comments+i), ";");					// separo nome de comentario com o strtok							
			strcpy(itens[i].nome, *(comments+i));		// e vou alocando cada um deles nas regiões da memoria do meu intesesse			
			int length = strlen(itens[i].nome);				
			strcpy(itens[i].sentenca, *(comments+i)+length+2);
	}	

	for(int j=0; j<q; j++){         // já a partir daqui trato as questões que preciso responder
		
		fgets (*(questions+j), maxchar, stdin);			// a principio, funciona identicamente ao local onde trato os comentarios
		char palavras[5][20];							// com a diferença de que, aqui, eu faço um split completo de cada palavra da sentença
		
		strtok(*(questions+j), " ");				
		strcpy(*palavras, *(questions+j));						

		for(int k=1; k<5; k++){
			char* aux;
			aux= strtok(NULL, " ");
			strcpy(*(palavras+k), aux);
		}

		strcat(*(palavras+3)," ");
		strcat(*(palavras+3), *(palavras+4));			// e para facilitar processos futuros eu concateno os ultimos 2 nomes (que sempre sao os nomes dos produtos)
														// para poder trabalhaar mais facilmente comm eles


		qtd=0, qtdn=0, total=0;
		for(int w=0; w<c; w++){
			if(strncmp(*(palavras+3),itens[w].nome, strlen(itens[w].nome))<=2 && strncmp(*(palavras+3),itens[w].nome, strlen(itens[w].nome))>=-2){     //aqui é onde começo a fazer a apuração da informação requerida nas questões
				switch(**palavras){

					case 'p':                                               // caso a primeira palavra da pergunta comece com p de "palavra", ela conta a palavra pedida e retorna sua frequencia no comentario
						qtd+=count(itens[w].sentenca,*(palavras+1));
						define=true;
						
						break;

					case 'q':												// caso a a primeira palavra comece com q de "quantos", ela deveria analisar se os comentarios são positivos ou negativos 
						define=false;
						opniao=evalue(itens[w].sentenca,*(palavras+1));
						if(opniao==1) qtd++;
						if(opniao==-1) qtdn++;
						total++;

				}

			}
				
		}
	}	
		if(define) printf("%d\n", qtd);
		else {
			if(opniao==1){ 
				printf("%.2f  \n", (float)(qtd/total)*100);     //e aqui eu imprimo a resposta, dependendo do caso que foi determinado anteriormente
			}else{
				printf("%.2f  \n", (float)(qtdn/total)*100);
			}
		}	

			

	return 0;
		
}

//meu trabalho não acerta nenhum caso no run codes tampouco funciona razoavelmente em muitas situações, porém agradeceria caso o senhor corretor/professor levasse em conta os mínimos desse trabalho
