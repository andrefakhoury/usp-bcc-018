#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


int main(){
	int com_per[2], aux = 0, k = 0, i, tam, j, t= 0,cont1,cont2,cont3,cont4;	// O vetor guarda dois numeros o primeiro o número de COMentarios e o segundo número o de PERguntas
	char nume[10];

	
	fgets(nume, sizeof(nume), stdin);
	
	k = strlen(nume);	//Correcao para que nume nao armazene o enter
	nume[k-1] = '\0';	// A variavel k nao sera mais usada entao pode ser usada posteriormente
	
	while((int)nume[aux] >= 48 && (int)nume[aux] <= 57){ //Percorre a string para encontrar os valores
		aux++;											//aux mostra a posicao do espaco que separa os dois numeros.
	}
	
	com_per[0] = 0;
	com_per[1] = 0;
	
	com_per[0] = atoi(&nume[0]);		//pega uma string de numeros e converte para um valor inteiro
	com_per[1] = atoi(&nume[aux+1]);
	
	//printf("com_per[0][%d]\n", com_per[0]);
	//printf("com_per[1][%d]\n", com_per[1]);
	//printf("%d   %d\n", com_per[0], com_per[1]);
	
	//Conjunto de estruturas da bang-of-words
	int matriz[com_per[0]][200];	//Cria uma matriz que armazena os valores dos numeros de vezes que palavras foram citadas.
	
	for(i = 0 ; i <  com_per[0] ; i++){ //Zera todos os elementos da matriz ou seja nao existe nenhuma palavra registrada no bag-of-words 
		for(j = 0 ; j < 200 ; j++){
			matriz[i][j] = 0;
		}
	}
	
	char *palavras[200];			//Cria um vetor onde será armazenado todas as palavras de todos os comentários(corresponde as colunas da matriz)
	
	for(i = 0 ; i < 200 ; i++){ 	//Como nenhuma palavra foi inseria todos os ponteiros são null
		palavras[i] = NULL;
	}
	
	char *produtos[com_per[0]]; 	//Cria um vetor que armazena os produtos (corresponde as linhas da matriz)
	
	char pala[20];				//armazena momentaneamente a cada palavra do comentario
	char prod[50];				//armazena momentaneamente cada produto
	char coment[450];			// Variavel que armazena cada linha (produto + comentario)
	
	for(j = 0 ; j < com_per[0] ; j++){			//For varre cada linha de comentario
		fgets(coment, sizeof(coment), stdin);
	
		tam = strlen(coment);  //Correcao para que coment nao armazene o enter
		coment[tam-1] = '\0';
	
		//printf("[%s]\n", coment);	
	
		k = 0;
		while(coment[k] != ';'){ // k retorna a posicao na string do ; que mostra a divisao entre o produto e seu comentario
			k++;
		}
	
		for(i = 0 ; i < (k); i++){ //Separa o produto da string e armazena em prod
			prod[i] = coment[i];
		}
		prod[k-1] = '\0';
		//printf("[%s]\n", prod);
		
		produtos[j] = malloc(sizeof(char)*(k)); //Aloca memoria naquela posicao no vetor linha
		
		strcpy(produtos[j], prod);
	
		//printf("produtos [%c]\n", produtos[j][k-1]);
		produtos[j][k-1] = '\0';
		//printf("produtos [%s]\n", produtos[j]);
		
		/*i = 0;
		while(produtos[j][i] != '\0' ){
			printf("*** [%c]  ", produtos[j][i]);
			i++;	
		}
		printf("\n");*/
		//i = strlen(produtos[j]);
		//printf("tam produtos %d\n", i);
		//printf("tam [%s]\n", produtos[j]);
		//____________________________________________________________________________________________________________________________________________________________________
		k = k+2;		// O k anteriormente estava na posicao do ; agora esta na primeira letra da primeira palavra do comentario
		i = k;
		cont1 = 0;
		while(i < (tam-3)){ // Varre as palavras montando um vetor (colunas da matriz)

			
			if(coment[i] == ' '){
				pala[cont1] = '\0';
				//printf("[%s]\n", pala);
				
				t=0;
				while(palavras[t] != NULL && strcmp(palavras[t], pala) != 0){ //Percorre o vetor de palavras verificando se a nova palavra ja existe
					t++;
				}
				//printf("numero %d", t);
				if(palavras[t] != NULL && strcmp(palavras[t], pala) == 0){  //A palavra ja existe no banco apenas incrementa o numero de vezes que e citada
					matriz[j][t]++;
				}
				
				if(palavras[t] == NULL){ //Caso onde a palavra ainda nao existe no banco entao deve ser registrada nele ()
					palavras[t] = malloc(sizeof(char)*strlen(pala));
					strcpy(palavras[t], pala);
					matriz[j][t]++; // = matriz[j][t]++; //Incrementa o numero de vezes que a palavra aparece no banco
				}
				cont1 = 0;
			}
			else{
				pala[cont1] = coment[i];
				cont1++;
			}
			
			i++;
		}	
	}
	/*
	t=0;
	while(palavras[t] != NULL){
		printf("[[%s]]\n", palavras[t]);
	
		t++;
	}
	printf("\n");
	t = 0;
	while(t < com_per[0]){
		printf("[-[%s]-]\n", produtos[t]);
		t++;
	}
	
	printf("\n\n");
	*//*
	printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n\n");
	j = 0;
	for(i = 0 ; i <  com_per[0] ; i++){ 
		while(palavras[j] != NULL){
		//for(j = 0 ; j < 200 ; j++){
			printf("[%d]   ", matriz[i][j]);
			j++;
		}
		j=0;
		printf("\n");
	}*/
	char *positivo[12];
	positivo[0] = malloc(sizeof(char)*4);
	strcpy(positivo[0], "bom");
	positivo[1] = malloc(sizeof(char)*12);
	strcpy(positivo[1], "maravilhoso");
	positivo[2] = malloc(sizeof(char)*6);
	strcpy(positivo[2], "otimo");
	positivo[3] = malloc(sizeof(char)*12);
	strcpy(positivo[3], "sensacional");
	positivo[4] = malloc(sizeof(char)*10);
	strcpy(positivo[4], "excelente");
	positivo[5] = malloc(sizeof(char)*7);
	strcpy(positivo[5], "adorei");
	positivo[6] = malloc(sizeof(char)*7);
	strcpy(positivo[6], "gostei");
	positivo[7] = malloc(sizeof(char)*5);
	strcpy(positivo[7], "amei");
	positivo[8] = malloc(sizeof(char)*10);
	strcpy(positivo[8], "eficiente");
	positivo[9] = malloc(sizeof(char)*4);
	strcpy(positivo[9], "boa");
	positivo[10] = malloc(sizeof(char)*12);
	strcpy(positivo[10], "maravilhosa");
	positivo[11] = malloc(sizeof(char)*6);
	strcpy(positivo[11], "otima");
	
	
	
	char *negativo[12];
	negativo[0] = malloc(sizeof(char)*9);
	strcpy(negativo[0], "detestei");
	negativo[1] = malloc(sizeof(char)*6);
	strcpy(negativo[1], "odiei");
	negativo[2] = malloc(sizeof(char)*5);
	strcpy(negativo[2], "ruim");
	negativo[3] = malloc(sizeof(char)*8);
	strcpy(negativo[3], "pessimo");
	negativo[4] = malloc(sizeof(char)*9);
	strcpy(negativo[4], "terrivel");
	negativo[5] = malloc(sizeof(char)*6);
	strcpy(negativo[5], "raiva");
	negativo[6] = malloc(sizeof(char)*5);
	strcpy(negativo[6], "odio");
	negativo[7] = malloc(sizeof(char)*8);
	strcpy(negativo[7], "pessima");
	negativo[8] = malloc(sizeof(char)*6);
	strcpy(negativo[8], "lento");
	negativo[9] = malloc(sizeof(char)*6);
	strcpy(negativo[9], "lenta");
	negativo[10] = malloc(sizeof(char)*7);
	strcpy(negativo[10], "fragil");
	negativo[11] = malloc(sizeof(char)*8);
	strcpy(negativo[11], "desisti");



	
	char *vet_per[5];
	vet_per[0] = NULL;		//Armazena cada palavra da pergunta em uma posicao
	vet_per[1] = NULL;
	vet_per[2] = NULL;
	vet_per[3] = NULL;
	vet_per[4] = NULL;
	
	char perguntas[80];
	float vet_resposta[com_per[1]];	//vetor que guarda as respostas
	int vet_posiresp[com_per[1]];	//vetor auxiliar que armazena a ordem do tipo da pergunta, se e a primeira ou a segunda
	for(j = 0 ; j < com_per[1]; j++){ // Varre as linhas das perguntas
		
		fgets(perguntas, sizeof(perguntas), stdin);	//Recebe a pergunta e armazena na variavel perguntas
		perguntas[strlen(perguntas)] = '\0';
		//printf("[%s]\n", perguntas);
		
		cont2 = 0;
		i = 0;
		cont1 = 0;
		cont3 = strlen(perguntas);

		while(cont3 >= 0){
			
			if(perguntas[i] == ' ' || perguntas[i] == '\0'){
				pala[cont1] = '\0';
				//printf("[%s]\n", pala);
				
				vet_per[cont2] = malloc(sizeof(char)*strlen(pala));
				
				strcpy(vet_per[cont2], pala);
				
				cont1 =0;
				cont2++;
			}
			else{
				pala[cont1] = perguntas[i];
				cont1++;
			}
			
			i++;
			cont3--;
		}
		char busca_prod[70];
		
		strcpy(busca_prod, vet_per[3]);
		strcat(busca_prod, " ");
		strcat(busca_prod, vet_per[4]);
		cont4 = 0;
		
		for(cont4 = 0 ; cont4 < 70; cont4++){
			if(busca_prod[cont4] == '\n' || busca_prod[cont4] == '\r'){
				busca_prod[cont4] = '\0';
			}
		}
		//while(busca_prod[cont4] != '\n' && cont4 < 70){
		//	cont4++;
		//	printf("")
		//}
		//if(busca_prod[cont4] == '\n'){
		//	busca_prod[cont4] = '\0';
		//}
			
			
		//busca_prod[strlen(busca_prod)-1] = '\0';
		//printf("-[%s]-   [%c]\n", busca_prod, busca_prod[strlen(busca_prod)-1]);
		
		
		
		
		//printf("[[entrou]]\n");
		//Verificacao da pergunta
		char p1[8] = "palavra";	// strings usadas para comparacao
		char p2[8] = "quantos";
		float cont_resp = 0.0;
		if(strcmp(vet_per[0], p1) == 0){
			//printf("[entrou]\n");
			//n_pergunta = 1;
			for(i = 0 ; i < com_per[0]; i++){
					//printf("buscando linha %d\n produtos[%s]   busca_prod[%s]", i, produtos[i], busca_prod);
					//printf("produtos[%s] || busca_prod[%s]\n", produtos[i], busca_prod);
				if(strcmp(produtos[i], busca_prod) == 0){
					//printf("produtos[%s] || busca_prod[%s]\n", produtos[i], busca_prod);
					
					t=0;
					while(palavras[t] != NULL && strcmp(palavras[t], vet_per[1]) != 0){ //Percorre o vetor de palavras verificando se encontra a palavra
						t++;
					}
					
					if(palavras[t] != NULL && strcmp(palavras[t], vet_per[1]) == 0){  //A palavra foi encontrada
						cont_resp = cont_resp + (float)(matriz[i][t]);
						
					}
					
				}
			}
			//printf("%f\n", vet_resposta[j]);
			vet_posiresp[j] = 1;
			vet_resposta[j] = cont_resp;
			
		}
		
		int quant_total =0, x=0,y=0;
		int quant_analisada = 0;
		if(strcmp(vet_per[0], p2) == 0){
			//printf("entrou-----\n");
			for(i = 0 ; i < com_per[0]; i++){
				//printf("produtos[%s] || busca_prod[%s]\n", produtos[i], busca_prod);
				if(strcmp(produtos[i], busca_prod) == 0){
					quant_total++;
					if(strcmp(vet_per[1], "positivos") == 0){
						for(x = 0; x < 12 ; x++){
							y=0;
							while(palavras[y] != NULL && strcmp(palavras[y], positivo[x]) != 0){
								y++;
							}
							if(palavras[y] != NULL && strcmp(palavras[y], positivo[x]) == 0){
								if(matriz[i][y] >= 1){
									quant_analisada++;
									//printf("analisada %d    total  %d\n", quant_analisada, quant_total);
									break;
									
								}
							}
						
						}
						//vet_posiresp[j] = 2;
						//vet_resposta[j] = (quant_analisada/quant_total)*100.0;
					}
					
					if(strcmp(vet_per[1], "negativos") == 0){
						//printf("entrou negativo\n");
						for(x = 0; x < 12 ; x++){
							y=0;
							while(palavras[y] != NULL && strcmp(palavras[y], negativo[x]) != 0){
								//printf("palavra no vetor[%s]\tpalavra do banco[%s]\n", palavras[y], negativo[x]);
								y++;
							}
							if(palavras[y] != NULL && strcmp(palavras[y], negativo[x]) == 0){
								//printf("		palavra no vetor[%s]   palavra do banco[%s]  valor matriz [%d]\n", palavras[y], negativo[x], matriz[i][y]);
								if(matriz[i][y] >= 1){
									quant_analisada++;
									break;
									//printf("analisada %d    total  %d\n", quant_analisada, quant_total);
								}
							}
						
						}
						//printf("total[%d]\nanalisado[%d]\n", quant_total, quant_analisada);

					}
					
				}
				//printf("	fim da linha %d\n", i);
				//printf("analisada %d    total  %d\n", quant_analisada, quant_total);
			}
			vet_posiresp[j] = 2;
			vet_resposta[j] = (((float)(quant_analisada))/((float)(quant_total)))*100.0;
		}
		
	/*printf("\n\n");	
	j = 0;
	for(i = 0 ; i <  com_per[0] ; i++){ 
		while(palavras[j] != NULL){
		//for(j = 0 ; j < 200 ; j++){
			printf("[%d]   ", matriz[i][j]);
			j++;
		}
		j=0;
		printf("\n");
	}*/
		
		
		
		
		
	} //for das perguntas
	
	for(j = 0 ; j < com_per[1] ; j++){
		
		//printf("%d   ", vet_posiresp[j]);
		if(vet_posiresp[j] == 1){
			printf("%d\n", (int)(vet_resposta[j]));	
		}
		if(vet_posiresp[j] == 2){
			//printf("%f\n", (vet_resposta[j]));
			printf("%.1f", vet_resposta[j]);
			printf("%%\n");
			
		}

		
	}
	/*t = 0;
	while(t < 5){
		printf("-[%s]-\n", vet_per[t]);
		t++;
	}*/
	
	
	
	
	
	
	
	
	
	//Libera as estruturas que foram alocadas dinamicamente
	t = 0;
	while(t < 5){
		free(vet_per[t]);
		t++;
	}
	
	t = 0;
	while(palavras[t] != NULL){
		free(palavras[t]);
		t++;
	}
	
	t = 0;
	while(t < com_per[0]){
		free(produtos[t]);
		t++;
	}
	
	return 0;
}


/*com_per[0] = (com_per[0]) + (atoi(&nume[i])pow(10,(aux-i));*/