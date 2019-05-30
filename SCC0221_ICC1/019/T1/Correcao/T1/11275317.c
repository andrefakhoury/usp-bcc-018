#include <stdio.h> //biblioteca de entrada e saida
#include <stdlib.h> //biblioteca para chamar a funcao srand
#include <unistd.h> //biblioteca para chamar a funcao sleep

#define MAX_RAND 10 //define que o conjunto de numeros gerados aleatoriamente sera de 0 a 9
#define PONTO_POR_VALOR 10 //define 10 pontos para cada numero correto da sequencia
#define MAX_TENTATIVAS 3 //define o numero maximo de tentativas no jogo

//prototipos das funcoes
void ImprimirSequencia(int, int, int*);
int CompararSequencias(int, int*);
int ContarPontos(int,int,int,int,int*);
void GerarJogo(int, int, int); 

int main(void){ //funcao principal
	int semente = 0; //input de parametro do srand
	char nivel; //input para selecionar o nivel (F,I ou A)
	
	scanf("%d %c", &semente, &nivel); //Le as entradas digitadas pelo usuario
	
	srand (semente); //chamada da funcao srand com parametro definido pelo usuario
	
	switch(nivel){ //comando que determina qual tipo de jogo sera gerado com base no nivel de dificuldade
		case 'F': //caso o usuario escolha o nivel facil
			{
				GerarJogo(5, 3, 5); //gera um jogo com 5 numeros aleatarios, 3 sequencias diferentes e tempo limite de 5 segundos para memorizacao
				break;
			}
		case 'I': //caso o usuario escolha o nivel intermediario
			{
				GerarJogo(7, 4, 7); //gera um jogo com 7 numeros aleatorios, 4 sequencias diferentes e tempo limite de 7 segundos para memorizacao
				break;
			}
		case 'A': //caso o usuario escolha o nivel avancado
			{
				GerarJogo(9, 5, 10); //gera um jogo com 9 numeros aleatorios, 5 sequencias diferentes e tempo limite de 10 segundos para memorizacao
				break;
			}
	}
	
	return 0;
}

void ImprimirSequencia(int num_valores, int repeat, int* s){ //funcao que gera e imprime uma sequencia aleatoria
	int i = 0; //indice do loop
	
	for (i = 0; i < num_valores; i++){ //loop que gera uma sequencia ate uma quantidade i de numeros a depender do nivel de dificuldade
		if (repeat == 0){ //se o jogador esta pela primeira vez na sequencia
			s[i] = rand() % MAX_RAND; //gera um numero aleatorio de 0 a 9 e o guarda no vetor sequencia
		}
		//Obs.: Se o jogador errou, a sequencia tera que ser repetida, por isso nao é gerada uma nova sequencia
		if (i < num_valores - 1){ //se o numero nao for o ultimo do vetor
			printf("%d ", s[i]); //imprima o numero com espaco
		}
		else{ //se ele é o ultimo numero do vetor
			printf("%d\n", s[i]); //imprima sem espaco
		}
	}
}

int CompararSequencias(int num_valores, int *sequencia){ //funcao que compara a sequencia impressa com a dada pelo jogador
	int i = 0; //indice do loop
	int quant_acertos = 0; //variavel local
	
	for (i = 0; i < num_valores; i++){ //loop que le um valor x e o compara com o valor respectivo no vetor sequencia
		int x = 0; //inicializa a variavel local

		if (i < num_valores - 1){ //se o numero nao é o ultimo do vetor
			scanf("%d ", &x); // ler o valor x com espaco
		}
		else{ //se nao
			scanf("%d",&x); //ler o valor x sem espaco
		}
		if (x == sequencia[i]){ //se o valor x for igual ao da respectiva sequencia
			quant_acertos++; //o jogador acertou mais um valor
		}
	}
	
	return quant_acertos;
}

