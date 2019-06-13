/*Trabalho 2 de ICC I (SCC0221) - Contando Palavras*/
/*Nome: Diogo Castanho Emídio - 11297274*/
//
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//
/*	Struct do tipo produto que contém cada palavra da sentença ou pergunta em questão, com variáveis	*/
/*		específicas para o aparelho e para a marca do produto para facilitar a consulta	*/
typedef struct{
	char palavra[24][20];
	char* aparelho;
	char* marca;
}produto;
//
/*	Função, do tipo ponteiro da struct criada, que escreve e registra as sentenças	*/
produto* cadastro(int n_sentencas){
/*	Declaração das principais variáveis da função	*/
	char frase_cad[200];
	char* token;
	produto* sentenca = malloc(n_sentencas*sizeof(produto));
/*	Laço de repetição para escrita de cada sentença e armazenamento individual de cada palavra da mesma	*/
	for(int i=0; i<n_sentencas; i++){
		int j=1;
		fgets(frase_cad, 200, stdin);
/*	Medição do tamanho da sentença e substituição dos caracteres de enter por um de final de string	*/
		int size=strlen(frase_cad);
		frase_cad[size-2]='\0';
/*	Quebra da sentença depois da primeira palavra e armazenamento da mesma na variável correspondente	*/
/*		dentro da struct de registro de sentenças	*/
		token=strtok(frase_cad, " ");
		strcpy(sentenca[i].palavra[0], token);
/*	Laço de repetição para armazenamento individual de cada palavra, a partir da segunda	*/
		do{
/*	Quebra da sentença depois de cada palavra	*/
			token=strtok('\0', " ");
/*	Condição que determina se há alguma palavra para ser armazenada	*/
			if(token){
				strcpy(sentenca[i].palavra[j], token);
				j++;
			}
		}while(token);
/*	Registro do aparelho na variável correspondente e específica dentro da struct de sentenças	*/
		sentenca[i].aparelho = sentenca[i].palavra[0];
/*	Registro da marca na variável correspondente e específica dentro da struct de sentenças	*/
		sentenca[i].marca = sentenca[i].palavra[1];
	}
	return sentenca;
}
//
/*	Função, do tipo ponteiro da struct criada, que escreve e registra as perguntas	*/
produto* questionario(int n_perguntas){
/*	Declaração das principais variáveis da função	*/
	char frase_quest[100];
	char* token;
	produto* pergunta = malloc(n_perguntas*sizeof(produto));
/*	Laço de repetição para escrita de cada pergunta e armazenamento individual de cada palavra da mesma	*/
	for(int i=0; i<n_perguntas; i++){
		int j=1;
		fgets(frase_quest, 100, stdin);
/*	Medição do tamanho da pergunta	*/
		int size=strlen(frase_quest);
/*	Condição que determina quando há substituição dos caracteres de enter por um de final de string	*/
		if(i<n_perguntas-1)		frase_quest[size-2]='\0';
		else					frase_quest[size]='\0';
/*	Quebra da pergunta depois da primeira palavra e armazenamento da mesma na variável correspondente	*/
/*		dentro da struct de registro de perguntas	*/
		token=strtok(frase_quest, " ");
		strcpy(pergunta[i].palavra[0], token);
/*	Laço de repetição para armazenamento individual de cada palavra, a partir da segunda	*/
		do{
/*	Quebra da pergunta depois de cada palavra	*/
			token=strtok('\0', " ");
/*	Condição que determina se há alguma palavra para ser armazenada	*/
			if(token){
				strcpy(pergunta[i].palavra[j], token);
				j++;
			}
		}while(token);
/*	Registro do aparelho na variável correspondente e específica dentro da struct de perguntas	*/
		pergunta[i].aparelho = pergunta[i].palavra[3];
/*	Registro da marca na variável correspondente e específica dentro da struct de perguntas	*/
		pergunta[i].marca = pergunta[i].palavra[4];
	}
	return pergunta;
}
//
/*	Função que verifica se as palavras possuem polaridade, se essa deve ser invertida, caso exista, e	*/
/*		contabiliza a frequência da polaridade pedida de acordo com o resultado	*/
int inverte(produto* sentenca, char sinonimos[12][12], char antonimos[12][12], int cont_certo, int flag, int h){
	int inversor=0;
/*	Declaração da matriz contendo advérbios de negação (palavras inversoras)	*/
	char palavras_inv[3][7]={"nao", "jamais", "nunca"};
/*	Laço de repetição para comparação da polaridade pedida, na pergunta, com a da palavra que está na	*/
/*		g-ésima posição após ";", na sentença, contabilizando-a se forem a mesma	*/
	for(int g=0; flag==0; g++){
/*	Laço de repetição para comparação da palavra com cada sinônimo e antônimo das duas polaridades	*/
		for(int f=0; flag==0 && f<12; f++){
			int comp_sinonimos = strcmp(sentenca[h].palavra[g+3], sinonimos[f]);
			int comp_antonimos = strcmp(sentenca[h].palavra[g+3], antonimos[f]);
/*	Condição que determina se a palavra é um sinônimo ou um antônimo da polaridade pedida ou nenhum deles	*/
			if(comp_sinonimos==0 || comp_antonimos==0){
/*	Laços de repetição para comparação das palavras em até 3 posições antes, na sentença, com cada um dos	*/
/*		advérbios de negação	*/
				for(int j=1; inversor==0 && j<=3; j++){
					for(int e=0; inversor==0 && e<3; e++){
						if(strcmp(sentenca[h].palavra[g+3-j], palavras_inv[e]) == 0)		inversor=1;
					}
				}
/*	Condição que contabiliza a presença da polaridade pedida	*/
				if((comp_sinonimos==0 && inversor==0) || (comp_antonimos==0 && inversor==1)){
					cont_certo++;
					flag=1;
				}
/*	Condição que sai do laço de repetição quando a palavra na g-ésima posição após ";" for o identificador	*/
/*		de fim de sentença	*/
			}else if(strcmp(sentenca[h].palavra[g+3], "Ø") == 0)							flag=1;
		}
	}
	return cont_certo;
}
//
/*	Função que compara o que é pedido em cada pergunta com o conteúdo de cada sentença e imprime de acordo	*/
/*		com o pedido da respectiva pergunta 	*/
void compara_imprime(int n_sentencas, int n_perguntas, produto* sentenca, produto* pergunta){
/*	Declaração das matrizes contendo palavras de satisfação (positivas) ou de insatisfação (negativas)	*/
	char palavras_pos[12][12]={"bom", "maravilhoso", "otimo", "sensacional", "excelente", "adorei", "gostei", "amei", "eficiente", "boa", "maravilhosa", "otima"};
	char palavras_neg[12][12]={"detestei", "odiei", "ruim", "pessimo", "terrivel", "raiva", "odio", "pessima", "lento", "lenta", "fragil", "desisti"};
/*	Laço de repetição para comparação de palavras-chave de cada pergunta com cada palavra de cada sentença	*/
	for(int i=0; i<n_perguntas; i++){
		int cont_igual=0, cont_certo=0;
/*	Laço de repetição para comparação da i-ésima pergunta com cada sentença e para impressão do que foi	*/
/*		pedido na respectiva pergunta	*/
		for(int h=0; h<n_sentencas; h++){
/*	Condição que determina se as palavras referentes ao aparelho e à marca da i-ésima pergunta são as	*/
/*		mesmas das da h-ésima sentença	*/
			if(strcmp(pergunta[i].aparelho, sentenca[h].aparelho) == 0 && strcmp(pergunta[i].marca, sentenca[h].marca) == 0){
				int flag=0;
				cont_igual++;
/*	Condição que determina se será contabilizado o número de aparições de determinada palavra nas sentenças	*/
				if(strcmp(pergunta[i].palavra[0], "palavra") == 0){
/*	Laço de repetição para comparação da palavra pedida, na pergunta, com a que está na g-ésima posição	*/
/*		após ";", na sentença, contabilizando-a se forem a mesma	*/
					for(int g=0; flag==0; g++){
						if(strcmp(pergunta[i].palavra[1], sentenca[h].palavra[g+3]) == 0)	cont_certo++;
/*	Condição que sai do laço de repetição quando a palavra na g-ésima posição após ";" for o identificador	*/
/*		de fim de sentença	*/
						else if(strcmp(sentenca[h].palavra[g+3], "Ø") == 0)					flag=1;
					}
/*	Condição que determina se será contabilizada a frequência de aparição de determinada polaridade de	*/
/*		palavras nas sentenças	*/
				}else if(strcmp(pergunta[i].palavra[0], "quantos") == 0){
/*	Condição que determina se a polaridade é positiva	*/
					if(strcmp(pergunta[i].palavra[1], "positivos") == 0){
						cont_certo=inverte(sentenca, palavras_pos, palavras_neg, cont_certo, flag, h);
/*	Condição que determina se a polaridade é negativa	*/
					}else if(strcmp(pergunta[i].palavra[1], "negativos") == 0){
						cont_certo=inverte(sentenca, palavras_neg, palavras_pos, cont_certo, flag, h);
					}
				}
			}
/*	Condição que determina se o valor a ser impresso é o número de aparições de determinada palavra ou a	*/
/*		frequência de aparição de determinada polaridade de palavras	*/
			if(h==n_sentencas-1){
				if(strcmp(pergunta[i].palavra[0], "palavra") == 0){
					printf("%d\n", cont_certo);
				}else if(strcmp(pergunta[i].palavra[0], "quantos") == 0){
					printf("%.1f%%\n", ((float)cont_certo/(float)cont_igual)*100);
				}
			}
		}
	}
}
//
/*	Função principal	*/
int main(void){
/*	Declaração das principais variáveis, escrita do número de sentenças e do de perguntas e limpeza do	*/
/*		buffer do teclado	*/
	int n_sentencas, n_perguntas;
	produto* sentenca=NULL;
	produto* pergunta=NULL;
	scanf("%d %d", &n_sentencas, &n_perguntas);
	getchar();
	getchar();
/*	Chamada da função que escreve e registra as sentenças e atribuição do retorno da mesma a uma variável	*/
/*		do tipo ponteiro da struct criada	*/
	sentenca=cadastro(n_sentencas);
/*	Chamada da função que escreve e registra as perguntas e atribuição do retorno da mesma a uma variável	*/
/*		do tipo ponteiro da struct criada	*/
	pergunta=questionario(n_perguntas);
/*	Chamada da função que compara o que é pedido em cada pergunta com o conteúdo de cada sentença e imprime	*/
/*		de acordo com o pedido da respectiva pergunta 	*/
	compara_imprime(n_sentencas, n_perguntas, sentenca, pergunta);
/*	Liberação das memórias alocadas dinamicamente	*/
	free(sentenca);
	free(pergunta);
	return 0;
}