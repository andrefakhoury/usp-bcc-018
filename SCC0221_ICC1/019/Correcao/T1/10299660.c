#include <stdio.h>   // p/ fun��es b�sicas, como printf() e scanf().
#include <stdlib.h> // P/ as fun��es rand() e srand().
#include <time.h>  // P/ as fun��es time() e clock() e a constante CLOCKS_PER_SEC.
#include <unistd.h>

//prot�tipos: 
/*void temporizador (int tempo);*/
/* A fun��o acima exercer� o papel de pausar o programa pelo
tempo necess�rio e, fazer com que os valores apresentados sumam
na tela, para que o usu�rio n�o veja a sequ�ncia ap�s o tempo 
determinado. */ 
void comparador (char D, int seq, int seed, int val, int seg);

/*void temporizador (int tempo) {
	float t1, t2=0;
    t1 = (float)clock()/(float)CLOCKS_PER_SEC; 
    //   Como a func�o clock() retorna o valor desde o in�cio do programa
    // em milissegundos, t1 foi dividido pela constante CLOCKS_PER_SEC 
	// que equivale 1000, para transformar seu valor em segundos. 
    while (t2-t1<tempo) 
    	t2 = (float)clock()/(float)CLOCKS_PER_SEC;
    // O while ir� rodar at� que a diferen�a entre o tempo de in�cio 
	//da fun��o temporizador e o in�cio do programa ser maior ou igual
	//o valor em segundos definido. 
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	// Para a sequ�ncia "sumir" ap�s sair do while, foi optado o recurso de pular v�rias linhas.
	return ;
} */


