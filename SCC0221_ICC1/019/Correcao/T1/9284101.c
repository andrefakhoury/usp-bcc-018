#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int funcao_F(int semente, int tentativas, int tam, int n_seq);
int *trata(int tam);

int main(){
	int semente, tentativas = 3;
	char nivel;

	scanf("%d %c", &semente, &nivel);
	
	/*for(i = 0; i < 3 ; i++){
		scanf("%c", &vet[i]);
	}*/
	// fgets(v, 300, stdin);
	// i = 0;
	// while(v[i] != '\0'){
	// 	printf("%c\n", v[i]);
	// 	i++;
	// }
	// nivel = v[i-1];
	// i = i-3;
	
	// while(j <= i){
	// 	if(j == 0)
	// 		num = num + atoi(&v[j])*100;
	// 	if(j == 1)
	// 		num = num + (atoi(&v[j])*10);
	// 	if(j == 2)
	// 		num = num + atoi(&v[j]);
	// 	j++;
	// }
	/*
	for(i = 0; i < 3 ; i++){
		vet1[i] = vet[i];
	}
	vet1[3] = '\0';
	
	nivel = vet1[2];
	semente = atoi(&vet1[0]);
	*/
	
	//printf("\n[%d]   [%c]\n", semente, nivel);
	
	switch(nivel){
		case 'F':
			//printf("o valor do nivel e [%c]\n", nivel);
			//vetor = trata(9);
			funcao_F(semente, tentativas, 5, 3);
			break;
		case 'I':
			//printf("o valor do nivel e [%c]\n", nivel);
			funcao_F(semente, tentativas, 7, 4);
			break;
		case 'A':
			//printf("o valor do nivel e [%c]\n", nivel);
			funcao_F(semente, tentativas, 9, 5);
			break;
		default :
			printf("opcao invalida\n");
	}
	
	
	/*if(semente == 1){
		system("cls");
	}*/
	
	return 0;
}
	
	int *trata( int tam ){ // tam = 9
		char vet[tam], vet1[tam];
		int i;// *result[tam+(tam-1)];
		int *result = malloc(sizeof(int)*(tam+(tam-1)));
		
		for(i = 0; i < tam ; i++){
			if(i == 0)
				scanf(" %c", &vet[i]);
			else
				scanf("%c", &vet[i]);
		}
		
		for(i = 0; i < tam ; i++){
			vet1[i] = vet[i];
		}
		vet1[tam] = '\0';
		
		for(i = 0; i < tam ; i+=2){
			//printf("[%d]", i);
			result[i/2] = atoi(&vet1[i]);
		}	
		/*
		for(i = 0; i < ((tam+1)/2) ; i++){
			printf("[%d]\n", result[i]);
		}*/
		
		return result;
	}

	int funcao_F(int semente, int tentativas, int tam, int n_seq){ //tam e quantidade de numeros que o usuario devera tentar momorizar(tamanho do vetor)
		int i, correto=1, pontuacao = 0, erro=0, seq_atual = 1, pont_max[2];
		int vet[tam], *V;
		srand(semente); // função que regula a função rand.
		pont_max[1] = 0;
		
		
		while(tentativas > 0 && seq_atual <= n_seq ){
			
			//printf("Sequencia #%d:\n", tentativa);
			printf("Sequencia #%d:\n", seq_atual);
			if(erro == 0){
				for(i=0 ; i<tam ; i++){
					vet[i] = rand()%10;
				}
			}
			
			for(i=0 ; i<tam ; i++){
				if(i == (tam-1))
					printf("%d\n", vet[i]);
				else
					printf("%d ", vet[i]);
			}
			
			V = trata((tam+(tam-1)));
			//inserir função que limpa a tela em 5 segundos.
			//printf("\n");
			correto = 1;
			for(i=0 ; i<tam ; i++){
				//scanf("%d", &usua[i]);
				if(vet[i] == V[i]){
					pontuacao = pontuacao + 10;
				}
				else{
					correto = 0;
					//pontuacao = pontuacao - 10;
				}
			}
			
			if(pontuacao < 0)
				pontuacao = 0;
			
			if(correto == 0){
				printf("Incorreto!\n");
				tentativas--;
				printf("Tentativas disponiveis: %d\n", tentativas);
				if(pont_max[1] == 0){
					pont_max[0] = pontuacao;
					pont_max[1] = 1;
					printf("Pontuacao: %d\n", pontuacao);
					pontuacao = 0;
				}
				else{
					pontuacao = pont_max[0] - ((10*tam)-pontuacao);
					if(pontuacao < 0)
						pontuacao = 0;
					pont_max[1] = 2;
					pont_max[0] = pontuacao;
					printf("Pontuacao: %d\n", pontuacao);
				}
				
				if(tentativas == 0){
					printf("Nao ha mais tentativas disponiveis... Tente novamente!\n");
				}
				
				erro = 1;
			}
			else{
				printf("Correto!\n");
				printf("Tentativas disponiveis: %d\n", tentativas);
				if(pont_max[1] == 1){
					pontuacao = pont_max[0];
					pont_max[1] = 0;
				}
				if(pont_max[1] == 2){
					pontuacao = pont_max[0];
					pont_max[1] = 0;
				}
				
				printf("Pontuacao: %d\n", pontuacao);
				seq_atual++;
				if(seq_atual > n_seq){
					printf("Otima memoria! Parabens!!!\n");
				}
				erro = 0;
			}
		}	
		return 0;
	}

	

	
