#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(void){

	char dif;
	int seq[9], semente, jogador[9], tentativas = 3, n_memo = 0, qseq = 0, Pontuacao = 0, acertos = 0, vitorias = 0;
	/* seq[]: sao os numeros q mostrarao | jogador[]: os numeros que seram digitados | acertos: qtde de acertos na rodada | vitorias: quantas vezes acertou completamente
	 n_memo: quantidade de numeros que mostraram | qseq: quantidade de seq */
	// int time; variavel para tempo de espera
	scanf("%d %c", &semente, &dif);

	srand(semente);
	// parametros gerados a partir da dificuldade escolhida
	if(dif == 'F'){
		n_memo = 5;
		qseq = 3;
		//time=5;
	}
	if(dif == 'I'){
		n_memo = 7;
		qseq = 4;
		//time=7;
	}
	if(dif == 'A'){
		n_memo = 9;
		qseq = 5;
		//time=10;
	}

	while(tentativas>0 && vitorias<qseq){      //loop para mostrar o jogo, com base nas tentaivas e vitorias do jogador
		int Pontuacao_rodada = 0;
		int erro = 0;
		acertos=0;
		printf("Sequencia #%d:\n",vitorias+1);
		for(int i=0;i<n_memo;i++){    // cria a sequencia e imprime ela
			seq[i] = rand() % 10;
			printf("%d", seq[i]);
			if(i<n_memo-1){printf(" ");}
		}
		/*sleep(time);							parte para esperar no codigo e limpar a tela
		  printf("\r                  \r")*/
		printf("\n");
		for(int i=0;i<n_memo;i++){   //coleta a sequencia do jogador
			scanf("%d", &jogador[i]);
		}
		for(int i=0;i<n_memo;i++){ // compara a sequencia com a do jogador
			if(seq[i]==jogador[i]){
				acertos+=1;
			}
		}
		if(acertos==n_memo){
		vitorias+=1;
		Pontuacao_rodada=acertos*10;
		printf("Correto!\nTentativas disponiveis: %d\nPontuacao: %d\n", tentativas, Pontuacao+Pontuacao_rodada);
		Pontuacao+=Pontuacao_rodada;
		}
		while(acertos<n_memo && tentativas>0){ // se o jogador errar a sequencia
			erro+=(n_memo-acertos);
			Pontuacao_rodada=(n_memo-erro)*10;
			tentativas-=1;
			acertos=0;
			if(Pontuacao_rodada<0){Pontuacao_rodada=0;}
			printf("Incorreto!\nTentativas disponiveis: %d\nPontuacao: %d\n", tentativas, Pontuacao+Pontuacao_rodada);
			if(tentativas>0){	
				printf("Sequencia #%d:\n",vitorias+1);
				for(int i=0;i<n_memo;i++){
					printf("%d", seq[i]);//imprime novamente a sequencia
					if(i<n_memo-1){printf(" ");}
				}
				/*sleep(time);							parte para esperar no codigo e limpar a tela
		  		  printf("\r                  \r")*/
				printf("\n");
				for(int i=0;i<n_memo;i++){
					scanf("%d", &jogador[i]);// coleta a sequencia do jogador
				}
				for(int i=0;i<n_memo;i++){//compara novamente a sequencia do jogador
					if(seq[i]==jogador[i]){
						acertos+=1;
					}
				}
			}
			if(acertos==n_memo){  //se o jogador acertar toda a sequencia
				printf("Correto!\nTentativas disponiveis: %d\nPontuacao: %d\n", tentativas, Pontuacao+Pontuacao_rodada);
				Pontuacao+=Pontuacao_rodada;
				vitorias+=1;
			}
		}
	}//mensagem final com base nas vitorias que o jogador obteve
	if(vitorias == qseq){
		printf("Otima memoria! Parabens!!!");
	}
	else { printf("Nao ha mais tentativas disponiveis... Tente novamente!");
	}
	return 0;
}