int ContarPontos(int repeat, int num_valores, int quant_acertos, int pontos, int *ganhoMaximo){ //funcao que atualiza os pontos a cada rodada
	int perdaPorErros = 0; //controla a quantidade de erros em cada rodada
	
	if (repeat == 0){ //se o jogador esta pela primeira vez na sequencia,
		pontos += num_valores*PONTO_POR_VALOR; //os pontos sao somados a quantidade maxima de pontos da sequencia
		*ganhoMaximo = num_valores*PONTO_POR_VALOR; //inicializa o ganhoMaximo da rodada com a quantidade maxima de pontos da sequencia
	}  
	
	perdaPorErros = (num_valores - quant_acertos)*PONTO_POR_VALOR; //a quantidade de erros em pontos é dada pela quantidade maxima de numeros da sequencia menos a quantidade de acertos

	if (perdaPorErros <= *ganhoMaximo){ //se o numero de erros em pontos for menor ou igual ao ganhoMaximo que ele pode obter
		pontos -= perdaPorErros; //reduz o numero de erros em pontos dos pontos totais
		*ganhoMaximo -= perdaPorErros; //reduz o numero de erros em pontos do ganhoMaximo que ele pode obter
	} 
	else{ //o maximo que ele pode ganhar tambem é o maximo que ele pode perder, por isso, se o numero de erros for maior
		pontos -= *ganhoMaximo; //reduz o proprio ganhoMaximo dos pontos totais
		*ganhoMaximo = 0; //nao ha mais o que perder ou ganhar
	}
	
	/*Obs.: ao longo dos loops o ganhoMaximo pode diminuir, entao é preciso testar se o numero de erros é menor do que o maximo que ele pode perder, 
	porque nao é possivel ter pontos negativos na rodada.*/
	
	return pontos;
}
void GerarJogo(int num_valores, int num_sequencias, int tempo){ //funcao que gera o jogo com base no nivel de dificuldade
	int j = 0; // indice do loop
	int num_tentativas = MAX_TENTATIVAS; //inicialmente o jogador comeca com o numero maximo de tentativas
	int sequencia[9]; //guarda os numeros gerados aleatoriamente em sequencia
	int repeat = 0; //controla quantas vezes o jogador repetiu uma sequencia.
	int quant_acertos = 0; //quantifica o numero de acertos em uma determinada sequencia
	int pontos = 0; //guarda o numero de pontos total do jogador
	int ganhoMaximo = 0; //controla quanto ele ainda pode ganhar numa sequencia apos ter errado
	int *g = &ganhoMaximo; //ponteiro util para atualizar seguramente o ganhoMaximo. Se fosse ganhoMaximo fosse uma variavel local, iniciaria sempre com 0 na chamada da funcao 
	
	for (j=1; j <= num_sequencias; j++){ //loop principal que testa j sequencias a depender do nivel de dificuldade
		do{ //executa pelo menos uma vez o que esta abaixo
			printf("Sequencia #%d:\n", j); //imprime o numero da sequencia com base no indice j

			ImprimirSequencia(num_valores, repeat, sequencia);
			
			quant_acertos = CompararSequencias(num_valores, sequencia);
			
			pontos = ContarPontos(repeat, num_valores, quant_acertos, pontos, g);
			
			//fflush(stdout); //garante que a sequecia sera exibida ate o tempo proposto
			//sleep(tempo); //pausa a execucao do programa ate o tempo definido
			/*printf("\r                 \r");*/ /*move o cursor 17 casas pra frente (contando o maior conjunto de numeros: 9 mais os espacos entre eles: 8) apagando-os 
			e retorna o cursor para o inicio*/
			
			if (quant_acertos == num_valores){ //se o jogador memorizou toda a sequencia
				printf("Correto!\n"); //Imprime mnsg de acerto
			}
			else{ // se nao
				printf("Incorreto!\n"); //Imprime msng de erro
				num_tentativas--; //perde uma tentativa
				repeat++; //Agora que o jogador errou, a sequencia sera repetida uma ou mais vezes
			}	
			
			printf("Tentativas disponiveis: %d\n", num_tentativas); //imprime o numero de tentativas disponiveis
			printf("Pontuacao: %d\n", pontos); //imprime a quantidade atual de pontos
			
			if (num_tentativas == 0){ //se o jogador nao possui mais tentativas disponiveis
				printf("Nao ha mais tentativas disponiveis... Tente novamente!\n");
				break; //encerra o loop while
			} 
		} while (num_valores != quant_acertos); //enquanto o jogador nao acertar toda a sequencia
		
		repeat = 0; //reinicializa a quantidade de repeticoes, porque o jogador esta entrando em uma nova sequencia pela primeira vez
		
		if (num_tentativas == 0){ //se o jogador nao possui mais tentativas disponiveis
			break; //encerra o loop for, se nao, mesmo que saisse do while, continuaria executando outras sequencias
		} 

		if (j == num_sequencias){ //se o loop consegue chegar ate o fim, significa que o jogador memorizou todas as sequencias do nivel determinado
			printf("Otima memoria! Parabens!!!\n"); //imprime msng de vitoria :)
		} 
	}	
}