void comparador (char D, int seq, int seed, int val, int seg){

	int m, n = 0, k = 3, L[val], pontuacao = 0, resposta;
	int i, j, l[val], erro, diferenca;
	srand (seed);
	
	while (n < seq){
		j = 0, erro = 0;
		diferenca = val*10;
		pontuacao = pontuacao + val * 10;
		printf("Sequencia #%d:\n", n+1);
	
		for (i = 0; i < val; i++){ // Aqui � gerada uma lista a partir da fun��o rand(), de acordo com a seed plotada na fun��o srand().
			L[i] = rand()%10; 
			printf("%d ", L[i]);
		}
	
		printf("\n");	
		//temporizador(seg); ///////////////////// Fun��o que passa "seg" segundos./////////////////////

		if (D == 'F') // De acordo com a dificuldade, � pedido ao usu�rio digitar a sequ�ncia que memorizou.
			scanf("%d %d %d %d %d", &l[0], &l[1], &l[2], &l[3], &l[4]);
		else if (D == 'I')
			scanf("%d %d %d %d %d %d %d", &l[0], &l[1], &l[2], &l[3], &l[4], &l[5], &l[6]);
		else if (D == 'A')
			scanf("%d %d %d %d %d %d %d %d %d", &l[0], &l[1], &l[2], &l[3], &l[4], &l[5], &l[6], &l[7], &l[8]);

		while (j < val){ //
			if (l[j] != L[j]){
				resposta = 1;                     //   Caso a resposta seja diferente a da lista, um erro � contabilizado e a vari�vel "resposta" recebe
				erro = erro + 1;                  // o valor de 1. 
			}                                     
			if (j+1 == val && erro == 0)          //   Caso o usu�rio acerte toda a sequ�ncia, sem errar, � atribu�do 2 � vari�vel "resposta". 
				resposta = 2;
			j++;
		}
		
		if (resposta == 1 && k != 0){
	
			while (resposta == 1 && k != 0){
				k = k - 1;                      //   "k" iniciou valendo 3, que � o n�mero de tentativas restantes.
				m = 0;                          //   Como resposta vale 1, houve pelo menos um erro, portanto � descontado o valor de
												// 1 no n�mero de tentativas.
				while (m < erro){
					diferenca = diferenca - 10; //   Neste caso, o "while" exerce o papel de testar, caso o erro exceda o n�mero m�ximo
					if (diferenca < 0 )         // permitido, que no caso � o valor de val*10.
						erro = 0;               //   Caso exceda, o erro � tomado como o menor n�mero antes de da diferen�a ser igual a 0, podendo ser 0.
					else if (diferenca == 0)
						erro = m + 1;
				
					m++;
				}
	
				pontuacao = pontuacao - erro*10;
	
				if (pontuacao < 0) //  Este "if" impede com que o valor da pontua��o seja negativo.
					pontuacao = 0;

				printf("Incorreto!\n");
				printf("Tentativas disponiveis: %d\n", k);
				printf("Pontuacao: %d\n", pontuacao);
			
				if (k != 0)
					printf("Sequencia #%d:\n", n + 1);
	
				if (k == 0){                            //  Caso o n�mero de tentativas chegue a 0, � imprimido a mensagem abaixo, e terminado a fun��o.
					printf("Nao ha mais tentativas disponiveis... Tente novamente!\n");
					return ;
				}
		
				for (m = 0; m < val; m++) //   Caso o erro ocorra ap�s outro erro, � imprimida a mesma sequ�ncia e solicitado novamente para que
					printf("%d ", L[m]);  // o usu�rio digite o que memorizou.
				
				printf("\n");
				//temporizador(seg);  ///////////////////// Fun��o que passa "seg" segundos./////////////////////
			
				if (D == 'F')
					scanf("%d %d %d %d %d", &l[0], &l[1], &l[2], &l[3], &l[4]);
				else if (D == 'I')
					scanf("%d %d %d %d %d %d %d", &l[0], &l[1], &l[2], &l[3], &l[4], &l[5], &l[6]);
				else if (D == 'A')
					scanf("%d %d %d %d %d %d %d %d %d", &l[0], &l[1], &l[2], &l[3], &l[4], &l[5], &l[6], &l[7], &l[8]);
					
				m = 0, erro = 0;
				while (m < val){
					if (l[m] != L[m]){             //   Novamente, os erros s�o somados na vari�vel "erro".
						erro = erro + 1;           //   Caso acerte, o valor de "resposta" torna-se 2 e o c�dico "sai" do 
					}                              // "while (resposta == 1 && k != 0)" e do "if (resposta == 1 && k != 0)".
					if (erro == 0 && m+1 == val){
						resposta = 2;
					}
					m++;
				}
			}
		}
	
		if (resposta == 2){
			printf("Correto!\n");                  //   Quando "resposta" vale 2, muda-se a sequ�ncia de n�meros.
			n = n + 1;
			printf("Tentativas disponiveis: %d\n", k);
			printf("Pontuacao: %d\n", pontuacao);
			if (n == seq){
				printf("Otima memoria! Parabens!!!\n"); //   Chegando-se a acertar a �ltima sequ�ncia do jogo, o usu�rio recebe 
				return ;                                // tal mensagem, e a fun��o � terminada.
			}
		}
	}
}

int main(void){
    sleep(1);
    printf("oie\n");
	
	int i = 0, seed;
	char dif;
	
	while ( i != 1 ){
	
		scanf("%d %c", &seed, &dif ); 	// Leitura da semente e da dificuldade do jogo.
										// A fun��o comparador() � chamada diferentemente, de acordo com o valor de "dif".	
		if (dif == 'F'){
			comparador (dif, 3, seed, 5, 5);
			return 0;
		}
		else if (dif == 'I'){
			comparador (dif, 4, seed, 7, 7);
			return 0;
		}
		else if (dif == 'A'){
			comparador (dif, 5, seed, 9, 10);
			return 0;
		}
		else // Caso o usu�rio digite uma letra ou n�mero inv�lida, a mensagem abaixo � exibida e � solocitado novamente os valores pelo usu�rio.
			printf("Digite um valor e dificuldade valido. \n");
	}
}
