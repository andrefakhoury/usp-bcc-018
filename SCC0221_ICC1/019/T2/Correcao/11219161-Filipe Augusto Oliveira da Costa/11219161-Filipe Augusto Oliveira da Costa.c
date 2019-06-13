/*
			Aluno: Filipe Augusto Oliveira da Costa
			Professor: Rudinei Goulart
			N Usp: 11219161
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char *lernome(void){		// esta funcao le as 2 primeiras palavras digitadas no comentario + o (;) em 3 strings diferentes

	char *s1, *s2, *s3;
	s1 = (char *) calloc(40, sizeof(char));
	s2 = (char *) calloc(20, sizeof(char));
	s3 = (char *) calloc(2, sizeof(char));
	if(s1 == NULL || s2 == NULL || s3 == NULL)
		return NULL;
	scanf("%s", s1);
	scanf("%s", s2);
	scanf("%s", s3);
	strcat(s1, s2);		//concatena o nome do produto e a marca em uma string só
	free(s2);
	free(s3);
	return s1;		//retorna a string concatenada e libera as outras duas


}

char *leraval(void){		//esta funcao le cada uma das outras palavras do comentario (para cada palavra lida é uma execucao dessa funcao)

	char *str;
	str = (char *) calloc(20, sizeof(char));
	if(str == NULL)
		return NULL;
	scanf("%s", str);
	return str;		//retorna cada palavra como string indivual

}

char *lerexp(void){		//essa funcao le as tres primeiras palavras da pergunta, descarta a primeira e a terceira, retorna a segunda

	char *d1, *exp, *d2;
	d1 = (char *) calloc(20, sizeof(char));
	exp = (char *) calloc(20, sizeof(char));
	d2 = (char *) calloc(20, sizeof(char));
	if(d1 == NULL || exp == NULL || d2 == NULL)
		return NULL;
	scanf("%s", d1);
	scanf("%s", exp);
	scanf("%s", d2);
	free(d1);
	free(d2);
	return exp;

}

char *lerprod(void){		//essa funcao le as duas ultimas palavras da pergunta e concatena suas strings

	char *s1, *s2;
	s1 = (char *) calloc(40, sizeof(char));
	s2 = (char *) calloc(20, sizeof(char));
	if(s1 == NULL || s2 == NULL)
		return NULL;
	scanf("%s", s1);
	scanf("%s", s2);
	strcat(s1,s2);
	free(s2);
	return s1;		//o retorno é o nome do produto do qual esta sendo feita a pergunta, isso sera usado para encontrar os comentarios relacionados a este produto

}

int inversor(char *aval, int j, int inv){		//esta funcao le as palavras inversoras de polaridade e retorna o indice da string onde tais palavras estao escritas somado de 3, quando uma palavra que condiona a frase como positiva ou negativa for encontrada o programa vai testar se o indice dela é menor ou igual ao retorno dessa funçao

	if(strstr(aval, "nao") != NULL){
		return (j+3);
	}
	if(strstr(aval, "nunca") != NULL){
		return (j+3);
	}
	if(strstr(aval, "jamais") != NULL){
		return (j+3);
	}
	return inv;

}

int cbom (int j, int inv){	//esta funcao e a proxima definem a polaridade do comentario como positiva ou negativa, se o indice da string que esta sendo analisado for menor que a variavel inv (relaciona ao inversor da funcao acima) entao a polaridade do comentario é invertida

	if(j<=inv)
		return 2;
	else
		return 1;

}

int cruim (int j, int inv){		//mesma coisa que a funcao de cima

	if(j<=inv)
		return 1;
	else
		return 2;

}

int comparacao(char *aval, int inv, int j){	//comparando as palavras do comentario em busca de polarizadores, adaptacao do bag of words

	int estado;	
	if (strstr(aval,"bom") != NULL){
		estado = cbom(j, inv);	
		return estado;
	}
	if (strstr(aval,"maravilhoso") != NULL){
		estado = cbom(j, inv);	
		return estado;
	}
	if (strstr(aval,"otimo") != NULL){
		estado = cbom(j, inv);	
		return estado;
	}
	if (strstr(aval,"sensacional") != NULL){
		estado = cbom(j, inv);	
		return estado;
	}
	if (strstr(aval,"excelente") != NULL){
		estado = cbom(j, inv);	
		return estado;
	}
	if (strstr(aval,"adorei") != NULL){
		estado = cbom(j, inv);	
		return estado;
	}
	if (strstr(aval,"gostei") != NULL){
		estado = cbom(j, inv);	
		return estado;
	}
	if (strstr(aval,"amei") != NULL){
		estado = cbom(j, inv);	
		return estado;
	}
	if (strstr(aval,"eficiente") != NULL){
		estado = cbom(j, inv);	
		return estado;
	}
	if (strstr(aval,"boa") != NULL){
		estado = cbom(j, inv);	
		return estado;
	}
	if (strstr(aval,"maravilhosa") != NULL){
		estado = cbom(j, inv);	
		return estado;
	}
	if (strstr(aval,"otima") != NULL){
		estado = cbom(j, inv);	
		return estado;
	}
	if(strstr(aval,"detestei") != NULL){
		estado = cruim(j, inv);	
		return estado;
	}
	if(strstr(aval,"odiei") != NULL){
		estado = cruim(j, inv);	
		return estado;
	}
	if(strstr(aval,"ruim") != NULL){
		estado = cruim(j, inv);	
		return estado;
	}
	if(strstr(aval,"pessimo") != NULL){
		estado = cruim(j, inv);	
		return estado;
	}
	if(strstr(aval,"terrivel") != NULL){
		estado = cruim(j, inv);	
		return estado;
	}
	if(strstr(aval,"raiva") != NULL){
		estado = cruim(j, inv);	
		return estado;
	}
	if(strstr(aval,"odio") != NULL){
		estado = cruim(j, inv);	
		return estado;
	}
	if(strstr(aval,"pessima") != NULL){
		estado = cruim(j, inv);	
		return estado;
	}
	if(strstr(aval,"lento") != NULL){
		estado = cruim(j, inv);	
		return estado;
	}
	if(strstr(aval,"lenta") != NULL){
		estado = cruim(j, inv);	
		return estado;
	}
	if(strstr(aval,"fragil") != NULL){
		estado = cruim(j, inv);	
		return estado;
	}
	if(strstr(aval,"desisti") != NULL){
		estado = cruim(j, inv);	
		return estado;
	}

	return 0;

}

void posneg(char *prod, char **nome, char ***aval, int coments, char *exp){	//se foi perguntado a quantidade de comentarios positivos ou negativos de um produto essa funcao é chamada, primeiro identificam-se os comentarios referentes ao produto, depois procura nesses comentarios palavras polarizadoras

	int estado=0, inv=-1;
        float cneg=0, cpos=0, total;
	for(int i=0; i<coments; i++){
		if(strstr(prod, nome[i]) != NULL){
			for (int j=0; j<20; j++){
				estado = comparacao(aval[i][j], inv, j);
				inv = inversor(aval[i][j], j, inv);
				if(estado == 1){
					cpos++;
					inv = -1;
					break;
				}
				if(estado == 2){
					cneg++;
					inv = -1;
					break;
				}
			}
		}
	}
	if(strstr(exp, "positivos") != NULL){
		total = (cpos/(cneg+cpos))*100;
		printf("%.1f%%", total);
	}
	if(strstr(exp, "negativos") != NULL){
		total = (cneg/(cneg+cpos))*100;
		printf("%.1f%%", total);
	}

}


void procpal(char *prod, char *exp, char **nome, char ***aval, int coments){	//se a pergunta pedir para procurar alguma palavra especifica essa funcao é chamada, primeiro identifica-se os comentarios relacionados ao produto, entao percorre cada comentario procurando a palavra desejada

	int cont = 0, i, j;
	for(i=0; i<coments; i++){
		if(strstr(prod, nome[i]) != NULL){
			for (j = 0; j < 20; j++){
				if (aval[i][j] != NULL) {
					if(strcmp(aval[i][j], exp) == 0){
						cont++;
					}
				}
			}
		}
	}
	printf("%d", cont);

}

int main(){

	int coments, perg;
	scanf("%d%d", &coments, &perg);		//recebe se o numero de comentarios e perguntas que serao feitos
	int i, j;
	char **nome, ***aval;
	nome = (char **) calloc(coments, sizeof(char *));
	aval = (char ***) calloc(coments, sizeof(char **));
	if(aval == NULL || nome == NULL)	//confere o sucesso da alocaçao de memoria
		return 1;
	for(i=0; i<coments; i++){		//faz a leitura de cada comentario
		nome[i] = lernome();		//primeiro le o nome do produto
		aval[i] = (char **) calloc(20, sizeof(char *));
		if(aval[i] == NULL || nome[i] == NULL)
			return 1;
		for(j=0; j<20; j++){		//nessa laço for le cada uma das palavras do comentario, parando quando ler o caracter de fim de linha
			aval[i][j]= leraval();
			if(aval[i][j] == NULL)
				return 1;
			if(strstr(aval[i][j],"Ø") != NULL){
				break;
			}
		}
	}
	char **exp,** prod;
	exp = (char **) calloc(perg, sizeof(char*));
	prod = (char **) calloc(perg, sizeof(char*));
	if(exp == NULL || prod == NULL)
		return 1;
	for(i=0; i<perg; i++){		//le cada pergunta
	
		exp[i] = lerexp();	//le a expressao a ser procurada
		prod[i] = lerprod();	//le o nome do produto
		if(exp[i] == NULL || prod[i] == NULL)
			return 1;
		if(strstr(exp[i],"positivos") != NULL || strstr(exp[i],"negativos") != NULL){	//confere se a pergunta quer saber a polarizacao dos comentarios ou quer que procure uma palavra especifica
			if(i!=0)
				printf("\n");
			posneg(prod[i], nome, aval, coments, exp[i]);
		}
		else{
			if(i!=0)
				printf("\n");
			procpal(prod[i], exp[i], nome, aval, coments);
		}
	}
	for(i=0; i<coments; i++){	//todos os comandos a partir daqui sao para liberar a memoria alocada dinamicamente

		free(nome[i]);
		for(j=0; j<20; j++){
			free(aval[i][j]);
		}
		free(aval[i]);

	}
	free(nome);
	free(aval);
	for(i=0; i<perg; i++){

		free(exp[i]);
		free(prod[i]);

	}
	free(exp);
	free(prod);

	return 0;
}
